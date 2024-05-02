#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "IEntity.h"
#include "IObserver.h"
#include "IStrategy.h"
#include "math/vector3.h"
#include "util/json.h"

class Package;

/**
 * @class Robot
 * @brief Represents a robot in a physical system
 *
 * Robots move using euler integration based on a specified
 * velocity and direction.
 */
class Robot : public IEntity, public IObserver {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the robot's information
   */
  Robot(const JsonObject& obj);

  /**
   * @brief Updates the Package
   *
   * @param dt difference in time since last update
   */
  void update(double dt);

  /**
   * @brief Receives the passed in package
   *
   * @param Package* Package to be received by the robot
   */
  void receive(Package* p);

  bool requestedDelivery = true;

  // const std::string& getStrategyName() const { return strategyName; }

  /**
   * @brief Receive a message from a publisher that the entity is subscribed to.
   *
   * @param message the string message the publisher is sending
   * @param sender a pointer to the IPublisher entity sending the message
   */
  void notify(const std::string& message,
              const IPublisher* sender) const override;

 protected:
  Package* package = nullptr;
  mutable Package* pickingUp = nullptr;
  mutable IStrategy* toPackage = nullptr;
  mutable JsonObject receipt;
  // mutable std::string strategyName;
};

#endif  // ROBOT_H
