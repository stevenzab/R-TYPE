/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Parralax
*/

#include "InitTexture.hpp"

#ifndef PARRALAX_HPP_
#define PARRALAX_HPP_

//! Do the parralax of the background
class Parralax {
    public:
        Parralax(float scroll, float move, std::string name);
        ~Parralax();
        void draw();
    protected:
    private:
        float _scroll;
        float _move;
        InitTexture texture;
};

#endif /* !PARRALAX_HPP_ */
