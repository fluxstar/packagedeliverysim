#ifndef AUCTIONSIMULATIONMODEL_H_
#define AUCTIONSIMULATIONMODEL_H_

#include "Auctioneer.h"

//--------------------  AuctionSimulationModel ----------------------------

/**
 * @brief Class AuctionSimulationModel wraps the SimulationModel class and overrides
 * the update method to handle the auction simulation, managing an Auctioneer object
*/
class AuctionSimulationModel : public SimulationModel {
 public:
  /**
   * @brief Update the simulation model
   * @param dt Type double containing the time since update was last called.
  */
  void update(double dt) override;
 private:
  Auctioneer auctioneer;
};

#endif // AUCTIONSIMULATIONMODEL_H_