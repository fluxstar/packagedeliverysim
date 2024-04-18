#include "AuctionDrone.h"

void AuctionDrone::getNextDelivery() {
    // wait for auctioneer to start an auction
}

void AuctionDrone::setNextDelivery(Package* package) {
    this->setAvailable(false);
    this->setPickedUp(false);
    this->setPackage(package);
    printf("AuctionDrone %d setNextDelivery %s\n", this->getId(),
           package->getName().c_str());

    if (package) {
        std::string message = getName() + " heading to: " + package->getName();
        notifyObservers(message);
        this->setAvailable(false);
        this->setPickedUp(false);

        Vector3 packagePosition = this->getPackage()->getPosition();
        Vector3 finalDestination = this->getPackage()->getDestination();

        this->setToPackage(new BeelineStrategy(position, packagePosition));

        std::string strat = package->getStrategyName();
        if (strat == "astar") {
            this->setDestination(new JumpDecorator(new AstarStrategy(
                packagePosition, finalDestination, model->getGraph())));
        } else if (strat == "dfs") {
            this->setDestination(
                new SpinDecorator(new JumpDecorator(new DfsStrategy(
                    packagePosition, finalDestination, model->getGraph()))));
        } else if (strat == "bfs") {
            this->setDestination(
                new SpinDecorator(new SpinDecorator(new BfsStrategy(
                    packagePosition, finalDestination, model->getGraph()))));
        } else if (strat == "dijkstra") {
            this->setDestination(
                new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
                    packagePosition, finalDestination, model->getGraph()))));
        } else {
            this->setDestination(
                new BeelineStrategy(packagePosition, finalDestination));
        }
    }
}
