#ifndef AUCTIONEER_H_
#define AUCTIONEER_H_

#include <vector>
#include "SimulationModel.h"
#include "Package.h"
#include "AuctionDrone.h"
#include <limits.h>

//--------------------  Auctioneer ----------------------------

/**
 * @brief Class Auctioneer manages the auctioning of drones to packages
 * in the simulation using wait times and available drones
 **/
class Auctioneer {
 public:
  /**
   * @brief Default constructor that creates the Auctioneer object
  */
  Auctioneer(SimulationModel* model, int maxWait);
  
  /**
   * @brief Destructor
  */
  ~Auctioneer();

  /**
   * @brief Update the auction
   * @param dt Type double containing the time since update was last called.
  */
  void update(double dt);
 private:
  std::vector<AuctionDrone*> drones;
  SimulationModel* model;
  std::vector<Package> packages;
  std::vector<int> waitTimes;
  int maxAllottedWait;
};

#endif // AUCTIONEER_H_