#include "catan.hpp"

/**
 * @struct PairHash
 * @brief A hash function for std::pair to be used in unordered containers.
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
 * @brief Constructs a Catan game instance with three players and a game board.
 * @param player1 The first player.
 * @param player2 The second player.
 * @param player3 The third player.
 * @param board The game board.
 */
Catan::Catan(Player &player1, Player &player2, Player &player3, Board &board) : currentPlayerIndex(0), largestArmyOwner(nullptr), board(board)
{
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);

    board.setRobberLocation("desert");
}

/**
 * @brief Starts and plays the game.
 * @throws std::runtime_error if the number of players is not exactly 3.
 */
void Catan::play()
{
    if (players.size() != 3)
    {
        throw std::runtime_error("This Catan game requires exactly 3 players.");
    }

    std::random_device rd;                // Obtain a random number from hardware
    std::default_random_engine eng(rd()); // Seed the generator

    std::shuffle(players.begin(), players.end(), eng); // Shuffle the players

    chooseStartingLocations();
}

/**
 * @brief Gets the game board.
 * @return A reference to the game board.
 */
Board &Catan::getBoard()
{
    return board;
}

/**
 * @brief Advances the game to the next player's turn.
 */
void Catan::nextTurn()
{
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

/**
 * @brief Allows players to choose their starting locations at the beginning of the game.
 */
void Catan::chooseStartingLocations()
{
    for (Player &player : players)
    {
        // Choosing roads
        for (int i = 0; i < 2; ++i)
        {
            std::cout << player.getName() << ", choose location for road " << i + 1 << ":" << std::endl;

            // Display available road locations
            auto possibleRoads = board.getPossibleRoads();
            int index = 1;
            for (const auto &road : possibleRoads)
            {
                std::cout << index << ": " << road.first << " to " << road.second << std::endl;
                ++index;
            }
            std::cout << std::endl;

            int choiceIndex;
            std::cin >> choiceIndex;

            // Validate the chosen index
            if (choiceIndex < 1 || choiceIndex > possibleRoads.size())
            {
                std::cout << "Invalid road choice. Try again." << std::endl;
                --i; // Retry the same index
                continue;
            }

            // Place the road for the player
            auto it = possibleRoads.begin();
            std::advance(it, choiceIndex - 1); // Move iterator to chosen index
            std::pair<std::string, std::string> chosenRoad = *it;

            try
            {
                player.placeRoad(chosenRoad.first, chosenRoad.second, board, true);
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << e.what() << std::endl;
                --i; // Retry the same index
                continue;
            }
        }

        // Choosing settlements
        for (int i = 0; i < 2; ++i)
        {
            std::cout << player.getName() << ", choose location for settlement " << i + 1 << ":" << std::endl;

            // Display available settlement locations
            std::unordered_set<std::string> validSettlements = board.getPossibleSettlements();
            std::vector<std::string> possibleSettlements;
            for (const auto &settlement : validSettlements)
            {
                if (getBoard().isSettlementPlaceable(settlement, false))
                {
                    possibleSettlements.push_back(settlement);
                }
            }
            int index = 1;
            for (const auto &settlement : possibleSettlements)
            {
                std::cout << index << ": " << settlement << std::endl;
                ++index;
            }
            std::cout << std::endl;

            int choiceIndex;
            std::cin >> choiceIndex;

            // Validate the chosen index
            if (choiceIndex < 1 || choiceIndex > possibleSettlements.size())
            {
                std::cout << "Invalid settlement choice. Try again." << std::endl;
                --i; // Retry the same index
                continue;
            }

            // Place the settlement for the player
            auto it = possibleSettlements.begin();
            std::advance(it, choiceIndex - 1); // Move iterator to chosen index
            std::string chosenSettlement = *it;

            try
            {
                player.placeSettlement(chosenSettlement, board, true);
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << e.what() << std::endl;
                --i; // Retry the same index
                continue;
            }

            // Give resources based on the location of the settlement
            std::string hexagon = board.getHexagonByLocation(chosenSettlement);
            std::string resource = board.getResource(hexagon);

            if (resource != "none")
            {
                player.addResource(resource, 1);
                std::cout << player.getName() << " collected " << resource << " from settlement at " << chosenSettlement << std::endl;
            }
        }

        player.addVictoryPoints(2); // Starting points for the initial settlements
    }
}
