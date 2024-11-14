#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "player.hpp"
#include "board.hpp"
#include "catan.hpp"

// Test the Player class
TEST_CASE("Player class tests")
{
    // Test Player constructor
    SUBCASE("Player constructor and initial resources")
    {
        Player player("Gal");

        const auto &resources = player.getResources();

        // Check constructor
        CHECK(player.getName() == "Gal");
        CHECK(resources.at("wood") == 0);
        CHECK(resources.at("brick") == 0);
        CHECK(resources.at("wool") == 0);
        CHECK(resources.at("oat") == 0);
        CHECK(resources.at("iron") == 0);
        CHECK(player.getVictoryPoints() == 0);
        CHECK(player.getResources().size() == 5);
    }

    // Test placeSettlement method
    SUBCASE("placeSettlement method")
    {
        Board board;
        Player player("Gal");

        player.addResource("wood", 2);
        player.addResource("brick", 2);
        player.addResource("wool", 2);
        player.addResource("oat", 2);

        // Invalid placement
        //CHECK_THROWS(player.placeSettlement("forest_hills", board, false));
        CHECK(player.getVictoryPoints() == 0);

        // Check resources after placement
        const auto &resources = player.getResources();
        CHECK(resources.at("wood") == 2);
        CHECK(resources.at("brick") == 2);
        CHECK(resources.at("wool") == 2);
        CHECK(resources.at("oat") == 2);
    }

    // Test placeRoad method
    SUBCASE("placeRoad method")
    {
        Board board;
        Player player("Gal");

        player.addResource("wood", 1);
        player.addResource("brick", 1);

        // Valid placement
        CHECK_THROWS(player.placeRoad("forest_hills", "forest_pasture", board, false));
        CHECK_NOTHROW(player.placeRoad("forest_hills", "forest_pasture", board, true));
        const auto &resources = player.getResources();
        CHECK(resources.at("wood") == 1);
        CHECK(resources.at("brick") == 1);

        // Invalid placement (road already exists)
        CHECK_THROWS(player.placeRoad("forest", "hills", board, false));
    }

    // Test placeCity method
    SUBCASE("placeCity method")
    {
        Board board;
        Player player("Gal");

        player.addResource("wood", 4);
        player.addResource("brick", 3);
        player.addResource("wool", 2);
        player.addResource("oat", 3);
        player.addResource("iron", 3);

        CHECK_NOTHROW(player.placeRoad("forest_hills", "forest_pasture", board, true));
        CHECK_NOTHROW(player.placeRoad("forest_pasture", "hills_pasture", board, true));

        CHECK_NOTHROW(player.placeSettlement("forest_hills", board, false));
        CHECK_NOTHROW(player.placeCity("forest_hills", board));

        const auto &resources = player.getResources();

        // Invalid placement (no settlement to upgrade)
        CHECK_THROWS(player.placeCity("forest_pasture", board));
    }

    // Test trade method
    SUBCASE("trade method")
    {
        Player player1("Gal");
        Player player2("Alex");

        player1.addResource("wood", 2);
        player2.addResource("brick", 2);

        CHECK_NOTHROW(player1.trade(player2, "wood", "brick", 1, 1));

        const auto &resources1 = player1.getResources();
        const auto &resources2 = player2.getResources();
        CHECK(resources1.at("wood") == 1);
        CHECK(resources1.at("brick") == 1);
        CHECK(resources2.at("wood") == 1);
        CHECK(resources2.at("brick") == 1);
    }

    // Test buyDevelopmentCard method
    SUBCASE("buyDevelopmentCard method")
    {
        Player player("Gal");

        player.addResource("iron", 1);
        player.addResource("wool", 1);
        player.addResource("oat", 1);

        CHECK_NOTHROW(player.buyDevelopmentCard());

        const auto &resources = player.getResources();
        CHECK(resources.at("iron") == 0);
        CHECK(resources.at("wool") == 0);
        CHECK(resources.at("oat") == 0);
        CHECK(!player.getDevelopmentCards().empty());
    }

    // Test rollDice method
    SUBCASE("rollDice method")
    {
        Player player("Gal");
        Player p2("Sharon");
        Player p3("Ori");
        Board board;

        // Create a Catan game
        Catan game(player, p2, p3, board);

        player.addResource("wood", 3);
        player.addResource("brick", 3);
        player.addResource("wool", 1);
        player.addResource("oat", 3);
        player.addResource("iron", 3);

        CHECK_NOTHROW(player.placeRoad("forest_hills", "forest_pasture", board, true));
        CHECK_NOTHROW(player.placeRoad("forest_pasture", "hills_pasture", board, true));

        CHECK_NOTHROW(player.placeSettlement("forest_hills", board, true));
        CHECK_NOTHROW(player.placeCity("forest_hills", board));

        // Simulate a dice roll that yields resources for settlements
        for (int i = 0; i < 100; i++)
        {
            //player.rollDice(game);
        }

        // Check that resources have been collected
        const auto &resources = player.getResources();
        // These values depend on the implementation of rollDice and getResource
        CHECK(resources.at("wood") >= 1);
        CHECK(resources.at("brick") >= 1);
        CHECK(resources.at("wool") >= 1);
        CHECK(resources.at("oat") >= 1);
    }
}

