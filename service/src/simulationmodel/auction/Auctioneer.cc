#include "Auctioneer.h"

Auctioneer::Auctioneer(SimulationModel* model, int maxWait) : model(model), maxAllottedWait(maxWait) {
}

Auctioneer::~Auctioneer() {}

void Auctioneer::update(double dt) {
    // If |removed| + |map| - |packageQueue| - # of known entities, 
    // then there is a new entity(ies) that may be a drone (check by id, only the new ones)

    // TODO: Implement auctioneer update
    
    // check if there are any new packages added to sim model and add them and their counters

    // If there is a counter expiration, calculate the optimal choice
    // If there is a drone to deliver then remove the counter and the package from the queue
    // Use the already computed data to send all packages that have already expired
}
