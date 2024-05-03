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

  void rescheduleTrip(JsonObject& details, Robot* receiver);

  void notify(const std::string& message, const IPublisher* sender) const;

  std::deque<Package*> scheduledDeliveries;

 protected:
  IController& controller;
  std::map<int, IEntity*> entities;
  std::set<int> removed;
  const routing::Graph* graph = nullptr;
  CompositeFactory entityFactory;
  
 private:
  Auctioneer* auctioneer = nullptr;
  SimulationModel* model;
};

#endif // AUCTIONSIMULATIONMODEL_H_