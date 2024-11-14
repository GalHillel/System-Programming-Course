#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <random>
#include <utility>
#include "board.hpp"

// Forward declarations
class Catan;
class Board;

/**
 * @class Player
 * @brief Represents a player in the game of Catan.
 */
class Player
{
public:
    /**
     * @brief Constructs a Player object with a given name.
     * @param name The name of the player.
     */
    explicit Player(std::string name);

    /**
     * @brief Places a settlement for the player on the board.
     * @param location The location to place the settlement.
     * @param board The game board.
     * @param isFirst Indicates if this is the first settlement of the player.
     */
    void placeSettlement(const std::string &location, Board &board, bool isFirst);

    /**
     * @brief Places a road for the player on the board.
     * @param startLocation The start location of the road.
     * @param endLocation The end location of the road.
     * @param board The game board.
     * @param isFirst Indicates if this is the first road of the player.
     */
    void placeRoad(const std::string &startLocation, const std::string &endLocation, Board &board, bool isFirst);

    /**
     * @brief Upgrades a settlement to a city.
     * @param location The location of the settlement to upgrade.
     * @param board The game board.
     */
    void placeCity(const std::string &location, Board &board);

    /**
     * @brief Rolls the dice for the player's turn.
     * @param game The game instance.
     */
    void rollDice(Catan &game);

    /**
     * @brief Trades resources with another player.
     * @param other The other player.
     * @param giveResource The resource to give.
     * @param receiveResource The resource to receive.
     * @param giveAmount The amount of resource to give.
     * @param receiveAmount The amount of resource to receive.
     */
    void trade(Player &other, const std::string &giveResource, const std::string &receiveResource, int giveAmount, int receiveAmount);

    /**
     * @brief Buys a development card.
     */
    void buyDevelopmentCard();

    /**
     * @brief Uses a development card.
     * @param card The development card to use.
     * @param game The game instance.
     */
    void useDevelopmentCard(const std::string &card, Catan &game);

    /**
     * @brief Ends the player's turn.
     */
    void endTurn();

    /**
     * @brief Prints the player's resources.
     */
    void printResources() const;

    /**
     * @brief Confirms a trade with another player.
     * @param other The other player.
     * @param giveResource The resource to give.
     * @param receiveResource The resource to receive.
     * @param giveAmount The amount of resource to give.
     * @param receiveAmount The amount of resource to receive.
     */
    void confirmTrade(Player &other, const std::string &giveResource, const std::string &receiveResource, int giveAmount, int receiveAmount);

    /**
     * @brief Adds victory points to the player.
     * @param points The number of points to add.
     */
    void addVictoryPoints(int points);

    /**
     * @brief Subtracts victory points from the player.
     * @param points The number of points to subtract.
     */
    void subtractVictoryPoints(int points);

    /**
     * @brief Adds resources to the player.
     * @param resource The resource to add.
     * @param amount The amount of the resource to add.
     */
    void addResource(const std::string &resource, int amount);

    /**
     * @brief Gets the player's victory points.
     * @return The number of victory points.
     */
    int getVictoryPoints() const;

    /**
     * @brief Counts the total resources the player has.
     * @return The total number of resources.
     */
    int countTotalResources() const;

    /**
     * @brief Checks if the player has a settlement at a given location.
     * @param location The location to check.
     * @param board The game board.
     * @return True if the player has a settlement at the location, otherwise false.
     */
    bool hasSettlement(const std::string &location, const Board &board);

    /**
     * @brief Checks if the player has a city at a given location.
     * @param location The location to check.
     * @param board The game board.
     * @return True if the player has a city at the location, otherwise false.
     */
    bool hasCity(const std::string &location, const Board &board);

    /**
     * @brief Gets the player's resources.
     * @return A const reference to the player's resources.
     */
    const std::unordered_map<std::string, int> &getResources() const;

    /**
     * @brief Gets the player's development cards.
     * @return A const reference to the player's development cards.
     */
    const std::vector<std::string> &getDevelopmentCards() const;

    /**
     * @brief Gets the player's settlements.
     * @return A const reference to the player's settlements.
     */
    const std::vector<std::string> &getSettlements() const;

    /**
     * @brief Gets the player's name.
     * @return A const reference to the player's name.
     */
    const std::string &getName() const;

private:
    /**
     * @brief Discards half of the player's resources.
     * @param numToDiscard The number of resources to discard.
     */
    void discardHalfResources(int numToDiscard);

    int victoryPoints;       ///< The player's victory points.
    int knightCardCount = 0; ///< The number of knight cards the player has.

    std::string name;                                       ///< The player's name.
    std::unordered_map<std::string, int> resources;         ///< The player's resources.
    std::vector<std::string> settlements;                   ///< The player's settlements.
    std::vector<std::string> cities;                        ///< The player's cities.
    std::vector<std::pair<std::string, std::string>> roads; ///< The player's roads.
    std::vector<std::string> developmentCards;              ///< The player's development cards.
};

#endif