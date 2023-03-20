/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Entity
*/

#include <string>
#include <vector>
#include <typeinfo>
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Component.hpp"
#include "raylib.h"
#include "Init/InitTexture.hpp"

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

//! Class for any object like ennemy or player
class Entity {
    public:
        ~Entity() = default;
        void addComponent(Component* component);
        template<typename T>
        T* getComponent() {
            auto it = components.find(typeid(T).name());
                if (it != components.end()) {
                    return dynamic_cast<T*>(it->second);
                }
            return nullptr;
        }
        std::unordered_map<std::string, Component*> components;
    protected:
    private:
        int id;
};

//! Manage the spawn of the object
class SpawnComponent : public Component {
    public :
        SpawnComponent() = default;
        void update(std::vector<Entity *>const & entities);
    private :
        int state = 0;
        float timeLastSpawn = 0.0f;
};

#endif /* !ENTITY_HPP_ */
