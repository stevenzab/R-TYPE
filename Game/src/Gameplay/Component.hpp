/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Component
*/

#include <vector>
#include "raylib.h"
#include "../Raylib.hpp"
#include "../Init/InitTexture.hpp"
#include "../Init/Sound.hpp"

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

//! Base of all component. If you create a new component, you need to heritate with
class Component{
    public:
        virtual ~Component() = 0;
        int id;
    protected:
};

//! Handle collision with other objects
class CollisionComponent : public Component {
    public:
        CollisionComponent(float x, float y, float width, float height);
        ~CollisionComponent() = default;
        void setPos(float x, float y) {hitbox = Rectangle{x, y, hitbox.width, hitbox.height};};
        Rectangle hitbox;
        bool isTouch = false;
    private:
};

//! Handle the position of object
class PositionComponent : public Component {
    public:
        PositionComponent(float, float);
        ~PositionComponent() = default;
        Vector2 vector;
    private:
};

//! Handle Movement of object
class MovementComponent : public Component{
    public:
        MovementComponent(float, float);
        float getSpeed() const { return speed;};
        float getDirection() const { return direction;}
        float speed;
        float direction;
    private:
};

//! Component for become invicible for a short period
class InvicibilityComponent : public Component {
    public :
        InvicibilityComponent() = default;
        void update();
        float timeLastDamage = 0.0f;
};

//! Manage the number of life of the object
class LifeComponent : public Component {
    public :
        LifeComponent(int _life) : life(_life), maxlife(_life){};
        int life;
        int maxlife = life;
        bool isDead = false;
};
//! Manage the life of the object
class RenderComponent : public Component {
    public :
        RenderComponent(std::string const & fileName);
        void draw(Vector2 position);
        void draw(Vector2 position, float scale);
        InitTexture texture;
};
//! Sound component
class SoundComponent : public Component {
    public :
        SoundComponent(std::string const & fileName);
        void play();
        InitSound sound;
};
//! Manage the number of shoot of the object
class ShootComponent : public Component {
    public :
        ShootComponent() = default;
        bool isShooting;
};

//! Manage the spawn of the object
class SpawnComponent : public Component {
    public :
        SpawnComponent(float time);
    private :
        int state = 0;
        float timeLastSpawn = 0.0f;
        float limit = 0.0f;
};

#endif /* !COMPONENT_HPP_ */
