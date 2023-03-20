/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Game
*/

#include "Game.hpp"
#include "Menu.hpp"
#include "Init/Parralax.hpp"
#include "Gameplay/Player.hpp"
#include "Gameplay/plateform.hpp"

//! Initialise the necessities like the window, initiate the audio devise and call the loop
void Game::start()
{
    WindowInit win(1920, 1080, "R-Type");
    win.setFPS(144);
    InitAudioDevice();
    gameLoop();
}

//! The loop of the game with initialisation
void Game::gameLoop()
{
    MyMusic music("./music/OST.ogg");
    //InitTexture background {"./assets/BG.png"};
    InitTexture midground {"./assets/Mid.png"};
    PlayerSystem playerSystem;
    PlateformSystem Plateform;

    music.playMusic();
    
    Plateform.spawn(1, {800, 400});
    playerSystem.spawn(1);
    while (!WindowShouldClose()) {
        music.updateMusic();
        playerSystem.update(Plateform, 1);
        BeginDrawing();
            ClearBackground(BLUE);
            playerSystem.render();
            Plateform.render();
            midground.draw((Vector2){ 0, 0 });
        EndDrawing();
    }
}