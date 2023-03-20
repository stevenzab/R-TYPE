/*
** EPITECH PROJECT, 2022
** Test
** File description:
** Player
*/

#include "System.hpp"

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

//! Create and manage a player
class Player : public Entity {
public:
	Player(Color Color, Vector2 pos, int id);
	~Player() = default;
	int _id;

private:
	Color _Color;
};

#endif /* !PLAYER_HPP_ */
