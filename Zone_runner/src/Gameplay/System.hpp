/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Entity.hpp"
#include "../Init/Sound.hpp"
#include "plateform.hpp"


//! Base of System class
class System {
    public:
        virtual ~System() = 0;

    protected:
        int id;
    private:
};

//! Manage the movement of the entity
class MoveSystem : public Component {
    public:
        void update(std::vector<Entity *>const & entities);
};

//! Can manage each bullet individually
class Bullet {
    public :
        Bullet(float x, float y, float speed);
        void update();
        void draw();
        Entity * bullet = new Entity();
        MoveSystem move;
    private :
};

//! Manage shoot of the object
class ShootSystem : public System {
    public :
        ShootSystem(Vector2 pos, Vector2 sp) : position(pos), speed(sp){};
        ~ShootSystem() = default;
        void shoot();
        void update(Vector2 &pos, std::vector<Entity *>const & entities);
        void render();
    private :
        Vector2 position;
        Vector2 speed;
        std::vector<Bullet> bullets;
        float timeLastShoot = 1.0f;
        // InitSound piew {"./Game/blaster.ogg"};
};

//! Manage the movement of the player
class MovementSystem : public System {
    public:
        void update(std::vector<Entity *>const & entities, ShootSystem &shoot, int state);
        void update(std::vector<Entity *>const & entities, int state);
};

class CollisionSystem : public System {
    public:
        void update(std::vector<Entity *>const &, std::vector<Entity *>const &);
};

class SpawnSystem : public System {
    public :
        Entity update(int x);
        Entity update(int x, int y);
};

class JumpSystem : public System {
    public :
        JumpSystem() : _state(0){};
        void update(std::vector<Entity *>const & entities, PlateformSystem &Plateform);
        int _state;
};

#endif /* !SYSTEM_HPP_ */
