/*
** EPITECH PROJECT, 2023
** Test
** File description:
** InitTexture
*/

#include "InitTexture.hpp"
#include <iostream>

//! Constructor of InitTexture
InitTexture::InitTexture(std::string name)
{
    try {
        _name = name;
        texture = LoadTexture(name.c_str());
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        exit(84);
    }
}

//! Destructor of InitTexture
InitTexture::~InitTexture()
{
    UnloadTexture(texture);
}

//! Draw the texture
void InitTexture::draw(Vector2 pos)
{
    DrawTexture(texture, (int)pos.x, (int)pos.y, WHITE);
}

//! Draw the texture with scale
void InitTexture::draw(Vector2 pos, float scale)
{
    DrawTextureEx(texture, pos, 0.0f,  scale, WHITE);
}

//! Draw a part of a texture defined by a rectangle
void InitTexture::draw(Rectangle sourceRec, Rectangle btnBounds)
{
    DrawTextureRec(texture, sourceRec, (Vector2){btnBounds.x, btnBounds.y}, WHITE);
}

//! Copy the other InitTexture with text = tex form
InitTexture &InitTexture::operator=(const InitTexture &newTex)
{
    _name = newTex._name;
    texture = newTex.texture;
    std::cout << file << std::endl;
    return *this;
}