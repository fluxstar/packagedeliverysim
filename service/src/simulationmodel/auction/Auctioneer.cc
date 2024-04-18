#include "Auctioneer.h"

Auctioneer::Auctioneer(SimulationModel* model, int maxWait) : model(model), maxAllottedWait(maxWait) {
}

Auctioneer::~Auctioneer() {}

int getDifference(Drone* drone, Package* package) {
    return std::abs(drone->getPosition().dist(package->getPosition()));
}

std::vector<std::vector<int>> branchAndBoundAssignment(const std::vector<std::vector<int>>& costMatrix) {
    int m = costMatrix.size();   // Number of jobs
    if (m==0) return std::vector<std::vector<int>>(); // Return empty vector if no jobs (packages
    int n = costMatrix[0].size(); // Number of workers
    std::vector<int> assignment(m, -1);
    std::vector<bool> rowUsed(m, false), colUsed(n, false);
    int minCost = INT_MAX;
    std::vector<std::vector<int>> minAssignment(m, std::vector<int>(n, -1));

    // Helper function to perform recursive backtracking
    auto backtrack = [&](int depth, int cost, auto&& backtrack) -> void {
        std::cout << "Entering backtrack with depth: " << depth << ", cost: " << cost << std::endl;

        if (cost >= minCost) {
            std::cout << "Cost is greater than or equal to minCost. Returning early." << std::endl;
            return;
        }

        if (depth == m) {
            std::cout << "Depth equals m. Checking if cost is less than minCost." << std::endl;
            if (cost < minCost) {
                std::cout << "Cost is less than minCost. Updating minCost and minAssignment." << std::endl;
                minCost = cost;
                minAssignment = std::vector<std::vector<int>>(m, std::vector<int>(n, -1));
                for (int i = 0; i < m; ++i) {
                    minAssignment[i][assignment[i]] = 1;
                }
            }
            return;
        }

        for (int j = 0; j < n; ++j) {
            std::cout << "Checking row " << depth << " and column " << j << std::endl;
            if (!rowUsed[depth] && !colUsed[j]) {
                std::cout << "Row and column are not used. Updating assignment and calling backtrack recursively." << std::endl;
                rowUsed[depth] = colUsed[j] = true;
                assignment[depth] = j;
                backtrack(depth + 1, cost + costMatrix[depth][j], backtrack);
                std::cout << "Back from recursion. Resetting row and column usage." << std::endl;
                rowUsed[depth] = colUsed[j] = false;
            }
        }
    };

    std::cout << "Starting backtrack from root." << std::endl;
    backtrack(0, 0, backtrack);
    std::cout << "Backtrack completed. Returning minAssignment." << std::endl;
    return minAssignment;
}

void Auctioneer::update(double dt) {
    // If |removed| + |map| - |packageQueue| - # of known entities, 
    // then there is a new entity(ies) that may be a drone (check by id, only the new ones)

    // TODO: Implement auctioneer update
    
    // check if there are any new packages added to sim model and add them and their counters

    // If there is a counter expiration, calculate the optimal choice
    // If there is a drone to deliver then remove the counter and the package from the queue
    // Use the already computed data to send all packages that have already expired
    std::map<int, IEntity*> entities = model->getEntities();
    for (int i = 0; i < entities.size(); i++){
        if (entities.contains(i)){
            IEntity* entity = entities.at(i);
            if (entity->getName() == "drone") {
                AuctionDrone* drone = dynamic_cast<AuctionDrone*>(entity);
                if (drone != nullptr) {
                    drones.push_back(drone);
                }
            }
        }

    }

    for (int i = 0; i < waitTimes.size(); i++){
        waitTimes[i] -= dt;
    }
    
    while (!model->scheduledDeliveries.empty()){
        Package* package = model->scheduledDeliveries.front();
        packages.push_back(package);
        waitTimes.push_back(maxAllottedWait);
        model->scheduledDeliveries.pop_front();
        printf("Auctioneer added package %s\n", package->getName().c_str());
    }

    if (!this->packages.empty() && this->waitTimes.front() <= 0 && drones.size() > 0) {
        printf("Package %s has expired\n", this->packages.front()->getName().c_str());
        std::vector<std::vector<int>> table;
        
        for(Package* package : packages) {
            std::vector<int> temp = std::vector<int>(); 
            table.push_back(temp);
            for(AuctionDrone* drone : drones) {
                table[table.size()].push_back(getDifference(drone, package));
                printf("Drone %s\n", drone->getName().c_str());
            }
        }
        printf("Table size: %d\n", table.size());
        std::vector<std::vector<int>> assignment = branchAndBoundAssignment(table);
    }
}