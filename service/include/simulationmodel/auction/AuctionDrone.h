#ifndef AUCTIONDRONE_H_
#define AUCTIONDRONE_H_

#include "Drone.h"
#include "Auctioneer.h"

class AuctionDrone : public Drone {
 public:
  void getNextDelivery() override;
  void setNextDelivery(Package* package);
  bool isAvailable();
};

#endif // AUCTIONDRONE_H_