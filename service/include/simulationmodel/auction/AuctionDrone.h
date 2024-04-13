#ifndef AUCTIONDRONE_H_
#define AUCTIONDRONE_H_

#include "Drone.h"

//--------------------  AuctionDrone ----------------------------

/**
 * @brief Class AuctionDrone wraps Drone to interface with the auctioneer
**/
class AuctionDrone : public Drone {
 public:
  /**
   * @brief Gets the next delivery from the auctioneer
  */
  void getNextDelivery();
  /**
   * @brief Sets the next delivery for the drone
  */
  void setNextDelivery(Package* package);
  /**
   * @brief Checks if the drone is available
   * @return bool True if the drone is available, false otherwise
  */
  bool isAvailable();

  AuctionDrone(const JsonObject& obj) : Drone(obj) {}
  private:
  
};

#endif // AUCTIONDRONE_H_