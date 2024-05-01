#define _USE_MATH_DEFINES
#include "Thief.h"
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

Thief::Thief(const JsonObject& obj) : Human(obj) {}

Thief::~Thief() {
  if (movement) delete movement;
}

void Thief::update(double dt) {
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
    std::cout << "Thief " << name << " received message " << message << std::endl;
  }
}