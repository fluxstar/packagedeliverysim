#ifndef THIEF_H_
#define THIEF_H_

#include "Human.h"
#include "IEntity.h"
#include "IObserver.h"
#include "IStrategy.h"
#include "Package.h"

class Thief : public Human, public IObserver {
 public:
  /**
   * @brief Thieves are created with a name
   * @param obj JSON object containing the thief's information
   * 
   * Thieves move around the map stealing packages that they are close to.
   */
  Thief(const JsonObject& obj);

  ~Thief();

  /**
   * @brief Updates the Thief
   *
   * @param dt difference in time since last update
   */
  void update(double dt);

  /**
   * @brief Receive a message from a publisher that the entity is subscribed to.
   *
   * @param message the string message the publisher is sending
   * @param sender a pointer to the IPublisher entity sending the message
   */
  void notify(const std::string& message,
              const IPublisher* sender) const override;

 protected:
  mutable std::set<Package*> availablePackages;
  mutable Package* stealing = nullptr;
};

#endif
