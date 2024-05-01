#ifndef THIEF_H_
#define THIEF_H_

#include "IEntity.h"
#include "IStrategy.h"
#include "Human.h"

class Thief : public Human {
 public:
  /**
   * @brief Thieves are created with a name
   * @param obj JSON object containing the thief's information
   */
  Thief(const JsonObject& obj);

  ~Thief();

  void update(double dt);

};

#endif
