/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Menu
*/

#include "Menu.hpp"

//! Constructor of class Menu
Menu::Menu()
{
    currentScreen = MENU1;
    _isConnected = false;
}

//! Deconstructor of class Menu
Menu::~Menu()
{
}

//! menu1 manage the buttons on the first menu.
void Menu::menu1()
{
    // btnAction = false;
    if (_button_play.CheckCollisionButton(GetMousePosition()) == true)
        currentScreen = MENU2;
    if (_button_quit.CheckCollisionButton(GetMousePosition()) == true)
        CloseWindow();
    if (_button_settings.CheckCollisionButton(GetMousePosition()) == true)
        currentScreen = SETTINGS;
}

//! menu1 manage the buttons and textfields on the second menu.
void Menu::menu2()
{
    _input_ip = _textfield_ip.CheckCollisionTextField(GetMousePosition());
    _input_port = _textfield_port.CheckCollisionTextField(GetMousePosition());

    if (_button_back.CheckCollisionButton(GetMousePosition()) == true)
        currentScreen = MENU1;
    if (_input_ip.length() > 0 && _input_port.length() > 0) {
        if (_button_connect.CheckCollisionButton(GetMousePosition()) == true)
            currentScreen = GAMEPLAY;
    }
}

//! menu1 manage the buttons on the second menu.
void Menu::menuSettings(MyMusic &music)
{
    if (_button_back.CheckCollisionButton(GetMousePosition()) == true)
        currentScreen = MENU1;
    if (_button_music_up.CheckCollisionButton(GetMousePosition()) == true) {
                music.setVolume(0.1);
    }
    if (_button_music_down.CheckCollisionButton(GetMousePosition()) == true) {
            if (music.getVolume() > 0)
                music.setVolume(-0.1);
    }
}

//! draw the background of the game.
void Menu::drawBackground()
{
    background.draw();
    midground.draw();
}

//! draw the buttons on the first menu.
void Menu::drawMenu1()
{
    _button_play.drawButton();
    _button_quit.drawButton();
    _button_settings.drawButton();
}

//! draw the buttons and textfields on the second menu.
void Menu::drawMenu2()
{
    _textfield_ip.draw();
    _textfield_port.draw();
    _button_connect.drawButton();
    _button_back.drawButton();
}

//! draw the buttons on the settings menu.
void Menu::drawMenuSettings()
{
    _button_music_down.drawButton();
    _button_music_up.drawButton();
    _button_back.drawButton();
}

//! draw the game over screen.
void Menu::drawGameOver()
{
    GameOver.draw((Vector2){0, 0});
}