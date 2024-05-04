#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include <deque>
#include <map>
#include <set>

#include "CompositeFactory.h"
#include "Drone.h"
#include "Graph.h"
#include "IController.h"
#include "IEntity.h"
#include "IObserver.h"
#include "Robot.h"

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel : public IObserver {
 public:
  /**
   * @brief Default constructor that create the SimulationModel object
   **/
  SimulationModel(IController& controller);

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type Graph* contain the new graph for SimulationModel
   **/
  virtual void setGraph(const routing::Graph* graph);

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   *which entity to create
   **/
  virtual IEntity* createEntity(const JsonObject& entity);

  /**
   * @brief Removes entity with given ID from the simulation
   *
   * @param id of the entity to be removed
   */
  virtual void removeEntity(int id);

  /**
   * @brief Get the entities in the simulation
   * @return std::map<int, IEntity*> contain the entities in the simulation
   */
  virtual std::map<int, IEntity*> getEntities();
  virtual void addEntity(IEntity* entity);
  virtual void addToController(IEntity* entity);

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   *the detail of the trip being scheduled
   **/
  virtual void scheduleTrip(const JsonObject& details);

  /**
   * @brief Reschedules a trip for a given receiver robot.
   *
   * This function takes in a `JsonObject` to create the package and a pointer
   * to a `Robot` object representing the receiver robot. It reschedules the
   * trip based on the provided details.
   *
   * @param details The `JsonObject` containing the details of the package.
   * @param receiver A pointer to the `Robot` object representing the receiver
   * robot.
   */
  virtual void rescheduleTrip(JsonObject& details, Robot* receiver);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  virtual void update(double dt);

  /**
   * @brief Stops the simulation
   * @return Void
   **/
  virtual void stop();

  /**
   * @brief Returns the graph of the map
   *
   * @returns Graph* graph pointer
   */
  virtual const routing::Graph* getGraph() const;

  /**
   * @brief Get the controller
   * @return IController& containing the controller
   */
  virtual IController& getController();

  /**
   * @brief Get the entity factory
   * @return IEntityFactory& containing the entity factory
   */
  virtual IEntityFactory* getEntityFactory();

  /**
   * @brief Receives a notification from a publisher.
   *
   * This function sends notifications to the controller
   * to be displayed on the front end
   * and also notifies the thieves of available packages
   *
   * @param message The message being received.
   * @param publisher The publisher that triggered the notification.
   *
   */
  virtual void notify(const std::string& message, const IPublisher*) const;

  /**
   * @brief Get the scheduled deliveries
   * @return std::deque<Package*> containing the scheduled deliveries
   */
  virtual std::deque<Package*>& getScheduledDeliveries();

  std::deque<Package*> scheduledDeliveries;

 protected:
  IController& controller;
  std::map<int, IEntity*> entities;
  std::set<int> removed;
  void removeFromSim(int id);
  const routing::Graph* graph = nullptr;
  CompositeFactory entityFactory;
};

#endif
