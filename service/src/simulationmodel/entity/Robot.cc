#include "Robot.h"

Robot::Robot(const JsonObject& obj) : IEntity(obj) {}

void Robot::update(double dt) {}

void Robot::receive(Package* p) { package = p; }

void Robot::notify(const std::string& message, const IPublisher* sender) const {
  std::cout << "Robot received message: " << message << std::endl;
}