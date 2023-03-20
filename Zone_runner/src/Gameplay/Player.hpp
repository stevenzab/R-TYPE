/*
** EPITECH PROJECT, 2022
** Test
** File description:
** Player
*/

#include "System.hpp"
#include "Ennemy.hpp"
#include "plateform.hpp"

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

//! Create and manage a player
class Player {
    public :
        Player(Color Color, int id, Vector2 pos);
        ~Player() = default;
        void update(PlateformSystem &Plateform);
        void update();
        void draw();
        int getID() const;
        std::vector<Entity*> player;
        MovementSystem move;
        ShootSystem shoot{Vector2{0, 0}, Vector2{3, 0}};
        JumpSystem jump;

    private :
        int _id;
        Color _Color;
};

//! Manage the spawn of Player, the update and the render
class PlayerSystem : public System {
    public :
        PlayerSystem(int id);
        PlayerSystem();
        ~PlayerSystem() = default;
        void spawn(int _id);
        bool update(PlateformSystem &Plateform, int playerId);
        bool update(int playerId);
        void render();
        std::vector<Player> MyPlayers;
        int alive;
    private:
        InitTexture background;
};

#endif /* !PLAYER_HPP_ */
