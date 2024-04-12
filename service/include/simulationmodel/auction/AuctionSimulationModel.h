#ifndef AUCTIONSIMULATIONMODEL_H_
#define AUCTIONSIMULATIONMODEL_H_

#include "SimulationModel.h"
#include "Auctioneer.h"

class AuctionSimulationModel : public SimulationModel {
 public:
  void update(double dt) override;
 private:
  Auctioneer auctioneer;
};

#endif // AUCTIONSIMULATIONMODEL_H_