#define _USE_MATH_DEFINES
#include "Thief.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "Human.h"
#include "SimulationModel.h"

Thief::Thief(const JsonObject& obj) : Human(obj) {}

Thief::~Thief() {
  if (movement) delete movement;
}

void Thief::update(double dt) {
  if (stealing) {
    if (movement && movement->isCompleted()) {
      std::string message = stealing->getName() + " was stolen";
      int id = stealing->getId();
      stealing->notifyObservers(message);
      model->removeEntity(id);
    } else if (movement) {
      movement->move(this, dt);
      return;
    }
    stealing = nullptr;
    delete movement;
    movement = nullptr;
    return;
  }

  for (auto p : availablePackages) {
    if (this->position.dist(p->getPosition()) < 150) {
      if (movement) delete movement;
      movement =
          new AstarStrategy(position, p->getPosition(), model->getGraph());
      speed = 30;
      stealing = p;
      break;
    }
  }

  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
  } else {
    if (movement) delete movement;
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (model) movement = new AstarStrategy(position, dest, model->getGraph());
  }
}

void Thief::notify(const std::string& message, const IPublisher* sender) const {
  Package* p = dynamic_cast<Package*>(const_cast<IPublisher*>(sender));
  if (!p) return;

  if (message == p->getName() + " is now available") {
    availablePackages.insert(p);
  }

  if ((message == p->getName() + " was picked up by owner") ||
      (message == p->getName() + " was stolen")) {
    availablePackages.erase(p);
    if (stealing == p) {
      stealing = nullptr;
      movement = nullptr;
      speed = 15;
    }
  }
}
