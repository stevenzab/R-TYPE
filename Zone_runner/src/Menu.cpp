/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Menu
*/

#include "raylib.h"
#include "Menu.hpp"
#include <iostream>

Menu::Menu()
{
    _isMenuPlay = false;
    _mousePoint = {0.0f, 0.0f};
    frameHeight = (float)_button_play.getHeight()/2;
    sourceRec = { 0, 0, (float)_button_play.getWidth(), frameHeight };
    btnBounds = { 100/2.0f - _button_play.getWidth()/2.0f, 100/2.0f - _button_play.getHeight()/2/2.0f, (float)_button_play.getWidth(), frameHeight };
}

Menu::~Menu()
{
}

bool Menu::isConnected()
{
    return(false);
}

void Menu::ConnectionBG()
{
    Connecting.draw((Vector2){ 0, 0 });
}

void Menu::loop(bool alive)
{
    if (alive == true) {
        btnAction = false;
        CheckCollisionButton(GetMousePosition());
        drawBackground();
        drawMenu();
    }
    else
        GameOver.draw((Vector2){ 0, 0 });
}

void Menu::drawMenu()
{
    _button_play.draw(sourceRec, btnBounds);
}

void Menu::drawBackground()
{
    background.draw();
    midground.draw();
}

bool Menu::getIsMenuPlay() const
{
    return _isMenuPlay;
}

void Menu::setIsMenuPlay(bool isMenuPlay)
{
    _isMenuPlay = isMenuPlay;
}

void Menu::CheckCollisionButton(Vector2 mousePoint)
{
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
        std::cout << "_____PLAY____\n";
        // PlaySound(fxButton);
    }
    sourceRec.y = btnState*frameHeight;
}