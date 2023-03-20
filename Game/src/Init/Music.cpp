/*
** EPITECH PROJECT, 2023
** Test
** File description:
** Music
*/

#include "Music.hpp"

//! Constructor of music
MyMusic::MyMusic(std::string const& name): _name(name)
{
    music = LoadMusicStream(_name.c_str());
    _volume = 1;
}

//! Destructor of music
MyMusic::~MyMusic()
{
    UnloadMusicStream(music);
}

//! Play the music
void MyMusic::playMusic()
{
    PlayMusicStream(music);
}

//! Stop the music
void MyMusic::stopMusic()
{
    StopMusicStream(music);
}

//! Set the volume of the music
void MyMusic::setVolume(float volume)
{
    _volume += volume;
    SetMusicVolume(music, _volume);
}

//! Update the music
void MyMusic::updateMusic()
{
    UpdateMusicStream(music);
}

//! Return the volume
float MyMusic::getVolume() const
{
    return _volume;
}