#ifndef AUCTIONDRONE_H_
#define AUCTIONDRONE_H_

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "Drone.h"
#include "IEntityDecorator.h"
#include "JumpDecorator.h"
#include "Package.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"

//--------------------  AuctionDrone ----------------------------

/**
 * @brief Class AuctionDrone wraps Drone to interface with the auctioneer
 **/
class AuctionDrone : public IEntityDecorator<Drone> {
 public:
  AuctionDrone(Drone* drone) : IEntityDecorator<Drone>(drone) {}
  /**
   * @brief overriden to perform nothing
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

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Sets the destination strategy for the drone
   * @param strategy IStrategy object
   */
  void setToFinalDestination(IStrategy* strategy);

  /**
   * @brief Sets the source strategy for the drone
   * @param strategy IStrategy object
   */
  void setToPackage(IStrategy* strategy);
  /**
   * @brief Gets the source strategy for the drone
   * @return IStrategy object
   */
  IStrategy* getToPackage();
  /**
   * @brief Checks if the drone has picked up a package
   * @return bool True if the drone has picked up a package, false otherwise
   */
  bool hasPickedUp();
  /**
   * @brief Sets the availability of the drone
   * @param available bool containing the availability of the drone
   */
  void setAvailable(bool available);
  /**
   * @brief Sets the picked up status of the drone
   * @param pickedUp bool containing the picked up status of the drone
   */
  void setPickedUp(bool pickedUp);
  /**
   * @brief Gets the package the drone is carrying
   * @return Package pointer to the package the drone is carrying
   */
  Package* getPackage();
  /**
   * @brief Sets the package the drone is carrying
   * @param package Package pointer to the package the drone is carrying
   */
  void setPackage(Package* package);
  /**
   * @brief Gets the destination strategy for the drone
   * @return IStrategy object
   */
  IStrategy* getToFinalDestination();

 private:
};

#endif  // AUCTIONDRONE_H_