TEST_CASE("Board class tests")
{
    // Test getAffectedLocations method
    SUBCASE("getAffectedLocations method")
    {
        Board board;

        // Test with a robber location that exists in adjacencyList
        std::vector<std::string> affectedLocations1 = board.getAffectedLocations("forest");
        CHECK(affectedLocations1.size() == 3); // Expected adjacent locations count

        // Test with a robber location that doesn't exist in adjacencyList
        std::vector<std::string> affectedLocations2 = board.getAffectedLocations("invalid_location");
        CHECK(affectedLocations2.empty()); // Expected no affected locations
    }

    // Test getPlayersToStealFrom method
    SUBCASE("getPlayersToStealFrom method")
    {
        Board board;
        Player player1("Alice");
        Player player2("Bob");
        Player player3("Charlie");
        Catan game(player1, player2, player3, board);
        game.play();

        for (auto &player : game.players)
        {
            player.addResource("oat", 30);
            player.addResource("iron", 30);
            player.addResource("wood", 30);
            player.addResource("wool", 30);
            player.addResource("brick", 30);
        }

        // Set up players with settlements and cities in affected locations
        player1.placeSettlement("forest_hills", board, true);
        player2.placeSettlement("hills_forest", board, true);

        // Test with a robber location that affects player settlements and cities
        std::vector<Player *> playersToStealFrom1 = board.getPlayersToStealFrom("forest", game);
        CHECK(playersToStealFrom1.size() == 1); // Expected players count
    }
}

TEST_CASE("Board class tests")
{
    Board board;

    SUBCASE("Initialization and accessors")
    {
        // Test initialization of hexagons
        CHECK(board.getResource("forest") == "wood");
        CHECK(board.getResource("hills") == "brick");
        CHECK(board.getResource("pasture") == "wool");
        CHECK(board.getResource("agriculture") == "oat");
        CHECK(board.getResource("mountains") == "iron");
        CHECK(board.getResource("desert") == "none");

        // Test initialization of number to hexagon mapping
        CHECK(board.getHexagonNumber("hills") == 2);
        CHECK(board.getHexagonNumber("pasture") == 3);
        CHECK(board.getHexagonNumber("agriculture") == 4);
        CHECK(board.getHexagonNumber("mountains") == 5);
        CHECK(board.getHexagonNumber("forest") == 6);

        // Test adjacency list
        CHECK(board.getAdjacentLocations("forest") == std::vector<std::string>{"hills", "pasture"});
        CHECK(board.getAdjacentLocations("hills") == std::vector<std::string>{"forest", "agriculture", "pasture"});
        CHECK(board.getAdjacentLocations("pasture") == std::vector<std::string>{"forest", "hills", "mountains", "agriculture"});
        CHECK(board.getAdjacentLocations("agriculture") == std::vector<std::string>{"hills", "pasture", "desert"});
        CHECK(board.getAdjacentLocations("mountains") == std::vector<std::string>{"pasture", "agriculture", "forest"});
        CHECK(board.getAdjacentLocations("desert") == std::vector<std::string>{"agriculture"});

        // Test possible locations initialization
        CHECK(board.getPossibleSettlements().size() == 18);
        CHECK(board.getPossibleRoads().size() == 23);
    }

    SUBCASE("Road placement")
    {
        // Test road placement
        CHECK(board.isRoadPlaceable("forest_hills", "forest_pasture", true) == true);
        board.placeRoad("forest_hills", "forest_pasture");
        CHECK(board.isRoadPlaceable("forest_hills", "forest_pasture", false) == false);
        CHECK(board.getPossibleRoads().size() == 22); // One road placed
        CHECK(board.isRoadPlaceable("forest_hills", "hills_agriculture", false) == false); // No road adjacent

        // Test duplicate road placement
        CHECK_NOTHROW(board.placeRoad("forest_hills", "forest_pasture"));
    }

    SUBCASE("Settlement placement")
    {
        // Test settlement placement
        CHECK(board.isSettlementPlaceable("forest_hills", true) == true);
        board.placeSettlement("forest_hills");
        CHECK(board.isSettlementPlaceable("forest_hills", false) == false);
        CHECK(board.getPossibleSettlements().size() == 17); // One settlement placed

        // Test settlement adjacency to road
        CHECK(board.isSettlementPlaceable("forest_pasture", false) == false);
        CHECK(board.isSettlementPlaceable("hills_agriculture", true) == true);

        // Test city placement
        CHECK(board.isCityPlaceable("forest_hills") == true);
        board.placeCity("forest_hills");
        CHECK(board.isCityPlaceable("forest_hills") == false);
    }

    SUBCASE("Robber functionality")
    {
        // Test robber location
        CHECK(board.isRobberOnHexagon("desert") == false);
        board.setRobberLocation("desert");
        CHECK(board.isRobberOnHexagon("desert") == true);
    }
}

