#include "Server.hpp"

//! Constructor of class Server
Server::Server(asio::io_context& io_context, unsigned short port)
	: _io_context(io_context),
	_socket(io_context, udp::endpoint(asio::ip::address::from_string("0.0.0.0"), port))
{
	do_receive();
}

//! Destructor default of the class
Server::~Server()
{
}


// The function that updates the position of each enemy in the list and removes any enemies that are outside of the screen
void Server::updateEnemies() {
	float enemySpeed = 500.0f;
	float enemyWidth = 50.0f;
	float enemyHeight = 50.0f;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1080 - enemyHeight);

	auto startTime = std::chrono::steady_clock::now();

	while (true) {
		// Move enemies and remove those outside of the screen
		std::unique_lock<std::mutex> lock(_enemyMutex);
		for (auto it = _enemies.begin(); it != _enemies.end(); ) {
			it->_x -= enemySpeed * 0.116f;
			if (it->_x < -1000) {
				++it;
				continue;
			}
			++it;
		}
		std::vector<Enemy> enemies_copy = _enemies;
		for (const auto& enemy : enemies_copy) {
			if (enemy._x < -1000) {
				auto it = std::find_if(_enemies.begin(), _enemies.end(), [enemy](const Enemy& e) { return e.id == enemy.id; });
				if (it != _enemies.end()) {
					_enemies.erase(it);
				}
			}
		}

		// Create a message to send to all clients
		std::ostringstream oss;
		oss << "enemies=";
		for (const auto& enemy : _enemies) {
			oss << "id" << enemy.id << "x" << enemy._x << "y" << enemy._y << ";";
		}
		std::string enemyStr = oss.str();
		lock.unlock();

		Message response_msg;
		response_msg.type = ACTION::OK;
		response_msg.msgType = MessageType::UPDATE_ALL_ENEMIES;
		response_msg.SetStringData(enemyStr);

		// Send the message to all clients
		for (const auto& client : _clients) {
			_socket.async_send_to(asio::buffer(&response_msg, sizeof(response_msg) + 1), client.endpoint, [](std::error_code ec, std::size_t bytes_sent) {});
		}

		// Sleep for the remaining time to get a total iteration time of 500ms
		auto endTime = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::this_thread::sleep_for(std::chrono::milliseconds(500) - elapsed);

		// Update the start time for the next iteration
		startTime = std::chrono::steady_clock::now();
	}
}


// The function that spawns enemies at random locations on the screen
void Server::spawnEnemies() {
	float enemyWidth = 50.0f;
	float enemyHeight = 50.0f;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1080 - enemyHeight);
	int enemyId = 1;
	auto startTime = std::chrono::steady_clock::now();
	while (true) {
		// Spawn a new enemy at a random location
		Enemy enemy(enemyId++, (float)1920, (float)dis(gen));

		// Add the new enemy to the list of enemies
		std::unique_lock<std::mutex> lock(_enemyMutex);
		_enemies.push_back(enemy);
		lock.unlock();

		// Sleep for 2 seconds before spawning the next enemy
		auto endTime = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::this_thread::sleep_for(std::chrono::milliseconds(800) - elapsed);

		// Update the start time for the next iteration
		startTime = std::chrono::steady_clock::now();
	}
}

//! Start receiving data from the client asynchronously
void Server::do_receive()
{
	_socket.async_receive_from(
		asio::buffer(_recv_buffer), _recv_endpoint,
		[this](const asio::error_code& error, std::size_t bytes_recvd)
		{
			if (!error && bytes_recvd > 0)
			{
				Message msg;
				std::memcpy(&msg, _recv_buffer.data(), std::min(bytes_recvd, sizeof(Message)));

				std::string dataStr(msg.data.begin(), msg.data.begin() + std::min<size_t>(msg.data.size(), bytes_recvd));
				std::istringstream iss(dataStr);
				int nbChar;
				iss >> nbChar;
				iss.ignore(); // consume the newline character
				std::string str;
				std::getline(iss, str);
				str = str.substr(0, nbChar);
				// std::cout << "string result : " << str << std::endl;

				handle_receive(msg, _recv_endpoint, str);
			}
	do_receive();
		});
}

