#ifndef CATAN_HPP
#define CATAN_HPP

#include "player.hpp"
#include "board.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

/**
 * @class Catan
 * @brief Represents the Catan game, managing players, the game board, and game progression.
 */
class Catan
{
public:
    /**
     * @brief Constructs a Catan game instance with three players and a game board.
     * @param player1 The first player.
     * @param player2 The second player.
     * @param player3 The third player.
     * @param board The game board.
     */
    Catan(Player &player1, Player &player2, Player &player3, Board &board);

    /**
     * @brief Gets the game board.
     * @return A reference to the game board.
     */
    Board &getBoard();

    /**
     * @brief The player who currently has the largest army.
     */
    Player *largestArmyOwner;

    /**
     * @brief Advances the game to the next player's turn.
     */
    void nextTurn();

    /**
     * @brief Starts and plays the game.
     */
    void play();

    /**
     * @brief A vector containing all the players in the game.
     */
    std::vector<Player> players;

private:
    /**
     * @brief The game board.
     */
    Board &board;

    /**
     * @brief The index of the current player in the players vector.
     */
    size_t currentPlayerIndex;

    /**
     * @brief Allows players to choose their starting locations at the beginning of the game.
     */
    void chooseStartingLocations();
};

#endif