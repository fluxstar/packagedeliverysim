#include "Auctioneer.h"

Auctioneer::Auctioneer(SimulationModel* model, int maxWait) : model(model), maxAllottedWait(maxWait) {}

Auctioneer::~Auctioneer() {
  for (auto& drone : availableDrones) { // Neccessary?
    delete drone;
  }
}

void Auctioneer::update(double dt) {
    // TODO: Implement auctioneer update
}
