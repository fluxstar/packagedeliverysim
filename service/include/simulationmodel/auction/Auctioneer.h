#ifndef AUCTIONEER_H_
#define AUCTIONEER_H_

#include "SimulationModel.h"
#include "Package.h"

class Auctioneer : public SimulationModel {
 public:
  Auctioneer(SimulationModel* model, int maxWait);
  void update(double dt);
 private:
  std::vector<AuctionDrone*> availableDrones;
  SimulationModel* model;
  std::vector<Package> packages;
  std::vector<int> waitTimes;
  int maxAllottedWait;
};

#endif // AUCTIONEER_H_