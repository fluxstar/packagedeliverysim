#include "Auctioneer.h"

Auctioneer::Auctioneer(SimulationModel* model, int maxWait) : model(model), maxAllottedWait(maxWait) {
}

Auctioneer::~Auctioneer() {}

int getDifference(Drone* drone, Package* package) {
    return std::abs(drone->getPosition().dist(package->getPosition()));
}

void Auctioneer::update(double dt) {
    // If |removed| + |map| - |packageQueue| - # of known entities, 
    // then there is a new entity(ies) that may be a drone (check by id, only the new ones)

    // TODO: Implement auctioneer update
    
    // check if there are any new packages added to sim model and add them and their counters

    // If there is a counter expiration, calculate the optimal choice
    // If there is a drone to deliver then remove the counter and the package from the queue
    // Use the already computed data to send all packages that have already expired
    std::vector<std::vector<int>> table;
    for(AuctionDrone* drone : drones) {
        std::vector<int> temp = std::vector<int>(); 
        table.push_back(temp);
        for(Package package : packages) {
            table[table.size()].push_back(getDifference(drone, &package));
        }
    }
}

std::vector<std::vector<int>> branchAndBoundAssignment(const std::vector<std::vector<int>>& costMatrix) {
    int m = costMatrix.size();   // Number of jobs
    int n = costMatrix[0].size(); // Number of workers
    std::vector<int> assignment(m, -1);
    std::vector<bool> rowUsed(m, false), colUsed(n, false);
    int minCost = INT_MAX;
    std::vector<std::vector<int>> minAssignment(m, std::vector<int>(n, -1));

    // Helper function to perform recursive backtracking
    auto backtrack = [&](int depth, int cost, auto&& backtrack) -> void {
        if (cost >= minCost) {
            return;
        }

        if (depth == m) {
            if (cost < minCost) {
                minCost = cost;
                minAssignment = std::vector<std::vector<int>>(m, std::vector<int>(n, -1));
                for (int i = 0; i < m; ++i) {
                    minAssignment[i][assignment[i]] = 1;
                }
            }
            return;
        }

        for (int j = 0; j < n; ++j) {
            if (!rowUsed[depth] && !colUsed[j]) {
                rowUsed[depth] = colUsed[j] = true;
                assignment[depth] = j;
                backtrack(depth + 1, cost + costMatrix[depth][j], backtrack);
                rowUsed[depth] = colUsed[j] = false;
            }
        }
    };

    backtrack(0, 0, backtrack);
    return minAssignment;
}