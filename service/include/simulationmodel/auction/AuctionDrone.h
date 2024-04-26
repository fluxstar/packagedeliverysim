#ifndef AUCTIONDRONE_H_
#define AUCTIONDRONE_H_

#include "Drone.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"
#include "AstarStrategy.h"
#include "DfsStrategy.h"
#include "BfsStrategy.h"
#include "DijkstraStrategy.h"
#include "BeelineStrategy.h"
#include "Package.h"
#include "SimulationModel.h"
#include "IEntityDecorator.h"

//--------------------  AuctionDrone ----------------------------

/**
 * @brief Class AuctionDrone wraps Drone to interface with the auctioneer
**/
class AuctionDrone : public IEntityDecorator<Drone> {
 public:
  AuctionDrone(Drone* drone) : IEntityDecorator<Drone>(drone) {}
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

  void update(double dt);
  void setDestination(IStrategy* strategy);
  void setToPackage(IStrategy* strategy);
  IStrategy* getToPackage();
  bool hasPickedUp();
  void setAvailable(bool available);
  void setPickedUp(bool pickedUp);
  Package* getPackage();
  void setPackage(Package* package);
  IStrategy* getToFinalDestination();

  private:
  
};

#endif // AUCTIONDRONE_H_