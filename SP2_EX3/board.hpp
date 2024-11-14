#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <utility>

class Player;
class Catan;

/**
 * @brief Class representing the game board in Catan.
 */
class Board
{
public:
    /**
     * @brief Hash function for pairs of strings.
     */
    struct PairHash
    {
        template <typename T, typename U>
        std::size_t operator()(const std::pair<T, U> &pair) const
        {
            return std::hash<T>()(pair.first) ^ std::hash<U>()(pair.second);
        }
    };

    /**
     * @brief Default constructor that initializes the board.
     */
    Board();

    /**
     * @brief Gets the number associated with a hexagon.
     * @param hexagon The hexagon whose number is to be retrieved.
     * @return The number of the hexagon.
     */
    int getHexagonNumber(const std::string &hexagon) const;

    /**
     * @brief Calculates the longest road starting from a specific location.
     * @param location The starting location.
     * @param visited A set of visited locations to avoid cycles.
     * @return The length of the longest road.
     */
    int calculateLongestRoad(const std::string &location, std::unordered_set<std::string> &visited) const;

    /**
     * @brief Initializes the board with hexagons and their numbers.
     */
    void initializeBoard();

    /**
     * @brief Initializes possible locations for settlements and roads.
     */
    void initializePossibleLocations();

    /**
     * @brief Places a road between two locations.
     * @param start The starting location of the road.
     * @param end The ending location of the road.
     */
    void placeRoad(const std::string &start, const std::string &end);

    /**
     * @brief Places a settlement at a specified location.
     * @param location The location where the settlement is to be placed.
     */
    void placeSettlement(const std::string &location);

    /**
     * @brief Places a city at a specified location.
     * @param location The location where the city is to be placed.
     */
    void placeCity(const std::string &location);

    /**
     * @brief Sets the location of the robber.
     * @param newLocation The new location for the robber.
     */
    void setRobberLocation(const std::string &newLocation);

    /**
     * @brief Checks if a road can be placed between two locations.
     * @param startLocation The starting location.
     * @param endLocation The ending location.
     * @param isFirst Whether this is the first road being placed.
     * @return True if the road can be placed, false otherwise.
     */
    bool isRoadPlaceable(const std::string &startLocation, const std::string &endLocation, bool isFirst) const;

    /**
     * @brief Checks if a settlement can be placed at a location.
     * @param location The location to check.
     * @param isFirst Whether this is the first settlement being placed.
     * @return True if the settlement can be placed, false otherwise.
     */
    bool isSettlementPlaceable(const std::string &location, bool isFirst) const;

    /**
     * @brief Checks if a city can be placed at a location.
     * @param location The location to check.
     * @return True if the city can be placed, false otherwise.
     */
    bool isCityPlaceable(const std::string &location) const;

    /**
     * @brief Checks if the robber is on a specified hexagon.
     * @param hexagonLocation The hexagon location to check.
     * @return True if the robber is on the hexagon, false otherwise.
     */
    bool isRobberOnHexagon(const std::string &hexagonLocation) const;

    /**
     * @brief Gets adjacent locations to a specified location.
     * @param location The location to check.
     * @return A vector of adjacent locations.
     */
    std::vector<std::string> getAdjacentLocations(const std::string &location) const;

    /**
     * @brief Gets the hexagon associated with a specific location.
     * @param location The location to check.
     * @return The hexagon associated with the location.
     */
    std::string getHexagonByLocation(const std::string &location) const;

    /**
     * @brief Gets the resource type of a hexagon.
     * @param hexagon The hexagon to check.
     * @return The resource type of the hexagon.
     */
    std::string getResource(const std::string &hexagon) const;

    /**
     * @brief Gets the locations affected by the robber.
     * @param robberLocation The location of the robber.
     * @return A vector of affected locations.
     */
    std::vector<std::string> getAffectedLocations(const std::string &robberLocation) const;

    /**
     * @brief Gets the players who can be stolen from at a specified location.
     * @param robberLocation The location of the robber.
     * @param game The game instance.
     * @return A vector of players who can be stolen from.
     */
    std::vector<Player *> getPlayersToStealFrom(const std::string &robberLocation, Catan &game) const;

    /**
     * @brief Gets the possible settlement locations.
     * @return A set of possible settlement locations.
     */
    std::unordered_set<std::string> getPossibleSettlements() const;

    /**
     * @brief Gets the possible road locations.
     * @return A set of possible road locations.
     */
    std::unordered_set<std::pair<std::string, std::string>, PairHash> getPossibleRoads() const;

private:
    std::unordered_map<std::string, std::string> hexagons;                           ///< Maps hexagons to their resource types
    std::unordered_map<int, std::string> numberToHexagon;                            ///< Maps numbers to hexagons
    std::unordered_map<std::string, std::vector<std::string>> adjacencyList;         ///< Adjacency list for locations
    std::unordered_set<std::string> possibleSettlements;                             ///< Possible settlement locations
    std::unordered_set<std::pair<std::string, std::string>, PairHash> possibleRoads; ///< Possible road locations
    std::unordered_set<std::string> possibleCities;                                  ///< Possible city locations
    std::unordered_set<std::pair<std::string, std::string>, PairHash> roads;         ///< Roads on the board
    std::unordered_set<std::string> settlements;                                     ///< Settlements on the board
    std::unordered_set<std::string> cities;                                          ///< Cities on the board

    /**
     * @brief Checks if a location meets the distance rule for settlements.
     * @param location The location to check.
     * @return True if the location meets the distance rule, false otherwise.
     */
    bool meetsDistanceRule(const std::string &location) const;

    std::string robberLocation; ///< Current location of the robber
};

#endif