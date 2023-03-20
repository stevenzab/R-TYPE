/*
** EPITECH PROJECT, 2023
** Test
** File description:
**
*/


#include "Game.hpp"

//! Main of the game
int main(int ac, char** argv)
{
    if (ac != 2)
        return 84;
    Game init;
    init.start(argv[1]);
    return 0;
}