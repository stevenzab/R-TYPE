/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Game
*/

#include "Game.hpp"
#include "Menu.hpp"
#include "./Gameplay/GameOver.hpp"
#include <random>
//! Initialise the necessities like the window, initiate the audio devise and call the loop
void Game::start(std::string ip)
{
	WindowInit win(1920, 1080, "R-Type");
	win.setFPS(144);
	InitAudioDevice();
	gameLoop(ip);
}

int getRandomInt(int minVal, int maxVal)
{
	// Create a random device object, which is used as a seed for the random number generator
	std::random_device rd;

	// Create a Mersenne Twister 19937 engine, seeded with the random device
	std::mt19937 gen(rd());

	// Create a uniform integer distribution between minVal and maxVal, inclusive
	std::uniform_int_distribution<> dis(minVal, maxVal);

	// Generate a random integer using the distribution and the engine
	return dis(gen);
}


//! The loop of the game with initialisation
void Game::gameLoop(std::string ip)
{
	InitTexture background("./Game/background2.png");
	MyMusic music("./Game/let-the-games-begin.ogg");
	InitTexture player("./Game/images/sprites/r-typesheet1.gif");
	InitTexture tex_player("./Game/images/vaisseau.png");
	InitTexture tex_ennemy("./Game/images/vaisseau_ennemi.png");

	asio::io_context io_context;
	Client _client(io_context, ip, "12345");
	_client.SendConnected();
	Menu menu;

	music.playMusic();

	bool alive = true;
	_client.Receive();

	Player mainPLayer{ RED, Vector2 {100, getRandomInt(0, 1080)}, 0};
	MovementSystem move;
	std::vector<Rectangle> shots;
	float enemySpeed = 500.0f;
	float enemyWidth = 50.0f;
	float enemyHeight = 50.0f;

	// Define a timer to spawn enemies periodically
	float enemySpawnTimer = 0.0f;
	float enemySpawnTime = 4.0f; // Spawn an enemy every 2 seconds
	float shootTimer = 0.0f;
	float shootInterval = 0.1f; // Shoot every 0.1 seconds

	try
	{
		while (!WindowShouldClose()) {
			io_context.poll();

            mainPLayer._id =_client._id;

			// Send the update
			_client.UpdateClient(mainPLayer.getComponent<PositionComponent>()->vector.x,
            mainPLayer.getComponent<PositionComponent>()->vector.y,
            mainPLayer.getComponent<ShootComponent>()->isShooting);
			_client.SendUpdateClient();

			BeginDrawing();
			ClearBackground(RAYWHITE);
			menu.drawBackground();

			// menu.loop(alive);
			if (!alive)
			{
				EndDrawing();
				_client.SendDisconnect();
				continue;
			}

			// Draw the circles at their new positions

			auto position = mainPLayer;
			for (const auto& shot : shots) {
				DrawRectangleRec(shot, RED);
			}

			// Draw the enemies
			for (const auto& enemy : _client.enemies) {
				tex_ennemy.draw((Vector2){enemy.rect.x, enemy.rect.y}, 0.1);

				// DrawRectangleRec(enemy.rect, BLUE);
			}

			// Move the enemies
			for (auto& enemy : _client.enemies) {

				if (CheckCollisionRecs(enemy.rect, { mainPLayer.getComponent<PositionComponent>()->vector.x - 50.0f, mainPLayer.getComponent<PositionComponent>()->vector.y - 50.0f, 100.0f, 100.0f })) {
					enemy.rect.x = GetScreenWidth() + enemyWidth;
					enemy.rect.y = getRandomInt(enemyHeight, GetScreenHeight() - enemyHeight);
					/*
					* send to the server that the block is killed
					*/
					_client.KillEnemy(enemy.id);

					mainPLayer.getComponent<LifeComponent>()->life--;
					if (mainPLayer.getComponent<LifeComponent>()->life <= 0) {
						alive = false;
					}
				}

				// Check for collisions with shots
				for (auto it = shots.begin(); it != shots.end(); ++it) {
					if (CheckCollisionRecs(enemy.rect, *it)) {
						it = shots.erase(it);
						enemy.rect.x = GetScreenWidth() + enemyWidth;
						enemy.rect.y = getRandomInt(enemyHeight, GetScreenHeight() - enemyHeight);
						_client.KillEnemy(enemy.id);
						break;
					}
				}
			}

			// Move the player's shots
			for (auto it = shots.begin(); it != shots.end(); ) {
				it->x += 1000.0f * GetFrameTime();
				if (it->x > GetScreenWidth()) {
					it = shots.erase(it);
				}
				else {
					++it;
				}
			}

			// Check for shoot messages from other players
			for (auto& player : _client.players)
			{
				if (player.getComponent<ShootComponent>()->isShooting)
				{
					shots.push_back({ player.getComponent<PositionComponent>()->vector.x - 5.0f, player.getComponent<PositionComponent>()->vector.y - 2.5f, 10.0f, 5.0f });
				}
			}

			move.movePlayer(mainPLayer.getComponent<PositionComponent>()->vector, _client.players);

			shootTimer += GetFrameTime();
			if (IsKeyDown(KEY_SPACE) && shootTimer >= shootInterval) {
				shots.push_back({ mainPLayer.getComponent<PositionComponent>()->vector.x - 5.0f, mainPLayer.getComponent<PositionComponent>()->vector.y - 2.5f, 10.0f, 5.0f });
				shootTimer = 0.0f;
				mainPLayer.getComponent<ShootComponent>()->isShooting = true;
			}
			else
				mainPLayer.getComponent<ShootComponent>()->isShooting = false;

			// Draw the player's circle
			tex_player.draw(mainPLayer.getComponent<PositionComponent>()->vector, 0.2);
			// DrawTextureV(mainPLayer.getComponent<PositionComponent>()->vector, MAROON);
			DrawText(TextFormat("Lives: %d", mainPLayer.getComponent<LifeComponent>()->life), 20, 20, 20, WHITE);

			for (auto it = _client.players.begin(); it != _client.players.end(); ++it)
			{
				tex_player.draw(it->getComponent<PositionComponent>()->vector, 0.2);

				// DrawCircleV(it->getComponent<PositionComponent>()->vector, 50, GREEN);
			}

			EndDrawing();
		}
		_client.SendDisconnect();
	}
	catch (const std::exception& ex)
	{
		_client.SendDisconnect();
		std::cout << "Exception caught: " << ex.what() << std::endl;
	}

	// io_context.stop();
}
