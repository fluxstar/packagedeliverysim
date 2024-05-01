#include "AuctionSimulationModel.h"
#include "IController.h"

AuctionSimulationModel::AuctionSimulationModel(IController& controller) : SimulationModel(controller), controller(controller) {
  auctioneer = new Auctioneer(this, 1000); // TODO: Five seconds for now
  this->model = new SimulationModel(controller);
} // constructor

AuctionSimulationModel::AuctionSimulationModel(SimulationModel* model) : SimulationModel(model->getController()), model(model), controller(model->getController()) {
  auctioneer = new Auctioneer(model, 1000);
} // constructor

AuctionSimulationModel::~AuctionSimulationModel() {
  delete auctioneer;
  delete model;
} // destructor

void AuctionSimulationModel::update(double dt) {
  this->model->update(dt);
  auctioneer->update(dt);
  //printf("Updating Auction Simulation Model\n");
}


void AuctionSimulationModel::setGraph(const routing::Graph* graph){
  this->model->setGraph(graph);
}

IEntity* AuctionSimulationModel::createEntity(const JsonObject& entity){
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = nullptr;
  IEntity* newEntity = nullptr;
  if (newEntity = this->model->getEntityFactory()->createEntity(entity)) {
    Drone* drone = dynamic_cast<Drone*>(newEntity);
    if (drone != nullptr) {
      printf("Attempting to create an auction drone\n");
      AuctionDrone* auctionDrone = new AuctionDrone(drone);
      auctioneer->addDrone(auctionDrone);
      myNewEntity = auctionDrone;
    }
    else {
      myNewEntity = newEntity;
    }
    // Call AddEntity to add it to the view
    myNewEntity->linkModel(this);
    this->model->addToController(myNewEntity);
    printf("Entity %s with ID %i added to the simulation\n", name.c_str(), myNewEntity->getId());
    this->model->addEntity(myNewEntity);
    // Add the simulation model as a observer to myNewEntity
    myNewEntity->addObserver(this);
  }
    return myNewEntity;
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

  void AuctionSimulationModel::stop() {
    this->model->stop();
  }

  const routing::Graph* AuctionSimulationModel::getGraph() const {
    return this->model->getGraph();
  }

  void AuctionSimulationModel::notify(const std::string& message) const {
    this->model->notify(message);
  }
