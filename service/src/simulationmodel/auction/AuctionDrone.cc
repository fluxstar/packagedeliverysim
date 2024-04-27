#include "AuctionDrone.h"

void AuctionDrone::getNextDelivery() {
    // wait for auctioneer to start an auction
}

void AuctionDrone::setNextDelivery(Package* package) {
    this->sub->setAvailable(false);
    this->sub->setPickedUp(false);
    this->sub->setNextDelivery(package);
}

bool AuctionDrone::isAvailable(){
    return this->sub->isAvailable();
}

void AuctionDrone::update(double dt){
    IStrategy* toPackage = this->sub->getToPackage();
    IStrategy* toFinalDestination = this->sub->getToFinalDestination();
    Package* package = this->sub->getPackage();
    if (toPackage) {
        toPackage->move(this, dt);

        if (toPackage->isCompleted()) {
            std::string message =
                this->sub->getName() + " picked up: " + package->getName();
            this->sub->notifyObservers(message);
            delete toPackage;
            this->sub->setToPackage(nullptr);
            this->sub->setPickedUp(true);
        }
    } else if (toFinalDestination != nullptr) {
        toFinalDestination->move(this, dt);

        if (package && this->hasPickedUp()) {
            package->setPosition(sub->getPosition());
            package->setDirection(sub->getDirection());
        }

        if (toFinalDestination->isCompleted()) {
            std::string message =
                this->sub->getName() + " dropped off: " + package->getName();
            this->sub->notifyObservers(message);
            delete toFinalDestination;
            this->sub->setToFinalDestination(nullptr);
            toFinalDestination = nullptr;
            package->handOff();
            this->sub->setPackage(nullptr);
            this->sub->setAvailable(true);
            this->sub->setPickedUp(false);
        }
    }
}
void AuctionDrone::setToFinalDestination(IStrategy* strategy){
    this->sub->setToFinalDestination(strategy);
}
void AuctionDrone::setToPackage(IStrategy* strategy){
    this->sub->setToPackage(strategy);
}
IStrategy* AuctionDrone::getToPackage(){
    return this->sub->getToPackage();
}
bool AuctionDrone::hasPickedUp(){
    return this->sub->hasPickedUp();
}
void AuctionDrone::setAvailable(bool available){
    this->sub->setAvailable(available);
}
void AuctionDrone::setPickedUp(bool pickedUp){
    this->sub->setPickedUp(pickedUp);
}
Package* AuctionDrone::getPackage(){
    return this->sub->getPackage();
}
void AuctionDrone::setPackage(Package* package){
    this->sub->setPackage(package);
}
IStrategy* AuctionDrone::getToFinalDestination(){
    return this->sub->getToFinalDestination();
}