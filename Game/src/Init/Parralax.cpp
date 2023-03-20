/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Parralax
*/

#include "Parralax.hpp"
#include <iostream>

//! Constructor of Parralax
Parralax::Parralax(float scroll, float move, std::string name) : _scroll(scroll), _move(move)
{
    texture.setTexture(name);
}

//! Destructor of Parralax
Parralax::~Parralax()
{
}

//! Do the operation to do the illusion of movement and draw the texture
void Parralax::draw()
{
    _scroll -= _move;

    if (_scroll <= -texture.getWidth() * 2)
        _scroll = 0;
    texture.draw((Vector2) {_scroll, 0}, 2.0f);
    texture.draw((Vector2) {texture.getWidth() * 2 + _scroll, 0}, 2.0f);
}