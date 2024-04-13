#ifndef AUCTIONSIMULATIONMODEL_H_
#define AUCTIONSIMULATIONMODEL_H_

#include "Auctioneer.h"
#include "SimulationModel.h"
#include "IController.h"

//--------------------  AuctionSimulationModel ----------------------------

/**
 * @brief Class AuctionSimulationModel wraps the SimulationModel class and overrides
 * the update method to handle the auction simulation, managing an Auctioneer object
*/
class AuctionSimulationModel : public SimulationModel {
 public:
  /**
   * @brief Constructor that creates the AuctionSimulationModel object
  */
  AuctionSimulationModel(IController& controller, Auctioneer auctioneer) : SimulationModel(controller), auctioneer(auctioneer), model(*this) {

  } // constructor

  /**
   * @brief Update the simulation model
   * @param dt Type double containing the time since update was last called.
  */
  void update(double dt);
 private:
  Auctioneer auctioneer;
  SimulationModel& model;  // Reference to SimulationModel
};

#endif // AUCTIONSIMULATIONMODEL_H_