#pragma once

#include <string>

namespace ariel
{
    class Player
    {
    private:
        std::string player_name;
    public:
        Player();
        Player(std::string);
        ~Player();
        // Const prevents function from modify the pointer this and its values
        int stacksize() const;
        int cardesTaken() const;
    };
}