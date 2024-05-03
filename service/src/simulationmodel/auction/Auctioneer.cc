#include "Auctioneer.h"

Auctioneer::Auctioneer(SimulationModel* model, int maxWait) : model(model), maxAllottedWait(maxWait) {
}

Auctioneer::~Auctioneer() {}

int getDifference(Drone* drone, Package* package) {
    return std::abs(drone->getPosition().dist(package->getPosition()));
}

void Auctioneer::addDrone(AuctionDrone* drone) {
    drones.push_back(drone);
}

void Auctioneer::auctionAssignment(std::vector<AuctionDrone*> drones, std::vector<Package*>& packages, std::vector<int> prices) {
    // TODO: drones, packages, and prices (waitTimes) are class variables

    std::vector<AuctionDrone*> currentAssignments;
    for (int i = 0; i < packages.size(); i++){
        currentAssignments.push_back(nullptr); // Initialize all packages to be unassigned
    }
    // Assume all drones are available
    for (int i = 0; i < MAX_ROUNDS; i++){
        for (int d = 0; d < drones.size(); d++){
            AuctionDrone* drone = drones[d];
            int maxValue = INT_MIN;
            int maxPackageIndex;
            for (int j = 0; j < prices.size(); j++){
                int value = (INT_MAX - getDifference(drone, packages[j])) - prices[j];
                if (value > maxValue){ // This function is to find the most valuable package
                    maxValue = value;
                    maxPackageIndex = j;
                }
            }
            
            // clear your current package's currentAssignment entry
            for (int j = 0; j < currentAssignments.size(); j++){
                if (currentAssignments[j] == drone){
                    currentAssignments[j] = nullptr;
                }
            }
            
            // reset the other drone
            if (currentAssignments[maxPackageIndex] != nullptr){
                currentAssignments[maxPackageIndex]->setAvailable(true);
                currentAssignments[maxPackageIndex]->setPickedUp(false);
                currentAssignments[maxPackageIndex]->setPackage(nullptr);
                currentAssignments[maxPackageIndex]->setToPackage(nullptr);
                currentAssignments[maxPackageIndex]->setToFinalDestination(nullptr);
            }

            drone->setNextDelivery(packages[maxPackageIndex]);

            currentAssignments[maxPackageIndex] = drone;

            // Calculate the new price for the package (equal to the current price of the second best option)
            int newCost = INT_MIN;
            int newValue = INT_MIN;
            for (int j = 0; j < prices.size(); j++){
                if(j != maxPackageIndex){
                    int value = (INT_MAX - getDifference(drone, packages[j])) - prices[j];
                    if (value > maxValue){ // This function is to find the most valuable package
                        newValue = value;
                        newCost = prices[j];
                    }
                }
            }
            if (prices[maxPackageIndex] < newCost){
                prices[maxPackageIndex] = newCost;            
            }
        }
    }

    for (int i = 0; i < currentAssignments.size(); i++){
        if (currentAssignments[i] != nullptr){
            packages.erase(packages.begin() + i);
            currentAssignments.erase(currentAssignments.begin() + i);
            waitTimes.erase(waitTimes.begin() + i);
            --i;
        }
    }


}

void Auctioneer::update(double dt) {
    // If |removed| + |map| - |packageQueue| - # of known entities, 
    // then there is a new entity(ies) that may be a drone (check by id, only the new ones)

    // TODO: Implement auctioneer update
    
    // check if there are any new packages added to sim model and add them and their counters

    // If there is a counter expiration, calculate the optimal choice
    // If there is a drone to deliver then remove the counter and the package from the queue
    // Use the already computed data to send all packages that have already expired

    for (int i = 0; i < waitTimes.size(); i++){
        waitTimes[i] -= dt;
    }
    
    while (!model->scheduledDeliveries.empty()){
        Package* package = model->scheduledDeliveries.front();
        packages.push_back(package);
        waitTimes.push_back(maxAllottedWait);
        model->scheduledDeliveries.pop_front();
        printf("Auctioneer added package %s\n", package->getName().c_str());
        model->notify("Auctioneer added package " + package->getName(), package);
    }

    std::vector<std::vector<int>> assignment;
    std::vector<AuctionDrone*> availableDrones;
    std::vector<int> prices;
    if (!this->packages.empty() && this->waitTimes.front() <= 0 && drones.size() > 0) {
        for (int i = 0; i < drones.size(); i++){
            if (drones[i]->isAvailable()){
                availableDrones.push_back(drones[i]);
            }
        }
        for (auto package : packages){
            prices.push_back(0);
        }

        auctionAssignment(availableDrones, packages, prices);
    }
}