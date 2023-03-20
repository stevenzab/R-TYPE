/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Entity
*/

#include "Entity.hpp"

//! Can add any Component if it's heritate of Component class
void Entity::addComponent(Component *component) {
    components[typeid(*component).name()] = component;
}