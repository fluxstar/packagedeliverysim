#include "AuctionDrone.h"

bool AuctionDrone::isAvailable() {
    return this->available;
}

void AuctionDrone::getNextDelivery() {
    this->available = true;
    this->pickedUp = false;
}

void AuctionDrone::setNextDelivery(Package* package) {
    this->available = false;
    this->pickedUp = false;
    this->nextDelivery = package;

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
