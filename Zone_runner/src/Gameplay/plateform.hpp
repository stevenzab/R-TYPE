/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** plateform
*/

#include "System.hpp"

#ifndef PLATEFORM_HPP_
#define PLATEFORM_HPP_



class Plateform {
    public :
        Plateform(int id, Vector2 pos);
        ~Plateform() = default;
        void draw();
        int getID() const;
        std::vector<Entity*> _plateform;
    private :
        int _id;
        Color _Color;
};

//! Manage the spawn of Plateform, the update and the render
class PlateformSystem {
    public :
        PlateformSystem(int id);
        PlateformSystem() = default;
        ~PlateformSystem() = default;
        void spawn(int id, Vector2 pos);
        void render();
        std::vector<Plateform> MyPlateforms;
        int alive;
    private:
        InitTexture background;
};

#endif /* !PLATEFORM_HPP_ */
