/*
** EPITECH PROJECT, 2023
** Test
** File description:
** Music
*/

#include <string>
#include "raylib.h"

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

//! Class to initiate music
class MyMusic {
    public:
        MyMusic(std::string const& name);
        ~MyMusic();
        void playMusic();
        void stopMusic();
        void setVolume(float volume);
        void updateMusic();
        float getVolume() const;

    protected:
    private:
        std::string _name;
        Music music;
        float _volume;
};

#endif /* !MUSIC_HPP_ */
