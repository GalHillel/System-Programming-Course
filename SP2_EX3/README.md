# Catan Game Simulation

This project is a simulation of the popular board game Catan, implemented in C++ using object-oriented programming principles. The simulation includes basic game mechanics such as dice rolling, resource management, building settlements, cities, and roads, as well as handling the robber's movement and resource stealing.

## Game Rules Implemented

1. **Setup Phase:**
   - Players take turns placing settlements and roads on the board.
   - Each settlement gives the player initial resources based on adjacent terrain types.

2. **Resource Management:**
   - Players collect resources (wood, brick, wool, oat, iron) based on dice rolls.
   - Resources are used to build settlements, cities, and roads.

3. **Building:**
   - Settlements and roads can be placed on valid board locations.
   - Settlements can be upgraded to cities with additional resources.

4. **Robber Mechanism:**
   - Rolling a 7 activates the robber, allowing the active player to move it and steal resources from adjacent players.

## Class Hierarchy

### `Board`
- Manages the game board, including hexagon placement and adjacency.
- Methods handle placement of settlements, cities, roads, and robber movements.

### `Player`
- Represents a player in the game.
- Manages resources, settlements, cities, roads, victory points, and actions such as building and discarding.

### `Catan`
- Orchestrates the overall game flow, including turn management, dice rolling, and interaction between players and the board.

## Implemented Methods

### `Board` Class Methods
- `placeSettlement(location)`: Places a settlement at the specified location.
- `placeCity(location)`: Upgrades a settlement to a city at the specified location.
- `placeRoad(startLocation, endLocation)`: Places a road between two specified locations.
- `setRobberLocation(newLocation)`: Moves the robber to a new hexagon location.
- `distributeResources(result, game)`: Distributes resources based on dice roll results.

### `Player` Class Methods
- `placeSettlement(location, board, isFirst)`: Places a settlement at a specified location on the board.
- `placeCity(location, board)`: Upgrades a settlement to a city at a specified location on the board.
- `placeRoad(startLocation, endLocation, board, isFirst)`: Places a road between two specified locations on the board.
- `rollDice(game)`: Rolls the dice and handles resource distribution or robber activation based on the result.
- `discardHalfResources(numToDiscard)`: Prompts the player to discard half of their resources when a 7 is rolled.
- `stealResource(targetPlayer)`: Steals a resource from a specified player adjacent to the robber's new location.

## Libraries Used

- **Standard Library:** `<iostream>`, `<algorithm>`, `<stdexcept>`, `<ctime>`, `<cstdlib>`, `<random>`
   - Used for basic input/output, algorithmic operations, error handling, random number generation, and utility functions.