//! Handle the received data and connect the client
void Server::handle_connect(const Message& msg, udp::endpoint endpointRcv)
{
	// Store the endpoint of the new client
	_clients.emplace_back(PlayerFromServer{ endpointRcv, (int)_clients.size() + 1, 50, 50, false });

	// Send a confirmation message back to the client
	int playerId = _clients.size();
	Message response_msg;
	response_msg.type = ACTION::OK;
	response_msg.msgType = MessageType::PLAYER_CONNECTED;
	response_msg.id_player = playerId;
	response_msg.SetStringData("Connected");
	std::cout << "ID : " << std::to_string(response_msg.id_player) << " Endpoint : " << _clients[_clients.size() - 1].endpoint << "\n";
	// Send the message to the client
	_socket.async_send_to(asio::buffer(&response_msg, sizeof(response_msg) + 1), endpointRcv, [](std::error_code ec, std::size_t bytes_sent) {});
}
//! Handle disconnect client
void Server::handle_disconnect(const Message& msg, udp::endpoint endpointRcv)
{
	auto it = std::find_if(_clients.begin(), _clients.end(),
		[&](const auto& client) {
			return client.endpoint == endpointRcv;
		});

	if (it != _clients.end())
	{
		// Remove the client from the vector
		_clients.erase(it);
	}
}

//! Update the client position
void Server::UpdateClient(const std::string& str, udp::endpoint endpointRcv)
{
	std::stringstream ss(str);
	std::string token;
	float x, y;
	int id;
	bool shooting = false;

	while (std::getline(ss, token, ';')) {
		if (token.find("PlayerId=") == 0) {
			id = std::stoi(token.substr(9));
		}
		else if (token.find("x=") == 0) {
			x = std::stoi(token.substr(2));
		}
		else if (token.find("y=") == 0) {
			y = std::stoi(token.substr(2));
		}
		else if (token.find("shoot=") == 0) {
			shooting = std::stoi(token.substr(6));
		}
	}
	// Find the client in the _clients vector using their endpoint
	auto client = std::find_if(_clients.begin(), _clients.end(),
		[&](const auto& c) {
			return c.id == id;
		});

	if (client != _clients.end()) {
		// Update the client's x and y coordinates
		client->x = x;
		client->y = y;
		client->isShooting = shooting;
	}
}
//! Update all clients
void Server::UpdateAllClients(const Message& msg, udp::endpoint endpointRcv)
{
	std::string updateStr = "";
	for (const auto& c : _clients) {
		updateStr += "Client (" + std::to_string(c.id) + "): x = " + std::to_string(c.x) + ", y = " + std::to_string(c.y) + ", shoot = " + std::to_string(c.isShooting) + "\n";
	}

	// Send a confirmation message back to the client
	Message response_msg;
	response_msg.type = ACTION::OK;
	response_msg.msgType = MessageType::UPDATE_ALL_CLIENTS;
	response_msg.id_player = msg.id_player;
	response_msg.SetStringData(updateStr);

	// Send the message to the client
	_socket.async_send_to(asio::buffer(&response_msg, sizeof(response_msg) + 1), endpointRcv, [](std::error_code ec, std::size_t bytes_sent) {});
}


void Server::RemoveEnemy(std::string dataString)
{
	int id = std::stoi(dataString);
	std::unique_lock<std::mutex> lock(_enemyMutex);
	auto it = std::find_if(_enemies.begin(), _enemies.end(), [id](const Enemy& e) { return e.id == id; });
	if (it != _enemies.end()) {
		_enemies.erase(it);
	}
}

//! Handle the received data
void Server::handle_receive(const Message& msg, udp::endpoint endpointRcv, std::string dataString)
{
	std::cout << "Id : " << std::to_string(msg.id_player) << " Action : " << msg.msgType << std::endl;

	// Handle the message type
	switch (msg.msgType)
	{
	case MessageType::PLAYER_CONNECTED:
	{
		handle_connect(msg, endpointRcv);
		break;
	}
	case MessageType::PLAYER_DISCONNECTED:
	{
		handle_disconnect(msg, endpointRcv);
		break;
	}
	case MessageType::UPDATE_CLIENT:
	{
		// mise a jour du client x
		UpdateClient(dataString, endpointRcv);
		break;
	}
	case MessageType::UPDATE_ALL_CLIENTS: {
		UpdateAllClients(msg, endpointRcv);
		break;
	}
	case MessageType::KILL_ENEMY: {
		RemoveEnemy(dataString);
		break;
	}
		do_receive();
	}
}