#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"

class Human : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Human(const JsonObject& obj);

  ~Human();

  /**
   * @brief Updates the Human
   *
   * @param dt difference in time since last update
   */
  virtual void update(double dt);

 private:
  static Vector3 kellerPosition;
  bool atKeller = false;

 protected:
  mutable IStrategy* movement = nullptr;
};

#endif
