/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** MoveSystem
*/

#ifndef MOVESYSTEM_HPP_
#define MOVESYSTEM_HPP_

#include "Player.hpp"
#include "Entity.hpp"
#include <math.h>

//! Manage the movement of the player
class MovementSystem : public System {
public:
	MovementSystem() {}
	Vector2 movePlayer(Vector2& vect, std::vector<Player> &players);

    protected:
    private:
};

#endif /* !MOVESYSTEM_HPP_ */
