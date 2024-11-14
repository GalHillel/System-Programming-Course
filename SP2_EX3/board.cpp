#include "board.hpp"
#include "player.hpp"
#include "catan.hpp"

/**
 * @brief Constructs a Board object and initializes the board and possible locations.
 */
Board::Board()
{
    initializeBoard();
    initializePossibleLocations();
    // std::srand(std::time(nullptr)); // Initialize random seed
}

/**
 * @brief Initializes the hexagons and their corresponding resources, numbers, and adjacency list.
 */
void Board::initializeBoard()
{
    // Initialize hexagons and their corresponding resources
    hexagons = {
        {"forest", "wood"},
        {"hills", "brick"},
        {"pasture", "wool"},
        {"agriculture", "oat"},
        {"mountains", "iron"},
        {"desert", "none"}};

    // Initialize number to hexagon mapping
    numberToHexagon = {
        {2, "hills"},
        {3, "pasture"},
        {4, "agriculture"},
        {5, "mountains"},
        {6, "forest"},
        {8, "hills"},
        {9, "pasture"},
        {10, "agriculture"},
        {11, "mountains"},
        {12, "forest"}};

    // Complete adjacency list for the Catan board
    adjacencyList = {
        {"forest", {"hills", "pasture"}},
        {"hills", {"forest", "agriculture", "pasture"}},
        {"pasture", {"forest", "hills", "mountains", "agriculture"}},
        {"agriculture", {"hills", "pasture", "desert"}},
        {"mountains", {"pasture", "agriculture", "forest"}},
        {"desert", {"agriculture"}}};
}

/**
 * @brief Initializes the possible locations for settlements and roads on the board.
 */
void Board::initializePossibleLocations()
{
    // Add all possible settlements
    possibleSettlements = {
        "forest_hills", "forest_pasture", "forest_mountains",
        "hills_forest", "hills_pasture", "hills_agriculture", "hills_mountains",
        "pasture_forest", "pasture_hills", "pasture_agriculture", "pasture_mountains",
        "agriculture_hills", "agriculture_pasture", "agriculture_mountains",
        "mountains_forest", "mountains_hills", "mountains_pasture", "mountains_agriculture"};

    // Add all possible roads
    possibleRoads = {
        {"forest_hills", "forest_pasture"}, {"forest_hills", "forest_mountains"}, {"forest_pasture", "forest_mountains"}, {"forest_pasture", "hills_pasture"}, {"forest_mountains", "hills_mountains"}, {"hills_forest", "hills_pasture"}, {"hills_forest", "hills_agriculture"}, {"hills_pasture", "hills_agriculture"}, {"hills_pasture", "hills_mountains"}, {"hills_agriculture", "hills_mountains"}, {"pasture_forest", "pasture_hills"}, {"pasture_forest", "pasture_mountains"}, {"pasture_hills", "pasture_agriculture"}, {"pasture_hills", "pasture_mountains"}, {"pasture_agriculture", "pasture_mountains"}, {"agriculture_hills", "agriculture_pasture"}, {"agriculture_hills", "agriculture_mountains"}, {"agriculture_pasture", "agriculture_mountains"}, {"mountains_forest", "mountains_hills"}, {"mountains_forest", "mountains_pasture"}, {"mountains_hills", "mountains_agriculture"}, {"mountains_hills", "mountains_pasture"}, {"mountains_agriculture", "mountains_pasture"}};

    // All possible cities are initially the same as possible settlements
    possibleCities = possibleSettlements;
}

/**
 * @brief Checks if a road can be placed between two locations.
 * @param startLocation The starting location of the road.
 * @param endLocation The ending location of the road.
 * @param isFirst Whether this is the first road being placed.
 * @return True if the road can be placed, false otherwise.
 */
