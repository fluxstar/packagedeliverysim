#ifndef AUCTIONSIMULATIONMODEL_H_
#define AUCTIONSIMULATIONMODEL_H_

#include "Auctioneer.h"
#include "SimulationModel.h"

//--------------------  AuctionSimulationModel ----------------------------

/**
 * @brief Class AuctionSimulationModel wraps the SimulationModel class and overrides
 * the update method to handle the auction simulation, managing an Auctioneer object
 */
class AuctionSimulationModel : public SimulationModel {
 public:
  // using SimulationModel::SimulationModel; // inherit constructor

  /**
   * @brief Constructor that creates the AuctionSimulationModel object
   */
  AuctionSimulationModel(IController& controller);

  /**
   * @brief Constructor for AuctionSimulationModel that wraps the SimulationModel object
   */
  AuctionSimulationModel(SimulationModel* model);

  /**
   * @brief Destructor
   */
  ~AuctionSimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type Graph* contain the new graph for SimulationModel
   **/
  void setGraph(const routing::Graph* graph);

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   *which entity to create
   **/
  IEntity* createEntity(const JsonObject& entity);

  /**
   * @brief Removes entity with given ID from the simulation
   *
   * @param id of the entity to be removed
   */
  void removeEntity(int id);

  /**
   * @brief Get the entities in the simulation
   * @return std::map<int, IEntity*> contain the entities in the simulation
   */
  std::map<int, IEntity*> getEntities();

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   *the detail of the trip being scheduled
   **/
  void scheduleTrip(const JsonObject& details);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

  /**
   * @brief Stops the simulation
   * @return Void
   **/
  void stop();

  /**
   * @brief Returns the graph of the map
   *
   * @returns Graph* graph pointer
   */
  const routing::Graph* getGraph() const;

  
  /**
   * @brief Reschedules a package for a given receiver robot.
   *
   * This function takes a reference to a `JsonObject` containing package details and a pointer to a `Robot` object representing the receiver robot.
   * It reschedules the trip for the receiver robot based on the provided details.
   *
   * @param details The package details as a `JsonObject` reference.
   * @param receiver A pointer to the `Robot` object representing the receiver robot.
   */
  void rescheduleTrip(JsonObject& details, Robot* receiver);

  /**
   * @brief Notifies the subscribers of a message.
   *
   * This function is responsible for notifying the subscribers of a message. The message
   * is passed as a parameter along with the sender of the message. The subscribers will
   * receive the message and can perform any necessary actions based on the message content.
   *
   * @param message The message to be sent to the subscribers.
   * @param sender The sender of the message.
   */
  void notify(const std::string& message, const IPublisher* sender) const;

  /**
   * @brief Get the scheduled deliveries
   * @return std::deque<Package*> containing the scheduled deliveries
   */
  std::deque<Package*>& getScheduledDeliveries();

  std::deque<Package*> scheduledDeliveries;

 protected:
  IController& controller;
  std::set<int> removed;
  const routing::Graph* graph = nullptr;
  CompositeFactory entityFactory;
  
 private:
  Auctioneer* auctioneer = nullptr;
  SimulationModel* model;
};

#endif // AUCTIONSIMULATIONMODEL_H_