/*
** EPITECH PROJECT, 2023
** Test
** File description:
** InitTexture
*/

#include <string>
#include "raylib.h"

#ifndef INITTEXTURE_HPP_
#define INITTEXTURE_HPP_

//! Initiate the texture
class InitTexture {
    public:
        InitTexture(std::string);
        ~InitTexture();
        InitTexture() = default;
        InitTexture(const InitTexture&) = delete;
        InitTexture& operator=(const InitTexture&);

        void setTexture(const std::string& name){texture = LoadTexture(name.c_str());};
        void draw(Vector2, float);
        void draw(Vector2);
        void draw(Rectangle sourceRec, Rectangle btnBounds);
        int getWidth() const { return texture.width; }
        int getHeight() const { return texture.height; }
        std::string getName() const { return _name; }

    protected:
    private:
        std::string _name;
        std::string file;
        Texture2D texture;
};

#endif /* !INITTEXTURE_HPP_ */
