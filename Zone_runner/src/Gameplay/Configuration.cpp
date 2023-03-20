/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Configuration
*/

#include "Configuration.hpp"
#include "../Init/JsonRead.hpp"

Configuration::Configuration()
{
    componentFactory = {
        {"Collision", [](const JsonRead& json) { return new CollisionComponent(json.getValueJson<float>("x"), json.getValueJson<float>("y"), json.getValueJson<float>("width"), json.getValueJson<float>("height")); }},
        {"Position", [](const JsonRead& json) { return new PositionComponent(json.getValueJson<float>("x"), json.getValueJson<float>("y")); }},
        {"Movement", [](const JsonRead& json) { return new MovementComponent(json.getValueJson<float>("speed"), json.getValueJson<float>("direction")); }},
        {"Render", [](const JsonRead& json) { return new RenderComponent(json.getValueJson<std::string>("filename")); }},
        {"Sound", [](const JsonRead& json) { return new SoundComponent(json.getValueJson<std::string>("filename")); }},
        {"Life", [](const JsonRead& json) { return new LifeComponent(json.getValueJson<float>("life")); }},
        {"Jump", [](const JsonRead& json) { return new JumpComponent(json.getValueJson<int>("speed"), json.getValueJson<int>("fall"), json.getValueJson<int>("max"), json.getValueJson<int>("ground"));}}
    };
}

Configuration::~Configuration()
{
}

Entity *Configuration::createEntityFromJson(const JsonRead& json)
{
    Entity* entity = new Entity();

    JsonRead compJson(json.getValueJsonFromString("components"));
    for (auto& componentJson : compJson.getJsonValue()) {
        const JsonRead& componentJ(componentJson);
        std::string componentName = componentJ.getValueJson<std::string>("type");
        auto componentFactoryIt = componentFactory.find(componentName);
        if (componentFactoryIt != componentFactory.end()) {
            Component* component = componentFactoryIt->second(componentJ);
            entity->addComponent(component);
            std::cout << "Component added" << std::endl;
        } else {
            std::cerr << "Unknown component type: " << componentName << std::endl;
        }
    }
    return entity;
}

std::vector<Entity*> Configuration::createEntitiesFromJsonFile(const std::string& filename) {
    JsonRead jsonF(filename);

    const JsonRead& entJson(jsonF.getValueJsonFromString("entities"));

    std::vector<Entity*> entities;
    for (auto& entityJson : entJson.getJsonValue()) {
        const JsonRead &eJ(entityJson);
        Entity* entity = createEntityFromJson(eJ);
        entities.push_back(entity);
    }
    return entities;
}