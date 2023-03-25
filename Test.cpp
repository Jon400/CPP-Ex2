#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
#include "doctest.h"
#include <iostream>
#include <sstream>
using namespace ariel;

TEST_CASE("Cards initializetion test")
{
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);

    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
    
}

TEST_CASE("Game prints not throwing objects validation in the begining of round of play")
{
    std::cout.clear();
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);
    CHECK_NOTHROW(game.printLastTurn());
    CHECK_NOTHROW(game.printWiner());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printStats());
}

TEST_CASE("Game prints content checking in the begining of round of play")
{
    // The following code uses buffer in order to track the prints which sent to to output file of the operational system
    // Source: https://truong.io/posts/capturing_stdout_for_c++_unit_testing.html
    std::stringstream buffer;
    std::streambuf* prevcoutbuf;
    std::string res = "";

    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);

    prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    game.printLastTurn();
    res = buffer.str();
    buffer.str("");
    std::cout.rdbuf(prevcoutbuf);
    CHECK(res == "");

    prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    game.printWiner();
    res = buffer.str();
    buffer.str("");
    std::cout.rdbuf(prevcoutbuf);
    CHECK(res == "");

    // Change redirection of stdout to the buffer
    prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    game.printLog();
    res = buffer.str();
    // To clear the buffer print from all characters
    buffer.str("");
    // Restore original buffer, to enable the prints of CHECK function
    std::cout.rdbuf(prevcoutbuf);
    CHECK(res == "");

    // Change redirection of stdout to the buffer
    prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    game.printStats();
    res = buffer.str();
    // To clear the buffer print from all characters
    buffer.str("");
    // Restore original buffer, to enable the prints of CHECK function
    std::cout.rdbuf(prevcoutbuf);
    CHECK(res == "");
}

TEST_CASE("First turn of play Test")
{
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);

    game.playTurn();
    CHECK(p1.stacksize() == 25);
    CHECK(p2.stacksize() == 25);
}

TEST_CASE("Five turns of play Test")
{
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);

    for (size_t i = 0; i < 5; i++)
    {
        game.playTurn();
    }
    CHECK(p1.stacksize() == 20);
    CHECK(p2.stacksize() == 20);
}

TEST_CASE("All turns of play Test")
{
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);

    game.playAll();

    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
    CHECK((p1.cardesTaken() + p2.cardesTaken()) == 52);
}

TEST_CASE("Invalid turn after Play All")
{
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);

    game.playAll();
    CHECK_THROWS(game.playTurn());
}

TEST_CASE("Play_ALL after Play All")
{
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);

    game.playAll();
    CHECK_THROWS(game.playAll());
}

TEST_CASE("Play all turns remained after 2 turns")
{
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);

    game.playTurn();
    game.playTurn();

    REQUIRE_NOTHROW(game.playAll());
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
    CHECK((p1.cardesTaken() + p2.cardesTaken()) == 52);
}


// Check there is a winner or draw
TEST_CASE("Winner or draw in the ending of the play Test")
{
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);
    std::stringstream buffer;
    std::streambuf* prevcoutbuf;
    std::string res = "";

    // In case of draw
    if (p1.cardesTaken() == p2.cardesTaken())
    {
        // Change redirection of stdout to the buffer
        prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
        game.printWiner();
        res = buffer.str();
        // To clear the buffer print from all characters
        buffer.str("");
        // Restore original buffer, to enable the prints of CHECK function
        std::cout.rdbuf(prevcoutbuf);
        CHECK(res == "");
    }
    // In case of winning
    else
    {
        // Change redirection of stdout to the buffer
        prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
        game.printWiner();
        res = buffer.str();
        // To clear the buffer print from all characters
        buffer.str("");
        // Restore original buffer, to enable the prints of CHECK function
        std::cout.rdbuf(prevcoutbuf);
        CHECK(res != "");
    }
}

// The probability of the left player to win at least one turn is almost one
TEST_CASE("Turn: Left player wins Test")
{
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);
    std::stringstream buffer;
    std::streambuf* prevcoutbuf;
    std::string res = "";

    while(p1.stacksize() > 0)
    {
        CHECK_NOTHROW(game.playTurn());
        // Change redirection of stdout to the buffer
        prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
        game.printLastTurn();
        res = buffer.str();
        // To clear the buffer print from all characters
        buffer.str("");
        // Restore original buffer, to enable the prints of CHECK function
        std::cout.rdbuf(prevcoutbuf);
        if(res.find("Tal") != std::string::npos)
        {
            CHECK(true);
            return;
        }
    }  
    CHECK(false);

}

// The probability of the right player to win at least one turn is almost one
TEST_CASE("Turn: Right player wins Test")
{
    Player p1("Tal");
    Player p2("May");
    Game game(p1, p2);
    int left_player_wins = -1;
    std::stringstream buffer;
    std::streambuf* prevcoutbuf;
    std::string res = "";

    while(p2.stacksize() > 0)
    {
        CHECK_NOTHROW(game.playTurn());
         // Change redirection of stdout to the buffer
        prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
        game.printLastTurn();
        res = buffer.str();
        // To clear the buffer print from all characters
        buffer.str("");
        // Restore original buffer, to enable the prints of CHECK function
        std::cout.rdbuf(prevcoutbuf);
        if(res.find("May") != std::string::npos)
        {
            CHECK(true);
            return;
        }
    }  
    CHECK(false);
}