#ifndef AUCTIONDRONE_H_
#define AUCTIONDRONE_H_

#include "Drone.h"
#include "Auctioneer.h"

//--------------------  AuctionDrone ----------------------------

/**
 * @brief Class AuctionDrone wraps the Drone class and adds the ability to
 * ???????????????????????????????????????????????????????????????????????
**/
class AuctionDrone : public Drone {
 public:
  /**
   * @brief Gets the next delivery from the auctioneer
  */
  void getNextDelivery() override;
  /**
   * @brief Sets the next delivery for the drone
  */
  void setNextDelivery(Package* package);
  /**
   * @brief Checks if the drone is available
   * @return bool True if the drone is available, false otherwise
  */
  bool isAvailable();
};

#endif // AUCTIONDRONE_H_