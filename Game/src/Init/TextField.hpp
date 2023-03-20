/*
** EPITECH PROJECT, 2023
** TextField.hpp
** File description:
** TextField
*/

#ifndef TEXTFIELD_HPP_
#define TEXTFIELD_HPP_
#include <iostream>
#include "raylib.h"

class TextField {
    public:
        TextField(const std::string text, float, float);
        ~TextField();
        std::string CheckCollisionTextField(Vector2);
        void draw();

    protected:
    private:
        std::string name;
        Rectangle textfield;
        bool mouseOnText;
        int framesCounter;
        int letterCount;
        std::string _text;
        float _pos_x;
        float _pos_y;
};

#endif /* !TEXTFIELD_HPP_ */
