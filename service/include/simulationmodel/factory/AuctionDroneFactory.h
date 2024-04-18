#ifndef AUCTION_DRONE_FACTORY_H_
#define AUCTION_DRONE_FACTORY_H_

#include "DroneFactory.h"
#include "AuctionDrone.h"

/**
 *@brief AuctionDrone Factory to produce AuctionDrones class.
 **/
class AuctionDroneFactory : public DroneFactory {
 public:
  /**
   * @brief Destructor for AuctionDroneFactory class.
   **/
  virtual ~AuctionDroneFactory() {}

   /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif