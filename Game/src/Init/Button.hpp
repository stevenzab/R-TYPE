/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <iostream>
#include "InitTexture.hpp"
#include <functional>

//! Create a button
class Button {
    public:
        Button(std::string, float, float);
        ~Button();
        void drawButton();
        bool CheckCollisionButton(Vector2 mousePoint);

    protected:
    private:
        InitTexture button_texture;

        float frameHeight;
        Rectangle sourceRec;
        Rectangle btnBounds;
        bool btnAction;
        int btnState;

};

#endif /* !BUTTON_HPP_ */
