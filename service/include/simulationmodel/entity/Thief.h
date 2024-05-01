#ifndef THIEF_H_
#define THIEF_H_

#include "IEntity.h"
#include "IStrategy.h"
#include "Human.h"
#include "Package.h"
#include "IObserver.h"

class Thief : public Human, public IObserver {
 public:
  /**
   * @brief Thieves are created with a name
   * @param obj JSON object containing the thief's information
   */
  Thief(const JsonObject& obj);

  ~Thief();

  void update(double dt);

  void notify(const std::string& message, const IPublisher* sender) const override;

 protected:
  mutable std::set<Package*> availablePackages;

};

#endif
