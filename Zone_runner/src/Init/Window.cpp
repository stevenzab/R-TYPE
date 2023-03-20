/*
** EPITECH PROJECT, 2022
** Test
** File description:
** Window
*/

#include "Window.hpp"

//! Constructor of Window
WindowInit::WindowInit(int width = 1200, int height = 800, std::string title = "RTYPE - SHOOT THEM ALL") : _width(width), _height(height), _title(title)
{
    InitWindow(_width, _height, _title.c_str());
}

//! Destructor of window
WindowInit::~WindowInit()
{
    CloseWindow();
}

//! Set the number of FPS in the window
void WindowInit::setFPS(float fps)
{
    SetTargetFPS(fps);
}