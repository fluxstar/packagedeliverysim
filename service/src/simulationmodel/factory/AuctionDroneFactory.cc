#include "AuctionDroneFactory.h"

IEntity* AuctionDroneFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("drone") == 0) {
    std::cout << "AuctionDrone created" << std::endl;
    return new AuctionDrone(entity);
  }
  return nullptr;
}
