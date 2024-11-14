#include "player.hpp"
#include "catan.hpp"

Player::Player(std::string name) : name(std::move(name)), victoryPoints(0)
{
    resources = {{"wood", 0}, {"brick", 0}, {"wool", 0}, {"oat", 0}, {"iron", 0}};
}

void Player::placeSettlement(const std::string &location, Board &board, bool isFirst)
{
    if (!board.isSettlementPlaceable(location, true))
    {
        throw std::runtime_error("Invalid placement for settlement.");
    }
    if ((resources["wood"] >= 1 && resources["brick"] >= 1 && resources["wool"] >= 1 && resources["oat"] >= 1) || isFirst)
    {
        if (!isFirst)
        {
            resources["wood"]--;
            resources["brick"]--;
            resources["wool"]--;
            resources["oat"]--;
        }

        board.placeSettlement(location);
        settlements.push_back(location);
        addVictoryPoints(1);

        std::cout << "Settlement successfully placed at " << location << "." << std::endl;
    }
    else
    {
        throw std::runtime_error("Insufficient resources for settlement.");
    }
}

void Player::placeRoad(const std::string &startLocation, const std::string &endLocation, Board &board, bool isFirst)
{
    if (!board.isRoadPlaceable(startLocation, endLocation, isFirst))
    {
        throw std::runtime_error("Invalid placement for road.");
    }
    if ((resources["wood"] >= 1 && resources["brick"] >= 1) || isFirst)
    {
        if (!isFirst)
        {
            resources["wood"]--;
            resources["brick"]--;
        }
        board.placeRoad(startLocation, endLocation);
        roads.emplace_back(startLocation, endLocation);

        std::cout << "Road successfully placed from " << startLocation << " to " << endLocation << "." << std::endl;
    }
    else
    {
        throw std::runtime_error("Insufficient resources for road.");
    }
}

void Player::discardHalfResources(int numToDiscard)
{
    std::cout << name << ", you need to discard " << numToDiscard << " resources." << std::endl;
    std::cout << "Current resources:" << std::endl;
    printResources();

    int discardedCount = 0; // Counter to track total discarded resources

    while (discardedCount < numToDiscard)
    {
        std::string resource;
        int count;

        // Prompt the player to choose a resource and specify how many to discard
        std::cout << "Choose a resource to discard and how many (e.g., wood 1, or enter 'done' to stop discarding): ";
        std::cin >> resource;

        if (resource == "done")
        {
            break;
        }

        std::cin >> count;

        // Check if the player has the chosen resource
        auto it = resources.find(resource);
        if (it != resources.end() && it->second >= count && count > 0)
        {
            it->second -= count;
            discardedCount += count;
            std::cout << name << " discarded " << count << " " << resource << "." << std::endl;
        }
        else
        {
            std::cout << "You don't have enough " << resource << " to discard. Choose again." << std::endl;
        }
    }

    std::cout << "Remaining resources after discarding:" << std::endl;
    printResources();
}

bool Player::hasSettlement(const std::string &location, const Board &board)
{
    std::vector<std::string> newSettlements;

    // Iterate through current settlements
    for (auto &settlement : settlements)
    {
        // Extract the location part before the underscore ('_')
        std::string newLoc = settlement.substr(0, settlement.find('_'));

        // Add the extracted location to newSettlements vector
        newSettlements.push_back(newLoc);
    }

    for (const auto& settlement : newSettlements)
    {
        if (settlement == location)
        {
            return true;
        }
    }

    return false;
}

// Implementation of hasCity function
bool Player::hasCity(const std::string &location, const Board &board)
{
    std::vector<std::string> newCities;

    for (auto &city : cities)
    {
        std::string newLoc = city.substr(0, newLoc.find('_'));
        newCities.push_back(newLoc);
    }

    for (const auto& city : newCities)
    {
        if (city == location)
        {
            return true;
        }
    }
    return false;
}

void Player::placeCity(const std::string &location, Board &board)
{
    // Check if city placement is valid on the board
    if (!board.isCityPlaceable(location))
    {
        throw std::runtime_error("Invalid placement for city.");
    }

    // Check if the player has enough resources to build a city
    if (resources["oat"] >= 2 && resources["iron"] >= 3)
    {
        // Deduct resources for building the city
        resources["oat"] -= 2;
        resources["iron"] -= 3;

        // Place the city on the board
        board.placeCity(location);

        // Add the location to the cities vector
        cities.push_back(location);

        // Remove the location from settlements (assuming settlements is a vector or container)
        auto it = std::find(settlements.begin(), settlements.end(), location);
        if (it != settlements.end())
        {
            settlements.erase(it);
        }

        // Add victory points for placing a city
        addVictoryPoints(1);

        std::cout << "City successfully placed at " << location << "." << std::endl;
    }
    else
    {
        throw std::runtime_error("Insufficient resources for city.");
    }
}

