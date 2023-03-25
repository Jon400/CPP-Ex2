#include "player.hpp"
#include "game.hpp"
#include <iostream>
using namespace ariel;

/*
* Outline implementation of Game
*/

Game::Game(ariel::Player p1, ariel::Player p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

Game::~Game()
{

}

// Dummy implementation of the functions below:
void Game::playTurn()
{
    return;
}
void Game::printLastTurn() const
{
    return;
}
void Game::playAll()
{
    return;
}
void Game::printWiner() const
{
    return;
}
void Game::printLog() const
{
    return;
}
void Game::printStats() const
{
    return;
}


