#include "Robot.h"
#include "Package.h"
#include "AstarStrategy.h"
#include "SimulationModel.h"

Robot::Robot(const JsonObject& obj) : IEntity(obj) {}

void Robot::update(double dt) {
  if (toPackage && toPackage->isCompleted()) {
    receive(pickingUp);

    pickingUp = nullptr;
    delete toPackage;
    toPackage = nullptr;

    package->notifyObservers(package->getName() + " was picked up by owner");
  }
  if (toPackage) toPackage->move(this, dt);
  
}

void Robot::receive(Package* p) { package = p; }

void Robot::notify(const std::string& message, const IPublisher* sender) const {
  Package *p = dynamic_cast<Package*>(const_cast<IPublisher*>(sender));
  if (!p) return;

  if (message == p->getName() + " is now available") {
    if (toPackage) delete toPackage;
    toPackage = new AstarStrategy(position, p->getPosition(), model->getGraph());
    pickingUp = p;
  }
}