void Player::rollDice(Catan &game)
{
    // Roll the dice
    int roll1 = std::rand() % 6 + 1;
    int roll2 = std::rand() % 6 + 1;
    int result = roll1 + roll2;
    std::cout << name << " rolled a " << roll1 << " + " << roll2 << " = " << result << std::endl;

    // Get the game board
    Board &board = game.getBoard();

    // Handling the case where the dice roll results in 7
    if (result == 7)
    {
        std::cout << "A 7 has been rolled! The robber activates." << std::endl;

        // Step 1: Players with more than 7 resource cards must discard half of their cards
        for (auto &player : game.players)
        {
            int numCards = player.countTotalResources();
            if (numCards > 7)
            {
                int cardsToDiscard = numCards / 2;
                if (numCards % 2 != 0)
                {
                    cardsToDiscard++; // Round up if there's an odd number of cards
                }
                player.discardHalfResources(cardsToDiscard);
                std::cout << "Player " << player.getName() << " discards " << cardsToDiscard << " resource cards." << std::endl;
            }
        }

        // Step 2: Prompt current player to choose a new hexagon location for the robber
        std::vector<std::string> hexagons = {"forest", "hills", "pasture", "agriculture", "mountains", "desert"};

        std::cout << "Choose a new hexagon location for the robber:" << std::endl;
        for (size_t i = 0; i < hexagons.size(); ++i)
        {
            std::cout << i + 1 << ". " << hexagons[i] << std::endl;
        }

        int choice;
        std::cout << "Enter your choice (1-" << hexagons.size() << "): ";
        std::cin >> choice;

        // Validate the choice
        if (choice >= 1 && choice <= static_cast<int>(hexagons.size()))
        {
            auto newRobberLocation = hexagons[static_cast<size_t>(choice - 1)]; // Ensure choice - 1 is within bounds
            // Move the robber to the chosen hexagon
            board.setRobberLocation(newRobberLocation);
            std::cout << "The robber is moved to " << newRobberLocation << "." << std::endl;

            // Step 3: Determine players to steal from
            std::vector<Player *> playersToStealFrom = board.getPlayersToStealFrom(newRobberLocation, game);
            if (playersToStealFrom.empty())
            {
                std::cout << "No players to steal from." << std::endl;
            }
            else
            {
                // Randomly choose a player to steal from
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<size_t> playerDist(0, playersToStealFrom.size() - 1);
                size_t playerIndex = playerDist(gen);
                auto *victim = playersToStealFrom[playerIndex];

                // Steal a random resource card from the victim
                const std::unordered_map<std::string, int> &victimResources = victim->getResources();
                if (!victimResources.empty())
                {
                    std::vector<std::string> victimResourceList;
                    for (const auto &pair : victimResources)
                    {
                        for (int i = 0; i < pair.second; ++i)
                        {
                            victimResourceList.push_back(pair.first);
                        }
                    }

                    if (!victimResourceList.empty())
                    {
                        std::uniform_int_distribution<size_t> resourceDist(0, victimResourceList.size() - 1);
                        size_t resourceIndex = resourceDist(gen);
                        auto stolenResource = victimResourceList[resourceIndex];
                        victim->addResource(stolenResource, -1); // Implement this method in Player class
                        resources[stolenResource]++;
                        std::cout << "Player " << name << " steals " << stolenResource << " from Player " << victim->getName() << "." << std::endl;
                    }
                }
            }
        }
        else
        {
            std::cout << "Invalid choice. The robber remains in its current location." << std::endl;
        }
    }
    else
    {
        // Non-7 roll: Collect resources based on the rolled number
        for (const auto &settlement : settlements)
        {
            std::string hexagon = board.getHexagonByLocation(settlement);
            if (board.getHexagonNumber(hexagon) == result && !board.isRobberOnHexagon(hexagon))
            {
                std::string resource = board.getResource(hexagon);
                if (!resource.empty())
                {
                    resources[resource]++;
                    std::cout << name << " collected " << resource << " from settlement at " << settlement << std::endl;
                }
            }
        }

        for (const auto &city : cities)
        {
            std::string hexagon = board.getHexagonByLocation(city);
            if (board.getHexagonNumber(hexagon) == result && !board.isRobberOnHexagon(hexagon))
            {
                std::string resource = board.getResource(hexagon);
                if (!resource.empty())
                {
                    resources[resource] += 2; // Cities collect double resources
                    std::cout << name << " collected 2 " << resource << " from city at " << city << std::endl;
                }
            }
        }
    }
}