bool Board::isRoadPlaceable(const std::string &startLocation, const std::string &endLocation, bool isFirst) const
{
    auto road = std::make_pair(startLocation, endLocation);
    if (roads.find(road) == roads.end() && possibleRoads.find(road) != possibleRoads.end())
    {
        if (isFirst)
        {
            return true;
        }

        // Road must be connected to an existing road, settlement, or city
        if (settlements.find(startLocation) != settlements.end() || settlements.find(endLocation) != settlements.end() ||
            cities.find(startLocation) != cities.end() || cities.find(endLocation) != cities.end())
        {
            return true;
        }

        for (const auto &existingRoad : roads)
        {
            if (existingRoad.first == startLocation || existingRoad.second == startLocation ||
                existingRoad.first == endLocation || existingRoad.second == endLocation)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Checks if a settlement can be placed at a location.
 * @param location The location to check.
 * @param isFirst Whether this is the first settlement being placed.
 * @return True if the settlement can be placed, false otherwise.
 */
bool Board::isSettlementPlaceable(const std::string &location, bool isFirst) const
{
    if (settlements.find(location) != settlements.end())
    {
        return false;
    }

    if (isFirst)
    {
        return true;
    }

    // Settlement must be adjacent to an existing road
    bool adjacentToRoad = false;
    for (const auto &road : roads)
    {
        if (road.first == location || road.second == location)
        {
            adjacentToRoad = true;
            break;
        }
    }
    if (!adjacentToRoad)
    {
        return false;
    }

    return meetsDistanceRule(location);
}

/**
 * @brief Checks if a city can be placed at a location.
 * @param location The location to check.
 * @return True if the city can be placed, false otherwise.
 */
bool Board::isCityPlaceable(const std::string &location) const
{
    // Cities must replace existing settlements
    return settlements.find(location) != settlements.end();
}

/**
 * @brief Places a road between two locations.
 * @param start The starting location of the road.
 * @param end The ending location of the road.
 */
void Board::placeRoad(const std::string &start, const std::string &end)
{
    roads.insert({start, end});
    possibleRoads.erase({start, end});
    possibleRoads.erase({end, start});
}

/**
 * @brief Places a settlement at a specified location.
 * @param location The location where the settlement is to be placed.
 */
void Board::placeSettlement(const std::string &location)
{
    settlements.insert(location);
    possibleSettlements.erase(location);
}

/**
 * @brief Places a city at a specified location.
 * @param location The location where the city is to be placed.
 */
void Board::placeCity(const std::string &location)
{
    settlements.erase(location);
    cities.insert(location);
    possibleCities.erase(location);
}

/**
 * @brief Calculates the longest road starting from a specific location.
 * @param location The starting location.
 * @param visited A set of visited locations to avoid cycles.
 * @return The length of the longest road.
 */
int Board::calculateLongestRoad(const std::string &location, std::unordered_set<std::string> &visited) const
{
    // Recursive function to calculate the length of the longest road starting from a given location
    visited.insert(location);
    int maxLength = 0;
    for (const auto &adj : getAdjacentLocations(location))
    {
        if (visited.find(adj) == visited.end() && roads.find({location, adj}) != roads.end())
        {
            maxLength = std::max(maxLength, 1 + calculateLongestRoad(adj, visited));
        }
    }
    visited.erase(location);
    return maxLength;
}

/**
 * @brief Gets adjacent locations to a specified location.
 * @param location The location to check.
 * @return A vector of adjacent locations.
 */
std::vector<std::string> Board::getAdjacentLocations(const std::string &location) const
{
    auto it = adjacencyList.find(location);
    if (it != adjacencyList.end())
    {
        return it->second;
    }
    return {};
}

/**
 * @brief Checks if a location meets the distance rule for settlements.
 * @param location The location to check.
 * @return True if the location meets the distance rule, false otherwise.
 */
bool Board::meetsDistanceRule(const std::string &location) const
{
    for (const auto &adj : getAdjacentLocations(location))
    {
        if (settlements.find(adj) != settlements.end() || cities.find(adj) != cities.end())
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Gets the hexagon associated with a specific location.
 * @param location The location to check.
 * @return The hexagon associated with the location.
 */
std::string Board::getHexagonByLocation(const std::string &location) const
{
    std::size_t pos = location.find('_');
    if (pos != std::string::npos)
    {
        return location.substr(0, pos);
    }
    return "";
}

/**
 * @brief Gets the number associated with a specific hexagon.
 * @param hexagon The hexagon to check.
 * @return The number associated with the hexagon, or -1 if not found.
 */
int Board::getHexagonNumber(const std::string &hexagon) const
{
    for (const auto &pair : numberToHexagon)
    {
        if (pair.second == hexagon)
        {
            return (pair.first - 6);
        }
    }
    return -1; // Return -1 if hexagon name not found
}

/**
 * @brief Gets the resource associated with a specific hexagon.
 * @param hexagon The hexagon to check.
 * @return The resource associated with the hexagon, or an empty string if not found.
 */
std::string Board::getResource(const std::string &hexagon) const
{
    auto it = hexagons.find(hexagon);
    if (it != hexagons.end())
    {
        return it->second;
    }
    return "";
}

/**
 * @brief Gets the locations affected by the robber's presence.
 * @param robberLocation The current location of the robber.
 * @return A vector of affected locations.
 */
std::vector<std::string> Board::getAffectedLocations(const std::string &robberLocation) const
{
    std::vector<std::string> affectedLocations;

    // Find robberLocation in adjacencyList
    auto it = adjacencyList.find(robberLocation);
    if (it != adjacencyList.end())
    {
        // Add robberLocation itself
        affectedLocations.push_back(robberLocation);

        // Add adjacent locations to affectedLocations
        for (const auto &adjacent : it->second)
        {
            affectedLocations.push_back(adjacent);
        }
    }

    return affectedLocations;
}

/**
 * @brief Gets the players who can be stolen from based on the robber's location.
 * @param robberLocation The current location of the robber.
 * @param game The game object containing player information.
 * @return A vector of pointers to players who can be stolen from.
 */
std::vector<Player *> Board::getPlayersToStealFrom(const std::string &robberLocation, Catan &game) const
{
    std::vector<Player *> playersToStealFrom;

    // Get affected locations (settlements and cities adjacent to robberLocation)
    auto affectedLocations = getAffectedLocations(robberLocation);

    // Loop through all players to find those who have settlements or cities in affectedLocations
    for (Player &player : game.players)
    {
        bool canSteal = false;
        for (const auto &location : affectedLocations)
        {
            // Check if the player has a settlement or city in this location
            if (player.hasSettlement(location, *this) || player.hasCity(location, *this))
            {
                canSteal = true;
                break;
            }
        }

        if (canSteal)
        {
            playersToStealFrom.push_back(&player);
        }
    }
    return playersToStealFrom;
}

/**
 * @brief Gets the possible settlement locations.
 * @return A set of possible settlement locations.
 */
std::unordered_set<std::string> Board::getPossibleSettlements() const
{
    return possibleSettlements;
}

/**
 * @brief Gets the possible road locations.
 * @return A set of possible road locations.
 */
std::unordered_set<std::pair<std::string, std::string>, Board::PairHash> Board::getPossibleRoads() const
{
    return possibleRoads;
}

/**
 * @brief Checks if the robber is on a specific hexagon.
 * @param hexagonLocation The location of the hexagon to check.
 * @return True if the robber is on the hexagon, false otherwise.
 */
bool Board::isRobberOnHexagon(const std::string &hexagonLocation) const
{
    return hexagonLocation == robberLocation;
}

/**
 * @brief Sets the location of the robber.
 * @param newLocation The new location of the robber.
 */
void Board::setRobberLocation(const std::string &newLocation)
{
    robberLocation = newLocation;
}
