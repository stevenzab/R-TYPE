/*
** EPITECH PROJECT, 2022
** Test
** File description:
** Player
*/

#include "Player.hpp"
#include "../Init/JsonRead.hpp"
#include "../Gameplay/Configuration.hpp"

//! Constructor of Player. Take the color and the Id as the parameter
Player::Player(Color Color, int id, Vector2 vector)  {
    const std::string& filename = "./src/Entity/player.json";
    Configuration conf;
    player = conf.createEntitiesFromJsonFile(filename);
    _id = id;
    _Color = Color;
}

//! give the ID associate to the player
int Player::getID() const {
    return (_id);
}

//! Update the position of the player and check if he is alive or touch by a ennemie
void Player::update(PlateformSystem &Plateform) {
    move.update({player.at(0)}, 1);
    jump.update({player.at(0)}, Plateform);
}

void Player::update() {
    if (player.at(0)->getComponent<CollisionComponent>()->isTouch == true) {
        player.at(0)->getComponent<LifeComponent>()->life--;
        if (player.at(0)->getComponent<LifeComponent>()->life == 0)
            player.at(0)->getComponent<LifeComponent>()->isDead = true;
        player.at(0)->getComponent<CollisionComponent>()->isTouch = false;
    }
    move.update({player.at(0)}, 1);
}

//! Draw the player
void Player::draw() {
    DrawCircleV(player.at(0)->getComponent<PositionComponent>()->vector, 50, MAROON);
    shoot.render();
}

//! Constructor of the player system that allow to manage and create multiple player. Create the first player and make it red with the ID 1
PlayerSystem::PlayerSystem(int id) {
    Vector2 startPosition = {100, 700}; // adjust the y-coordinate to create some spacing between players
    MyPlayers.emplace_back(Player(RED, id, startPosition));
    background = InitTexture("./Game/images/background/GameOver.jpg");
    alive = 1;
}

PlayerSystem::PlayerSystem() {
}

//! Spawn a new player with the Id associated to his number of arrival
void PlayerSystem::spawn(int id) {
    Color pColor = RED;
    pColor.b += id * 10;
    Vector2 startPosition = {100, 700}; // adjust the y-coordinate to create some spacing between players
    MyPlayers.emplace_back(Player(pColor, id, startPosition));
    alive++;
}

//! update the players movement and check the collision
bool PlayerSystem::update(PlateformSystem &Plateform, int playerId) {

    if (alive == 0)
        return false;
    for (auto it = MyPlayers.begin(); it != MyPlayers.end(); it++) {
        Player &MyPlayer = *it;
        MyPlayer.update(Plateform);
    }
    return true;
}

bool PlayerSystem::update(int playerId) {

    if (alive == 0)
        return false;
    for (auto it = MyPlayers.begin(); it != MyPlayers.end(); it++) {
        Player &MyPlayer = *it;
        if (MyPlayer.getID() == playerId) {
            MyPlayer.update();
        }
    }
    return true;
}


//! draw all of the player
void PlayerSystem::render() {
    for (Player& MyPlayer : MyPlayers) {
        MyPlayer.draw();
    }
}