/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Sound
*/

#include "Sound.hpp"

//! Create a sound
InitSound::InitSound(std::string const &name)
{
    sound = LoadSound(name.c_str());
}
//! Destroy a sound
InitSound::~InitSound()
{
    UnloadSound(sound);
}
//! Play a sound
void InitSound::play()
{
    PlaySound(sound);
}
//! Stop a sound
InitSound &InitSound::operator=(InitSound const &newSound)
{
    sound = newSound.sound;
    return *this;
}