/*
** EPITECH PROJECT, 2023plateform
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** plateform
*/

#include "plateform.hpp"
#include "../Init/JsonRead.hpp"
#include "../Gameplay/Configuration.hpp"

Plateform::Plateform(int id, Vector2 vector)  {
    const std::string& filename = "./src/Entity/plateform.json";
    Configuration conf;
    _plateform = conf.createEntitiesFromJsonFile(filename);
    _plateform.at(0)->getComponent<PositionComponent>()->x = vector.x;
    _plateform.at(0)->getComponent<PositionComponent>()->y = vector.y;
    _plateform.at(0)->getComponent<CollisionComponent>()->hitbox.x = vector.x;
    _plateform.at(0)->getComponent<CollisionComponent>()->hitbox.y = vector.y;
    _id = id;
    _Color = PURPLE;
}

int Plateform::getID() const {
    return (_id);
}

void Plateform::draw() {
    DrawRectangle(_plateform.at(0)->getComponent<PositionComponent>()->x, _plateform.at(0)->getComponent<PositionComponent>()->y, _plateform.at(0)->getComponent<CollisionComponent>()->hitbox.width, _plateform.at(0)->getComponent<CollisionComponent>()->hitbox.height , _Color);
    DrawRectangle(_plateform.at(0)->getComponent<CollisionComponent>()->hitbox.x, _plateform.at(0)->getComponent<CollisionComponent>()->hitbox.y, _plateform.at(0)->getComponent<CollisionComponent>()->hitbox.width,_plateform.at(0)->getComponent<CollisionComponent>()->hitbox.height, _Color);
}

PlateformSystem::PlateformSystem(int id) {
    Vector2 startPosition = {800, 400}; // adjust the y-coordinate to create some spacing between Plateform
    MyPlateforms.emplace_back(Plateform(id, startPosition));
    background = InitTexture("./Game/images/background/GameOver.jpg");
    alive = 1;
}

void PlateformSystem::spawn(int id, Vector2 pos) {
    Color pColor = PURPLE;
    MyPlateforms.emplace_back(Plateform(id, pos));
}

void PlateformSystem::render() {
    for (Plateform& MyPlateform : MyPlateforms) {
        MyPlateform.draw();
    }
}
