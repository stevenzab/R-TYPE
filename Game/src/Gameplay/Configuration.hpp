/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Configuration
*/

#include "Entity.hpp"
#include "Component.hpp"
#include "../Init/JsonRead.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include <nlohmann/json.hpp>

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

class Configuration {
    public:
        Configuration();
        ~Configuration();
        Entity* createEntityFromJson(const JsonRead& json);
        std::vector<Entity*> createEntitiesFromJsonFile(const std::string& filename);
    protected:
    private:
        std::unordered_map<std::string, std::function<Component*(const JsonRead& json)>> componentFactory;
};


#endif /* !CONFIGURATION_HPP_ */
