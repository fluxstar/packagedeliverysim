#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "Package.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"

Drone::Drone(const JsonObject& obj) : IEntity(obj) { available = true; }

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

void Drone::setToFinalDestination(IStrategy* strategy) {
  toFinalDestination = strategy;
}

IStrategy* Drone::getDestination() { return toFinalDestination; }

void Drone::setToPackage(IStrategy* strategy) { toPackage = strategy; }

IStrategy* Drone::getToPackage() { return toPackage; }

bool Drone::isAvailable() { return available; }

bool Drone::hasPickedUp() { return pickedUp; }

void Drone::setAvailable(bool available) { this->available = available; }

void Drone::setPickedUp(bool pickedUp) { this->pickedUp = pickedUp; }

Package* Drone::getPackage() { return package; }

void Drone::setPackage(Package* package) { this->package = package; }

void Drone::getNextDelivery() {
  std::cout << "Drone main" << std::endl;
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      std::string message = getName() + " heading to: " + package->getName();
      notifyObservers(message);
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination = new JumpDecorator(new AstarStrategy(
            packagePosition, finalDestination, model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
            new SpinDecorator(new JumpDecorator(new DfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
            new SpinDecorator(new SpinDecorator(new BfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
            new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }
    }
  }
}

void Drone::setNextDelivery(Package* package) {
  this->package = package;
  if (package) {
    std::string message = getName() + " heading to: " + package->getName();
    notifyObservers(message);
    available = false;
    pickedUp = false;

    Vector3 packagePosition = package->getPosition();
    Vector3 finalDestination = package->getDestination();

    toPackage = new BeelineStrategy(position, packagePosition);

    std::string strat = package->getStrategyName();
    if (strat == "astar") {
      toFinalDestination = new JumpDecorator(new AstarStrategy(
          packagePosition, finalDestination, model->getGraph()));
    } else if (strat == "dfs") {
      toFinalDestination = new SpinDecorator(new JumpDecorator(new DfsStrategy(
          packagePosition, finalDestination, model->getGraph())));
    } else if (strat == "bfs") {
      toFinalDestination = new SpinDecorator(new SpinDecorator(new BfsStrategy(
          packagePosition, finalDestination, model->getGraph())));
    } else if (strat == "dijkstra") {
      toFinalDestination =
          new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
              packagePosition, finalDestination, model->getGraph())));
    } else {
      toFinalDestination =
          new BeelineStrategy(packagePosition, finalDestination);
    }
  }
}

void Drone::update(double dt) {
  if (available) getNextDelivery();

  if (toPackage) {
    toPackage->move(this, dt);

    if (toPackage->isCompleted()) {
      std::string message = getName() + " picked up: " + package->getName();
      notifyObservers(message);
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }
  }
  if (toFinalDestination->isCompleted()) {
    std::string message = getName() + " dropped off: " + package->getName();
    notifyObservers(message);
    delete toFinalDestination;
    toFinalDestination = nullptr;
    // package->handOff();
    std::string packageMessage = package->getName() + " is now available";
    package->notifyObservers(packageMessage);
    package = nullptr;
    available = true;
    pickedUp = false;
  }
}

IStrategy* Drone::getToFinalDestination() { return toFinalDestination; }