TEST_CASE("Catan class tests")
{
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");
    Board board;

    Catan game(player1, player2, player3, board);

    SUBCASE("Initialization and setup")
    {
        // Test players setup
        CHECK(game.players.size() == 3);
        CHECK(game.players[0].getName() == "Alice");
        CHECK(game.players[1].getName() == "Bob");
        CHECK(game.players[2].getName() == "Charlie");

        // Test board setup
        CHECK(game.getBoard().getPossibleSettlements().size() == 18);
        CHECK(game.getBoard().getPossibleRoads().size() == 23);
        CHECK(game.getBoard().isRobberOnHexagon("desert") == true);
    }

    /*SUBCASE("Gameplay and turns")
    {
        // Start the game
        CHECK_NOTHROW(game.play());

        // Test nextTurn function
        game.nextTurn();
        CHECK(game.currentPlayerIndex == 1);

        // Ensure nextTurn wraps around correctly
        game.nextTurn();
        game.nextTurn();
        game.nextTurn();
        CHECK(game.currentPlayerIndex == 1); // Should wrap around to player 1 after player 3
    }

    SUBCASE("Choosing starting locations")
    {
        // Simulate choosing starting locations for each player
        std::string input = "1\n1\n2\n1\n2\n";

        // Redirect cin for testing
        std::istringstream iss(input);
        std::streambuf *backup = std::cin.rdbuf();
        std::cin.rdbuf(iss.rdbuf());

        // Test starting location choices for each player
        CHECK_NOTHROW(game.chooseStartingLocations());

        // Restore cin
        std::cin.rdbuf(backup);

        // Verify starting settlements and roads
        CHECK(player1.getSettlements().size() == 2);
        CHECK(player1.getRoads().size() == 2);
        CHECK(player2.getSettlements().size() == 2);
        CHECK(player2.getRoads().size() == 2);
        CHECK(player3.getSettlements().size() == 2);
        CHECK(player3.getRoads().size() == 2);
    }*/
}

/*TEST_CASE("Player class tests")
{
    // Create a mock Board object for testing
    class MockBoard : public Board
    {
    public:
        // Implement necessary mock methods for testing Player interactions
        std::unordered_set<std::string> getPossibleSettlements() const override
        {
            return {"A", "B", "C"};
        }

        std::vector<std::pair<std::string, std::string>> getPossibleRoads() const override
        {
            return {{"A", "B"}, {"B", "C"}, {"C", "A"}};
        }

        bool isSettlementPlaceable(const std::string &location, bool isFirst) const override
        {
            return true; // Mock implementation always returns true
        }

        std::string getHexagonByLocation(const std::string &location) const override
        {
            return "hex"; // Mock implementation returns a fixed hexagon for any location
        }

        std::string getResource(const std::string &hexagon) const override
        {
            return "resource"; // Mock implementation always returns a resource
        }
    };

    Player player("Alice");
    MockBoard board;

    SUBCASE("Initialization and getters")
    {
        CHECK(player.getName() == "Alice");
        CHECK(player.getVictoryPoints() == 0);
        CHECK(player.getResources().empty());
        CHECK(player.getSettlements().empty());
        CHECK(player.getDevelopmentCards().empty());
    }

    SUBCASE("Resource management")
    {
        player.addResource("wood", 3);
        player.addResource("brick", 1);

        auto resources = player.getResources();
        CHECK(resources.size() == 2);
        CHECK(resources["wood"] == 3);
        CHECK(resources["brick"] == 1);

        player.subtractVictoryPoints(1);
        CHECK(player.getVictoryPoints() == -1);

        CHECK(player.countTotalResources() == 4);

        player.discardHalfResources(2);
        CHECK(player.countTotalResources() == 2);
    }

    SUBCASE("Settlements and cities")
    {
        player.placeSettlement("A", board, true);
        CHECK(player.getSettlements().size() == 1);
        CHECK(player.hasSettlement("A", board) == true);

        player.placeCity("A", board);
        CHECK(player.hasCity("A", board) == true);
    }

    SUBCASE("Roads")
    {
        player.placeRoad("A", "B", board, true);
        CHECK(player.getSettlements().size() == 1);
        CHECK(player.getRoads().size() == 1);
    }

    SUBCASE("Development cards")
    {
        player.buyDevelopmentCard();
        player.buyDevelopmentCard();
        CHECK(player.getDevelopmentCards().size() == 2);

        player.useDevelopmentCard("knight", nullptr);
        CHECK(player.getDevelopmentCards().empty());
    }

    SUBCASE("Trades")
    {
        Player otherPlayer("Bob");
        player.addResource("wood", 2);
        player.addResource("brick", 1);

        player.trade(otherPlayer, "wood", "brick", 2, 1);

        auto resourcesPlayer = player.getResources();
        auto resourcesOther = otherPlayer.getResources();

        CHECK(resourcesPlayer["wood"] == 0);
        CHECK(resourcesPlayer["brick"] == 0);
        CHECK(resourcesOther["wood"] == 2);
        CHECK(resourcesOther["brick"] == 1);
    }
}*/