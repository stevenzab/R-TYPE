/*
** EPITECH PROJECT, 2022
** Test
** File description:
** Player
*/

#include "Player.hpp"

//! Constructor of Player. Take the color and the Id as the parameter
Player::Player(Color Color, Vector2 vector, int id)  {
    addComponent(new PositionComponent{vector.x, vector.y});
    addComponent(new LifeComponent{3});
    addComponent(new ShootComponent);
    _id = id;
    _Color = Color;
}