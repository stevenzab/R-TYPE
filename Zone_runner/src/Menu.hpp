/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Menu
*/

#include "Init/InitTexture.hpp"
#include "Init/Parralax.hpp"

#ifndef MENU_HPP_
#define MENU_HPP_

//! Manage the menu
class Menu {
    public:
        Menu();
        ~Menu();
        void loop(bool alive);
        void drawBackground();
        bool isConnected();
        void ConnectionBG();
        void CheckCollisionButton(Vector2 mousePoint);
        void setIsMenuPlay(bool);
        bool getIsMenuPlay() const;
        void drawMenu();

    protected:
    private:
        Parralax background {0.0f, 0.1f, "assets/background.png"};
        Parralax midground{0.0f, 0.3f, "assets/Mid.png"};
        InitTexture GameOver{"Game/game_over.png"};
        InitTexture Connecting{"Game/Connecting.png"};
        bool _isMenuPlay;
        Vector2 _mousePoint;
        float frameHeight;
        Rectangle sourceRec;
        Rectangle btnBounds;
        bool btnAction;
        int btnState;
        InitTexture _button_play;
};

#endif /* !MENU_HPP_ */