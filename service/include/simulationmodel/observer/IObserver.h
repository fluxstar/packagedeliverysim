#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <string>

class IPublisher;

class IObserver {
 public:
  /**
   * @brief Receive a message from a publisher that the IObserver is subscribed to.
   *
   * @param message the string message the publisher is sending
   * @param sender a pointer to the IPublisher entity sending the message
   */
  virtual void notify(const std::string& message,
                      const IPublisher* sender) const = 0;
};

#endif  // IOBSERVER_H_
