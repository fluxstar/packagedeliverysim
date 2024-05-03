#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <set>
#include <string>

#include "IObserver.h"

class IPublisher {
 public:
 /**
   * @brief Add an observer to the list of subscribers for the publisher.
   *
   * @param o a pointer to the observer object to add to the subscriber list
   */
  void addObserver(const IObserver* o);

  /**
   * @brief Remove an observer from the list of subscribers for the publisher.
   *
   * @param o a pointer to the observer object to remove from the subscriber list
   */
  void removeObserver(const IObserver* o);

  /**
   * @brief Send a message to the observers that are subscribed to the object.
   *
   * @param message a string containing the message to be sent to the subscribers
   */
  void notifyObservers(const std::string& message) const;

  virtual ~IPublisher() = default;

 private:
  std::set<const IObserver*> observers;
};

#endif  // IPUBLISHER_H_
