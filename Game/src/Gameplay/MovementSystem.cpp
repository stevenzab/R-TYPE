/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** System
*/

#include "MovementSystem.hpp"

//! Manage the movement of the player
Vector2 MovementSystem::movePlayer(Vector2& vect, std::vector<Player> &players)
{
	// Handle player input
	if (IsKeyDown(KEY_LEFT)) {
		Vector2 newPos{ vect.x - 1000 * GetFrameTime(), vect.y };
		bool canMove = true;
		for (auto& player : players) {
			float distance = sqrt(pow(newPos.x - player.getComponent<PositionComponent>()->vector.x, 2) + pow(newPos.y - player.getComponent<PositionComponent>()->vector.y, 2));
			if (distance < 100.0f) { // sum of radii is 100
				canMove = false;
				break;
			}
		}
		if (canMove) {
			vect = newPos;
			if (vect.x < 50) vect.x = 50; // Left bound
		}
		return newPos;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		Vector2 newPos{ vect.x + 1000 * GetFrameTime(), vect.y };
		bool canMove = true;
		for (auto& player : players) {
			float distance = sqrt(pow(newPos.x - player.getComponent<PositionComponent>()->vector.x, 2) + pow(newPos.y - player.getComponent<PositionComponent>()->vector.y, 2));
			if (distance < 100.0f) { // sum of radii is 100
				canMove = false;
				break;
			}
		}
		if (canMove) {
			vect = newPos;
			if (vect.x > GetScreenWidth() - 50) vect.x = GetScreenWidth() - 50; // Right bound
		}
		return newPos;
	}
	if (IsKeyDown(KEY_UP)) {
		Vector2 newPos{ vect.x, vect.y - 1000 * GetFrameTime() };
		bool canMove = true;
		for (auto& player : players) {
			float distance = sqrt(pow(newPos.x - player.getComponent<PositionComponent>()->vector.x, 2) + pow(newPos.y - player.getComponent<PositionComponent>()->vector.y, 2));
			if (distance < 100.0f) { // sum of radii is 100
				canMove = false;
				break;
			}
		}
		if (canMove) {
			vect = newPos;
			if (vect.y < 50) vect.y = 50; // Top bound
		}
		return newPos;
	}
	if (IsKeyDown(KEY_DOWN)) {
		Vector2 newPos{ vect.x, vect.y + 1000 * GetFrameTime() };
		bool canMove = true;
		for (auto& player : players) {
			float distance = sqrt(pow(newPos.x - player.getComponent<PositionComponent>()->vector.x, 2) + pow(newPos.y - player.getComponent<PositionComponent>()->vector.y, 2));
			if (distance < 100.0f) { // sum of radii is 100
				canMove = false;
				break;
			}
		}
		if (canMove) {
			vect = newPos;
			if (vect.y > GetScreenHeight() - 50) vect.y = GetScreenHeight() - 50; // Bottom bound
		}
		return newPos;
	}

}