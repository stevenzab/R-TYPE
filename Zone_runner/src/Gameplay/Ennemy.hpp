/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Ennemy
*/

#include "System.hpp"

#ifndef ENNEMY_HPP_
#define ENNEMY_HPP_


//! Create and manage a ennemi
class Ennemi {
    public :
        Ennemi() = default;
        Ennemi(float x, float y, float speed, int life, int size);
        void update();
        void draw();
        Entity * ennemi = new Entity();
    private :
};

//! Manage the spawn of Ennemy, the update and the render
class EnnemiSystem : public System {
    public :
        EnnemiSystem(float speed, int life, int size);
        EnnemiSystem() {};
        ~EnnemiSystem() = default;
        void spawn(float speed, int life, int size);
        void update();
        void render();
        Ennemi myEnnemi;
};

#endif /* !ENNEMY_HPP_ */
