#include "AuctionSimulationModel.h"

void AuctionSimulationModel::update(){
  for (auto& [id, entity] : entities) {
    entity->update(dt);
    controller.updateEntity(*entity);
  }
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
  auctioneer.update(dt);
}