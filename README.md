# Team 001-46 Final Drone Simulation Project

## Team 001-46 Members
- Logan Krant (KRANT115)
- Alexander Lovely (LOVEL170)
- Samuel Martin (MART6353)
- Wyatt Rasmussen (RASMU984)

## Project Overview
The goal of this project is to simulate a drone-based package delivery system on the University of Minnesota campus, including the ability to schedule deliveries using different path-finding algorithms and watch deliveries play out on an interactive 3D model of the campus. 

## Running the Simulation
Due to various dependencies, it is recommended that the project is run on a CSE lab machine. After accessing a lab machine and cloning the project enter the project directory and run the command:
```
make run -j
```
This command will build the project and start the server on the default port for the project,4041. Once the terminal prints 'starting server...', the simulation can be accessed at http://localhost:4041. 

## Simulation Functionality
Upon launching the simulation, the browser-based visualization will become available. In this simulation, a human, drone, and helicopter are all spawned. The user can use the keyboard and mouse the navigate the 3D map of campus and interact with the simulation. On the left side of the menu, the user can view logs posted by the various entities in the simulation. On the right side, there is a menu for controlling various aspects of the simulation. A change view option allows the user to select an entity to focus the simulation camera on, the simulation speed slider alters how fast the time is moving, the show all routes button overlays the map with a visualization of the entire routing graph, and buttons are present for scheduling deliveries, adding entities (humans, thieves, and drones), and stopping the simulation. 

When any of the add entity buttons are clicked, an entity of the corresponding type is added to the map and will begin running through its default behavior automatically. When the stop simulation is clicked, the server shuts down.

When schedule delivery is clicked, a menu appears where the user can name their delivery and the pathfinder strategy that is to be used by the delivery drone. To set the pick-up and drop-off locations for the package, the user must click on the simulation map twice, first to set the pick-up the location and the second for the drop-off. The locations will be highlighted with translucent beacons to indicate where the drone is set to go. When the delivery is submitted, all set data is sent to the server and a package is created at the pick-up location. A robot is created at a random spot on the map to represent the recipient of the delivery.

At this point, using an auctioneer system, an available drone is selected to carry out the delivery, using the pathfinding strategy previously chosen. The drone will move to the pick-up location and take the package to the drop-off location. When the package is dropped off, the recipient is alerted and will move to it. At this point, the drone is available for more deliveries.

While the package has been dropped off but not collected, any thief entity that gets near the package will see it and go to it. If a thief reaches a package before the robot does, the package is stolen. When the robot arrives at the site of the stolen package, the robot reorders the package and the same steps are carried out. If the robot arrives first, it successfully receives the package.

Multiple drones, thieves, and deliveries can be carried out simultaneously within the simulation. In addition to the entities that have important functionality in the simulation, the helicopter and human entities move around the map randomly.
. 
### Feature Addition: Auctioneer
This feature replaces the stock FIFO scheduling algorithm in SimulationModel with an Auctioneer that insteads holds auctions for multiple packages at once. This is interesting because it saves on distance that the drones need to travel, which in a real-world system would help decreace costs.

This adds to the existing work by extending the SimulationModel and Drone files and using a mediator inbetween them to house the Auctioneer. Due to this, there is nothing special the user needs to interact with the auctioneer as it is the new way that all scheduling occurs.

### Feature Addition: Porch Pirates

## Sprint Retrospective

## UML Diagrams

## Links
- Docker:
- YouTube:
