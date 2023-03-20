/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Game
*/

#include <iostream>
#include "raylib.h"
#include "Init/InitTexture.hpp"
#include "Init/Music.hpp"
#include "Init/Window.hpp"
#include "Gameplay/Entity.hpp"
#include "Gameplay/System.hpp"
#include "Gameplay/Player.hpp"
#include "Gameplay/MovementSystem.hpp"
#include "Client.hpp"
#include "../../Common/Message.hpp"


#ifndef GAME_HPP_
#define GAME_HPP_


//! Manage the game
class Game {
    public:
        Game() {};
        void start(std::string ip);
        void gameLoop(std::string ip);
    protected:
    private:

        // Client _client;
};

#endif /* !GAME_HPP_ */
