/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Ennemy
*/

#include "Ennemy.hpp"

//! Constructor of Ennemi? Take the pos in x y, the speed, the life point and size as the parameter
Ennemi::Ennemi(float x, float y, float speed, int life, int size) {
    ennemi->addComponent(new PositionComponent(x, y));
    ennemi->addComponent(new MovementComponent(-speed, 0));
    ennemi->addComponent(new CollisionComponent(x, y, size, size));
    ennemi->addComponent(new LifeComponent(life));
}

//! Update the position of the Ennemi and check if he is alive or touch by a bullet
void Ennemi::update() {
    if (ennemi->getComponent<CollisionComponent>()->isTouch == true) {
        ennemi->getComponent<LifeComponent>()->life--;
        if (ennemi->getComponent<LifeComponent>()->life == 0)
            ennemi->getComponent<LifeComponent>()->isDead = true;
    }
}

//! Draw the Ennemi
void Ennemi::draw() {
    auto pos = ennemi->getComponent<PositionComponent>();
    auto size = ennemi->getComponent<CollisionComponent>();
    DrawRectangle(pos->x, pos->y, size->hitbox.height, size->hitbox.width, VIOLET);
}

//! Constructor of the ennemi system that allow to manage and create multiple ennemies.
EnnemiSystem::EnnemiSystem(float speed, int life, int size) {
    std::srand(std::time(nullptr)%( GetScreenHeight() - 80));
    int random_variable = std::rand() %( GetScreenHeight() - 80);

    myEnnemi = Ennemi(GetScreenWidth(), random_variable, speed, life, size);
}

//! Spawn a new Ennemy
void EnnemiSystem::spawn(float speed, int life, int size) {
    std::srand(std::time(nullptr)% ( GetScreenHeight() - 80));
    int random_variable = std::rand() %( GetScreenHeight() - 80);

    myEnnemi = Ennemi(GetScreenWidth(), random_variable, speed, life, size);
}

//! update the ennemies movement and check the collision
void EnnemiSystem::update() {
    if (myEnnemi.ennemi->getComponent<LifeComponent>()->isDead == true || myEnnemi.ennemi->getComponent<PositionComponent>()->x <= -80) {
        spawn(2, myEnnemi.ennemi->getComponent<LifeComponent>()->maxlife, myEnnemi.ennemi->getComponent<CollisionComponent>()->hitbox.height);
    } else {
        myEnnemi.update();
    }
}

//! draw all of the ennemies
void EnnemiSystem::render() {
    myEnnemi.draw();
}