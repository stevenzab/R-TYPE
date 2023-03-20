/*
** EPITECH PROJECT, 2022
** Test
** File description:
** Window
*/

#include <string>
#include "raylib.h"

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

//! Initate the window
class WindowInit {
    public:
        WindowInit(int width, int height, std::string title);
        ~WindowInit();
        void setFPS(float fps);

    protected:
    private:
        int _width;
        int _height;
        std::string _title;
};

#endif /* !WINDOW_HPP_ */
