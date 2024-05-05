#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class Package;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(const JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the next delivery in the scheduler
   */
  virtual void getNextDelivery();

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief Sets the destination strategy for the drone
   * @param strategy IStrategy object
   */
  void setToFinalDestination(IStrategy* strategy);

  /**
   * @brief Gets the destination strategy for the drone
   * @return IStrategy object
   */
  IStrategy* getDestination();

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
   * @brief Checks if the drone is available
   * @return bool True if the drone is available, false otherwise
   */
  bool isAvailable();

  /**
   * @brief Checks if the drone has picked up a package
   * @return bool True if the drone has picked up a package, false otherwise
   */
  bool hasPickedUp();

  /**
   * @brief Sets the drone's availability
   * @param available True if the drone is available, false otherwise
   */
  void setAvailable(bool available);

  /**
   * @brief Sets the drone's picked up status
   * @param pickedUp True if the drone has picked up a package, false otherwise
   */
  void setPickedUp(bool pickedUp);

  /**
   * @brief Gets the drone's package
   * @return Package object
   */
  Package* getPackage();

  /**
   * @brief Sets the drone's package
   * @param package Package object
   */
  void setPackage(Package* package);

  /**
   * @brief Sets the next delivery package for the drone.
   * @param package A pointer to the package to be set as the next delivery.
   */
  void setNextDelivery(Package* package);

  /**
   * Retrieves the strategy used to get the drone to its final destination.
   *
   * @return A pointer to the IStrategy object representing the strategy for
   * getting to the final destination.
   */
  IStrategy* getToFinalDestination();

 private:
  bool available = false;
  bool pickedUp = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
};

#endif