void Player::trade(Player &other, const std::string &giveResource, const std::string &receiveResource, int giveAmount, int receiveAmount)
{
    if (resources[giveResource] >= giveAmount && other.resources[receiveResource] >= receiveAmount)
    {
        resources[giveResource] -= giveAmount;
        resources[receiveResource] += receiveAmount;
        other.resources[giveResource] += giveAmount;
        other.resources[receiveResource] -= receiveAmount;
        std::cout << name << " traded " << giveAmount << " " << giveResource << " for " << receiveAmount << " " << receiveResource << " with " << other.getName() << std::endl;
    }
    else
    {
        throw std::runtime_error("Insufficient resources for trade.");
    }
}

void Player::confirmTrade(Player &other, const std::string &giveResource, const std::string &receiveResource, int giveAmount, int receiveAmount)
{
    std::cout << other.getName() << ", do you accept the trade? (y/n): ";
    char choice;
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        trade(other, giveResource, receiveResource, giveAmount, receiveAmount);
    }
    else
    {
        std::cout << other.getName() << " declined the trade." << std::endl;
    }
}

void Player::buyDevelopmentCard()
{
    if (resources["iron"] >= 1 && resources["wool"] >= 1 && resources["oat"] >= 1)
    {
        resources["iron"]--;
        resources["wool"]--;
        resources["oat"]--;
        std::vector<std::string> developmentCardTypes = {"Promotion - Monopoly", "Promotion - Building Roads", "Promotion - Year of Plenty", "Knight", "Victory Point"};
        auto randomIndex = static_cast<size_t>(std::rand()) % developmentCardTypes.size();

        std::string cardType = developmentCardTypes[randomIndex];
        developmentCards.push_back(cardType);
        std::cout << name << " bought a development card of type: " << cardType << std::endl;
    }
    else
    {
        std::cerr << "Insufficient resources to buy a development card." << std::endl;
    }
}

