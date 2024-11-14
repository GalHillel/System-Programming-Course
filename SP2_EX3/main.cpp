// Id: 211696521 Mail: galh2011@icloud.com
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "board.hpp"
#include "player.hpp"
#include "catan.hpp"

void printBoard(const Board &board)
{
    // Placeholder function to print the board
    std::cout << "Board status" << std::endl;
}

int main()
{
    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Player p1("Gal");
    Player p2("Sharon");
    Player p3("Ori");
    Board board;

    // Create a Catan game
    Catan catan(p1, p2, p3, board);
    catan.play();

    for (auto &player : catan.players)
    {
        player.addResource("oat", 30);
        player.addResource("iron", 30);
        player.addResource("wood", 30);
        player.addResource("wool", 30);
        player.addResource("brick", 30);
    }

    // Game loop
    while (true)
    {
        // Clear screen
        system("clear");

        // Print board
        // printBoard(catan.getBoard());

        // Iterate through each player's turn
        for (auto &player : catan.players)
        {
            std::cout << "----------------------------------------" << std::endl;
            std::cout << "It's " << player.getName() << "'s turn." << std::endl;
            std::cout << "----------------------------------------" << std::endl;

            // Roll the dice
            player.rollDice(catan);

            // Player actions
            bool endTurn = false;
            while (!endTurn)
            {
                std::cout << "Select an action:" << std::endl;
                std::cout << "1. Build Settlement" << std::endl;
                std::cout << "2. Build Road" << std::endl;
                std::cout << "3. Build City" << std::endl;
                std::cout << "4. Buy Development Card" << std::endl;
                std::cout << "5. Use Development Card" << std::endl;
                std::cout << "6. Trade with Other Players" << std::endl;
                std::cout << "7. End Turn" << std::endl;

                int choice;
                std::cin >> choice;

                switch (choice)
                {
                    // TODO:implement the robber
                case 1:
                {
                    std::cout << "Choose location to build settlement: " << std::endl;

                    // Display available settlement locations
                    auto possibleSettlements = catan.getBoard().getPossibleSettlements();
                    std::vector<std::string> validSettlements;
                    for (const auto &settlement : possibleSettlements)
                    {
                        if (catan.getBoard().isSettlementPlaceable(settlement, false))
                        {
                            validSettlements.push_back(settlement);
                        }
                    }

                    int index = 1;
                    for (const auto &settlement : validSettlements)
                    {
                        std::cout << index << ": " << settlement << std::endl;
                        ++index;
                    }
                    std::cout << std::endl;

                    int choiceIndex;
                    std::cin >> choiceIndex;

                    // Validate the chosen index
                    if (choiceIndex < 1 || static_cast<size_t>(choiceIndex) > validSettlements.size())
                    {
                        std::cout << "Invalid settlement choice. Try again." << std::endl;
                        break; // Exit the case if invalid choice
                    }

                    // Place the settlement for the player
                    auto chosenSettlement = validSettlements[static_cast<size_t>(choiceIndex) - 1];

                    try
                    {
                        player.placeSettlement(chosenSettlement, catan.getBoard(), false);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    break;
                }

                case 2:
                {
                    std::cout << "Choose location to build road: " << std::endl;

                    // Display available road locations
                    auto possibleRoads = catan.getBoard().getPossibleRoads();
                    std::vector<std::pair<std::string, std::string>> validRoads;
                    for (const auto &road : possibleRoads)
                    {
                        if (catan.getBoard().isRoadPlaceable(road.first, road.second, false))
                        {
                            validRoads.push_back(road);
                        }
                    }

                    int index = 1;
                    for (const auto &road : validRoads)
                    {
                        std::cout << index << ": " << road.first << " to " << road.second << std::endl;
                        ++index;
                    }
                    std::cout << std::endl;

                    int choiceIndex;
                    std::cin >> choiceIndex;

                    // Validate the chosen index
                    if (choiceIndex < 1 || static_cast<size_t>(choiceIndex) > validRoads.size())
                    {
                        std::cout << "Invalid road choice. Try again." << std::endl;
                        break; // Exit the case if invalid choice
                    }

                    // Place the road for the player
                    auto chosenRoad = validRoads[static_cast<size_t>(choiceIndex) - 1];

                    try
                    {
                        player.placeRoad(chosenRoad.first, chosenRoad.second, catan.getBoard(), false);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    break;
                }
                case 3:
                {
                    std::cout << "Enter location to build city: " << std::endl;

                    // Get player's settlements
                    auto settlements = player.getSettlements();

                    // Display available settlements for upgrading to city
                    int index = 1;
                    for (const auto &settlement : settlements)
                    {
                        std::cout << index << ": " << settlement << std::endl;
                        ++index;
                    }

                    int choiceIndex;
                    std::cin >> choiceIndex;

                    // Validate the chosen index
                    if (choiceIndex < 1 || choiceIndex > settlements.size())
                    {
                        std::cout << "Invalid settlement choice. Aborting city placement." << std::endl;
                        break;
                    }

                    // Place the city at the chosen settlement
                    auto it = settlements.begin();
                    std::advance(it, choiceIndex - 1);
                    std::string chosenSettlement = *it;

                    try
                    {
                        player.placeCity(chosenSettlement, catan.getBoard());
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                }
                break;
                case 4:
                    try
                    {
                        player.buyDevelopmentCard();
                    }
                    catch (const std::runtime_error &e)
                    {
                        std::cout << e.what() << std::endl;
                    }
                    break;
                case 5:
                    std::cout << "Select a development card to use:" << std::endl;
                    for (size_t i = 0; i < player.getDevelopmentCards().size(); ++i)
                    {
                        std::cout << i + 1 << ". " << player.getDevelopmentCards()[i] << std::endl;
                    }
                    {
                        size_t cardChoice;
                        std::cin >> cardChoice;
                        if (cardChoice > 0 && cardChoice <= static_cast<int>(player.getDevelopmentCards().size()))
                        {
                            player.useDevelopmentCard(player.getDevelopmentCards()[cardChoice - 1], catan);
                            endTurn = true; // Using a development card ends the turn
                        }
                        else
                        {
                            std::cout << "Invalid choice. Please try again." << std::endl;
                        }
                    }
                    break;
                case 6:
                    std::cout << "Select a player to trade with:" << std::endl;
                    for (size_t i = 0; i < catan.players.size(); ++i)
                    {
                        std::cout << i + 1 << ". " << catan.players[i].getName() << std::endl;
                        catan.players[i].printResources();
                    }
                    {
                        size_t tradeChoice;
                        std::cin >> tradeChoice;
                        if (tradeChoice > 0 && tradeChoice <= static_cast<int>(catan.players.size()))
                        {
                            Player &tradePlayer = catan.players[tradeChoice - 1];
                            std::string giveResource, receiveResource;
                            int giveAmount, receiveAmount;
                            std::cout << "Enter resource to give, amount, resource to receive, and amount: ";
                            std::cin >> giveResource >> giveAmount >> receiveResource >> receiveAmount;
                            player.confirmTrade(tradePlayer, giveResource, receiveResource, giveAmount, receiveAmount);
                        }
                        else
                        {
                            std::cout << "Invalid player choice." << std::endl;
                        }
                    }
                    break;
                case 7:
                    endTurn = true;
                    player.endTurn();
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
                }

                // Check for victory condition
                if (player.getVictoryPoints() >= 10)
                {
                    // Clear screen
                    system("clear");

                    // Print board
                    printBoard(catan.getBoard());

                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << player.getName() << " has won the game!" << std::endl;
                    std::cout << "----------------------------------------" << std::endl;
                    return 0; // End the game
                }
            }

            // Move to the next player
            catan.nextTurn();
        }
    }

    return 0;
}