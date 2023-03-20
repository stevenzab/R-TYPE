/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Sound
*/

#include "raylib.h"
#include <string>

#ifndef SOUND_HPP_
#define SOUND_HPP_
//! Create a sound
class InitSound {
    public:
        InitSound(std::string const &name);
        InitSound() = default;
        ~InitSound();
        void play();
        InitSound& operator=(InitSound const &s);

    protected:
    private:
        Sound sound;

};

#endif /* !SOUND_HPP_ */
