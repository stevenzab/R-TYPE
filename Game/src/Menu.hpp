/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <iostream>

#include "Init/InitTexture.hpp"
#include "Init/Parralax.hpp"
#include "Init/Button.hpp"
#include "Init/TextField.hpp"
#include "Init/Music.hpp"

#include "Gameplay/GameOver.hpp"
#include <raylib.h>

typedef enum GameScreen {
    MENU1,
    MENU2,
    SETTINGS,
    GAMEPLAY,
    GAMEOVER,
} GameScreen;

//! Manage the menu
class Menu {
    public:
        Menu();
        ~Menu();
        void menu1();
        void menu2();
        void menuSettings(MyMusic &music);

        void drawMenu1();
        void drawMenu2();
        void drawMenuSettings();
        void drawGameOver();
        void drawBackground();

        std::string getInputIp() const { return _input_ip; }
        std::string getInputPort() const { return _input_port; }

        void setCurrentScreen(GameScreen screen) { currentScreen = screen; }
        GameScreen getCurrentScreen() const { return currentScreen; }

        void setIsConnected(bool connected) { _isConnected = connected; }
        bool getIsConnected() const { return _isConnected; }

    protected:
    private:
        /// Set texture background
        Parralax background {0.0f, 0.1f, "Game/images/background/background.png"};
        Parralax midground{0.0f, 0.3f, "Game/images/background/background_planets.png"};
        InitTexture GameOver{"Game/images/game_over.png"};
        InitTexture Connecting{"Game/images/Connecting.png"};

        GameScreen currentScreen;
        bool _isConnected;
        bool btnAction;
        int btnState;

        //! Initiate button menu : Play, Quit, Settings.
        Button _button_play{"Game/images/Menu/button_play3.png", 1920, 1080};
        Button _button_quit{"Game/images/Menu/button_quit.png", 1920, 1300};
        Button _button_settings{"Game/images/Menu/button_settings.png", 3700, 2000};
        Button _button_connect{"Game/images/Menu/button_connect.png", 1920, 2000};
        Button _button_music_up{"Game/images/Menu/button_music_up.png", 1820, 1080};
        Button _button_music_down{"Game/images/Menu/button_music_down.png", 2020, 1080};
        Button _button_back{"Game/images/Menu/button_back.png", 500, 500};



        //! Initiate textfile for ip and port.
        TextField _textfield_ip{"ENTER IP:", 1920, 1080};
        TextField _textfield_port{"ENTER PORT:", 1920, 1300};
        std::string _input_ip;
        std::string _input_port;

        //! Initiate Menu Settings
        float _gaugeSound = 0.0f;

};

#endif /* !MENU_HPP_ */