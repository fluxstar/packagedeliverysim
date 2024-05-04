#include "AuctionSimulationModel.h"

#include "IController.h"

AuctionSimulationModel::AuctionSimulationModel(IController& controller)
    : SimulationModel(controller), controller(controller) {
  auctioneer = new Auctioneer(this, 1000);
  this->model = new SimulationModel(controller);
}  // constructor

AuctionSimulationModel::AuctionSimulationModel(SimulationModel* model)
    : SimulationModel(model->getController()),
      model(model),
      controller(model->getController()) {
  auctioneer = new Auctioneer(model, 1000);
}  // constructor

AuctionSimulationModel::~AuctionSimulationModel() {
  delete auctioneer;
  delete model;
}  // destructor

void AuctionSimulationModel::update(double dt) {
  this->model->update(dt);
  auctioneer->update(dt);
  // printf("Updating Auction Simulation Model\n");
}

std::deque<Package*>& AuctionSimulationModel::getScheduledDeliveries() {
  return this->model->getScheduledDeliveries();
}

void AuctionSimulationModel::setGraph(const routing::Graph* graph) {
  this->model->setGraph(graph);
}

IEntity* AuctionSimulationModel::createEntity(const JsonObject& entity) {
  IEntity* newEntity = this->model->createEntity(entity);
  if (dynamic_cast<Drone*>(newEntity) != nullptr) {
    // Create an auction drone to wrap the drone, and then replace the drone
    // with the auction drone
    AuctionDrone* auctionDrone =
        new AuctionDrone(dynamic_cast<Drone*>(newEntity));
    auctioneer->addDrone(auctionDrone);
    this->model->addEntity(auctionDrone);
  }

  return newEntity;
}

void AuctionSimulationModel::removeEntity(int id) {
  this->model->removeEntity(id);
}

std::map<int, IEntity*> AuctionSimulationModel::getEntities() {
  return this->model->getEntities();
}

void AuctionSimulationModel::scheduleTrip(const JsonObject& details) {
  this->model->scheduleTrip(details);
}

void AuctionSimulationModel::stop() { this->model->stop(); }

const routing::Graph* AuctionSimulationModel::getGraph() const {
  return this->model->getGraph();
}

void AuctionSimulationModel::notify(const std::string& message,
                                    const IPublisher* sender) const {
  this->model->notify(message, sender);
}

void AuctionSimulationModel::rescheduleTrip(JsonObject& details,
                                            Robot* receiver) {
  this->model->rescheduleTrip(details, receiver);
}
