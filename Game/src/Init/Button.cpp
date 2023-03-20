/*
** EPITECH PROJECT, 2023
** Button.cpp
** File description:
** Button
*/

#include "Button.hpp"

//! Constructor class Button that set btnAction, button_texture, frameHeight, sourceRec, btnBounds
Button::Button(std::string name, float x, float y)
{
    btnAction = false;
    button_texture.setTexture(name);
    frameHeight = (float)button_texture.getHeight()/2;
    sourceRec = { 0, 0, (float)button_texture.getWidth(), frameHeight };
    btnBounds = { x/2.0f - button_texture.getWidth()/2.0f, y/2.0f - button_texture.getHeight()/2/2.0f, (float)button_texture.getWidth(), frameHeight };
}

//! Deconstructor of class Button
Button::~Button()
{
}

//! draw the button
void Button::drawButton()
{
    button_texture.draw(sourceRec, btnBounds);
}

//! check the collision between the mouse and button and if it's clicked
bool Button::CheckCollisionButton(Vector2 mousePoint)
{
    btnAction = false;
    if (CheckCollisionPointRec(mousePoint, btnBounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    } else
        btnState = 0;
    if (btnAction) {
        return true;
    }
    sourceRec.y = btnState*frameHeight;
    return false;
}