#ifndef AUCTIONEER_H_
#define AUCTIONEER_H_

#include <limits.h>

#include <vector>

#include "AuctionDrone.h"
#include "Package.h"
#include "SimulationModel.h"

#define MAX_ROUNDS 10

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

  /**
   * @brief Add a drone to the auctioneer
   * @param drone Type AuctionDrone pointer to the drone to be added
   */
  void addDrone(AuctionDrone* drone);

  /**
   * @brief Assign a package to a drone using an auction
   * @param drones Type vector of AuctionDrone pointers containing available
   * drones
   * @param packages Type vector of Package pointers containing packages to be
   * picked up
   * @param prices Type vector of integers containing the current "prices" of
   * packages
   */
  void auctionAssignment(std::vector<AuctionDrone*> drones,
                         std::vector<Package*>& packages,
                         std::vector<int> prices);

 private:
  std::vector<AuctionDrone*> drones;
  SimulationModel* model;
  std::vector<Package*> packages;
  std::vector<int> waitTimes;
  int maxAllottedWait;
};

#endif  // AUCTIONEER_H_
