#include "player.hpp"
#include "string.h"
using namespace ariel;

/*
* Outline implementation of Player
*/

Player::Player()
{
    Player("");
}

Player::Player(std::string player_name)
{
    this->player_name = player_name;
}

Player::~Player()
{

}

// Dummy implementation of the functions below:

int Player::stacksize() const
{
    return -1;
}

int Player::cardesTaken() const
{
    return -1;
}