void Player::useDevelopmentCard(const std::string &card, Catan &game)
{
    auto it = std::find(developmentCards.begin(), developmentCards.end(), card);
    if (it != developmentCards.end())
    {
        if (card == "Promotion - Monopoly")
        {
            // Monopoly: Choose a resource and get all of it from other players
            std::cout << "Choose a resource for Monopoly (wood, brick, wool, oat, iron): ";
            std::string chosenResource;
            std::cin >> chosenResource;

            for (auto &player : game.players)
            {
                if (player.getName() != name)
                {
                    resources[chosenResource] += player.resources[chosenResource];
                    player.resources[chosenResource] = 0;
                }
            }
            std::cout << name << " used Monopoly to collect " << chosenResource << " from other players." << std::endl;
        }
        else if (card == "Promotion - Building Roads")
        {
            std::cout << "You can build 2 roads at no cost." << std::endl;

            for (int i = 0; i < 2; ++i)
            {
                std::cout << name << ", choose location for road " << i + 1 << ":" << std::endl;

                // Display available road locations
                auto possibleRoads = game.getBoard().getPossibleRoads();
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
                std::advance(it, choiceIndex - 1);
                std::pair<std::string, std::string> chosenRoad = *it;

                try
                {
                    placeRoad(chosenRoad.first, chosenRoad.second, game.getBoard(), true);
                    std::cout << "Built road from " << chosenRoad.first << " to " << chosenRoad.second << std::endl;
                }
                catch (const std::runtime_error &e)
                {
                    std::cerr << e.what() << std::endl;
                    --i; // Retry the same index
                    continue;
                }

                // Remove the chosen road from possible options
                possibleRoads.erase(it);
            }
        }
        else if (card == "Promotion - Year of Plenty")
        {
            // Year of Plenty: Receive any 2 resources from the bank
            std::cout << "Choose first resource to receive from the bank (wood, brick, wool, oat, iron): ";
            std::string resource1;
            std::cin >> resource1;
            resources[resource1]++;
            std::cout << name << " received one " << resource1 << " from the bank." << std::endl;
            std::cout << "Choose second resource to receive from the bank (wood, brick, wool, oat, iron): ";
            std::string resource2;
            std::cin >> resource2;
            resources[resource2]++;
            std::cout << name << " received one " << resource2 << " from the bank." << std::endl;
            std::cout << name << " used Year of Plenty to receive 2 resources from the bank." << std::endl;
        }
        else if (card == "Knight")
        {
            knightCardCount++;
            std::cout << name << " used a Knight card." << std::endl;
            if (knightCardCount >= 3)
            {
                // Check if the player has the largest army
                if (game.largestArmyOwner == nullptr || knightCardCount > game.largestArmyOwner->knightCardCount)
                {
                    if (game.largestArmyOwner != nullptr)
                    {
                        game.largestArmyOwner->subtractVictoryPoints(2);
                    }
                    game.largestArmyOwner = this;
                    addVictoryPoints(2);
                    std::cout << name << " now has the largest army and gained 2 victory points." << std::endl;
                }
            }

            // Knight card: Move the robber
            std::vector<std::string> hexagons = {"forest", "hills", "pasture", "agriculture", "mountains", "desert"};

            std::cout << "Choose a new hexagon location for the robber:" << std::endl;
            for (size_t i = 0; i < hexagons.size(); ++i)
            {
                std::cout << i + 1 << ". " << hexagons[i] << std::endl;
            }

            int choice;
            std::cout << "Enter your choice (1-" << hexagons.size() << "): ";
            std::cin >> choice;

            // Validate the choice
            if (choice >= 1 && choice <= static_cast<int>(hexagons.size()))
            {
                auto newRobberLocation = hexagons[static_cast<size_t>(choice - 1)]; // Ensure choice - 1 is within bounds
                // Move the robber to the chosen hexagon
                game.getBoard().setRobberLocation(newRobberLocation);
                std::cout << "The robber is moved to " << newRobberLocation << "." << std::endl;

                // Step 3: Determine players to steal from
                std::vector<Player *> playersToStealFrom = game.getBoard().getPlayersToStealFrom(newRobberLocation, game);
                if (playersToStealFrom.empty())
                {
                    std::cout << "No players to steal from." << std::endl;
                }
                else
                {
                    // Randomly choose a player to steal from
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<size_t> playerDist(0, playersToStealFrom.size() - 1);
                    size_t playerIndex = playerDist(gen);
                    auto *victim = playersToStealFrom[playerIndex];

                    // Steal a random resource card from the victim
                    const std::unordered_map<std::string, int> &victimResources = victim->getResources();
                    if (!victimResources.empty())
                    {
                        std::vector<std::string> victimResourceList;
                        for (const auto &pair : victimResources)
                        {
                            for (int i = 0; i < pair.second; ++i)
                            {
                                victimResourceList.push_back(pair.first);
                            }
                        }

                        if (!victimResourceList.empty())
                        {
                            std::uniform_int_distribution<size_t> resourceDist(0, victimResourceList.size() - 1);
                            size_t resourceIndex = resourceDist(gen);
                            auto stolenResource = victimResourceList[resourceIndex];
                            victim->addResource(stolenResource, -1); // Implement this method in Player class
                            resources[stolenResource]++;
                            std::cout << "Player " << name << " steals " << stolenResource << " from Player " << victim->getName() << "." << std::endl;
                        }
                    }
                }
            }
            else
            {
                std::cout << "Invalid choice. The robber remains in its current location." << std::endl;
            }
        }
        else if (card == "Victory Point")
        {
            addVictoryPoints(1);
        }
        developmentCards.erase(it);
        std::cout << name << " used a development card of type: " << card << std::endl;

        // End turn automatically
        game.nextTurn();
    }
    else
    {
        throw std::runtime_error("Player does not have the specified development card.");
    }
}

void Player::printResources() const
{
    std::cout << "Resources for " << name << ":" << std::endl;
    for (auto it = resources.begin(); it != resources.end(); ++it)
    {
        std::cout << it->first << ": " << it->second;
        if (std::next(it) != resources.end())
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void Player::endTurn()
{
    std::cout << name << " ended their turn." << std::endl;
}

const std::string &Player::getName() const
{
    return name;
}

int Player::getVictoryPoints() const
{
    return victoryPoints;
}

void Player::addVictoryPoints(int points)
{
    victoryPoints += points;
}

void Player::subtractVictoryPoints(int points)
{
    victoryPoints -= points;
}

void Player::addResource(const std::string &resource, int amount)
{
    resources[resource] += amount;
}

const std::unordered_map<std::string, int> &Player::getResources() const
{
    return resources;
}

const std::vector<std::string> &Player::getDevelopmentCards() const
{
    return developmentCards;
}

const std::vector<std::string> &Player::getSettlements() const
{
    return settlements;
}

int Player::countTotalResources() const
{
    int total = 0;
    for (const auto &pair : resources)
    {
        total += pair.second;
    }
    return total;
}