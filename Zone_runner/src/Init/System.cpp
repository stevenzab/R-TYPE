/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** System
*/

#include "System.hpp"
#include "Raylib.hpp"

//! Destructor of System. Don't touch
System::~System()
{
}

//! Handle the shoot of the object. It shoot every second
void ShootSystem::shoot() {
    timeLastShoot += GetFrameTime();
    if (timeLastShoot >= 0.1) {
        bullets.emplace_back(Bullet(position.x, position.y, speed.x));
        timeLastShoot = 0;
        // piew.play();
    }
}

//! Update the position of each Bullet and manage if the bullet touch an object with CollisionComponent. Take the position of the principal object and the entity (like the ennemy or the player) as parameters
void ShootSystem::update(Vector2 &pos, std::vector<Entity *>const & entities) {
    position = pos;
    timeLastShoot += GetFrameTime();
    for (auto it = bullets.begin(); it != bullets.end(); it++) {
        Bullet& bullet = *it;
        bullet.update();
        auto position = bullet.bullet->getComponent<PositionComponent>();
        if (position->x < 0 || position->x > GetScreenWidth() || position->y < 0 || position->y > GetScreenHeight()) {
            bullets.erase(it--);
        }
        for (auto e : entities) {
            Rectangle hitbox = bullet.bullet->getComponent<CollisionComponent>()->hitbox;
            Rectangle ent = e->getComponent<CollisionComponent>()->hitbox;
            if (CheckCollisionRecs(ent, hitbox)) {
                bullets.erase(it--);
                e->getComponent<CollisionComponent>()->isTouch = true;
                break;
            }
        }
    }
}

//! Draw each bullet
void ShootSystem::render() {
    for (auto it = bullets.begin(); it != bullets.end(); it++) {
        Bullet& bullet = *it;
        bullet.draw();
    }
}

//! Manage the move of the player and update many information such as the position and the shoot
void MovementSystem::update(std::vector<Entity*>const &entities, ShootSystem &shoot, int state) {
    for (auto& e : entities) {
        auto movement = e->getComponent<MovementComponent>();
        auto position = e->getComponent<PositionComponent>();
        auto collision = e->getComponent<CollisionComponent>();
        auto entShoot = e->getComponent<ShootComponent>();
        if (movement) {
            if (state == 0) {
                if (IsKeyDown(UP) && position->y > 0) {
                    position->y -= movement->getSpeed();
                    movement->direction = 2;
                }
                if (IsKeyDown(DOWN) && position->y < GetScreenHeight()) {
                    position->y += movement->getSpeed();
                    movement->direction = 3;
                }
                if (IsKeyDown(LEFT) && position->x > 0) {
                    position->x -= movement->getSpeed();
                    movement->direction = 5;
                }
                if (IsKeyDown(RIGHT) && position->x < GetScreenWidth()) {
                    position->x += movement->getSpeed();
                    movement->direction = 4;
                }
                if (IsKeyDown(KEY_SPACE)) {
                    shoot.shoot();
                    entShoot->shooted = 1;
                }
            } else
                if (movement)
                    position->x += movement->getSpeed();
        }
        position->vector = Vector2{position->x, position->y};
        collision->setPos(position->x - 50, position->y - 50);
    }
}
//! Update the position of the object
void MovementSystem::update(std::vector<Entity *> const & entities, int state)
{
    for (auto& e : entities) {
        // auto player = e->getComponent<PlayerComponent>();
        // if (player && player->id != playerId) continue;

        auto movement = e->getComponent<MovementComponent>();
        auto position = e->getComponent<PositionComponent>();
        auto collision = e->getComponent<CollisionComponent>();
        if (movement) {
            if (state == 0) {
                if (IsKeyDown(UP) && position->y > 0)
                    position->y -= movement->getSpeed();
                if (IsKeyDown(DOWN) && position->y < GetScreenHeight())
                    position->y += movement->getSpeed();
                if (IsKeyDown(LEFT) && position->x > 0)
                    position->x -= movement->getSpeed();
                if (IsKeyDown(RIGHT) && position->x < GetScreenWidth())
                    position->x += movement->getSpeed();
            } else if (state == 1) {
                if (IsKeyDown(LEFT) && position->x > 0)
                    position->x -= movement->getSpeed();
                if (IsKeyDown(RIGHT) && position->x < GetScreenWidth())
                    position->x += movement->getSpeed();
            } else
                if (movement)
                    position->x += movement->getSpeed();
        }
        position->vector = Vector2{position->x, position->y};
        collision->setPos(position->x - 50, position->y - 50);
    }
}

//! Update the position of the object
void MoveSystem::update(std::vector<Entity *>const & entities) {
    for (auto& e : entities) {
        auto movement = e->getComponent<MovementComponent>();
        auto position = e->getComponent<PositionComponent>();
        auto collision = e->getComponent<CollisionComponent>();
        if (movement)
            position->x += movement->getSpeed();
        position->vector = Vector2{position->x, position->y};
        collision->setPos(position->x, position->y);
    }
}

//! Constructor of Bullet. Take the position x, y and the speed as the parameter
Bullet::Bullet(float x, float y, float speed) {
    bullet->addComponent(new PositionComponent(x, y));
    bullet->addComponent(new MovementComponent(10, 0));
    bullet->addComponent(new CollisionComponent(x, y, 5, 5));
    bullet->addComponent(new MoveSystem());
}

//! Update the position of the bullet
void Bullet::update() {
    bullet->getComponent<MoveSystem>()->update({bullet});
}

//! Draw the bullet
void Bullet::draw() {
    auto pos = bullet->getComponent<PositionComponent>();
    DrawCircle(pos->x, pos->y, 5.0f, RED);
}

void JumpSystem::update(std::vector<Entity *>const & entities) {
     for (auto& e : entities) {
        // auto player = e->getComponent<PlayerComponent>();
        // if (player && player->id != playerId) continue;

        auto movement = e->getComponent<MovementComponent>();
        auto position = e->getComponent<PositionComponent>();
        auto collision = e->getComponent<CollisionComponent>();
        auto jump = e->getComponent<JumpComponent>();
        if (_state == 0)
            if (IsKeyDown(SPACE) && position->y == 700)
                _state = 1;
        else if (_state == 1) {
            if (position->y - jump->_speed  == 700 - jump->_max)
                _state = 2;
            else 
                position->y -= jump->_speed;
        } else if (_state == 2) {
            if (position->y + jump->_fall == 700)
                _state = 0;
            else
                position->y += jump->_fall;
        }
    }
}