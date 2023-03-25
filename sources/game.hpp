#pragma once
#include "player.hpp"

namespace ariel
{
    class Game
    {
    private:
        ariel::Player p1, p2;
    public:
        Game(ariel::Player, ariel::Player);
        ~Game();
        // Const prevents function from modify the pointer this and its values
        void playTurn();
        void printLastTurn() const;
        void playAll();
        void printWiner() const;
        void printLog() const;
        void printStats() const;
    };    
}