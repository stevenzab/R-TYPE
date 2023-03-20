/*
** EPITECH PROJECT, 2023
** Client.cpp
** File description:
** Client
*/

#include "Client.hpp"

//! Constructor of client who init the socket and connect the client to the server.
Client::Client(asio::io_context& io_context, const std::string& host, const std::string& port)
	:
	_socket(io_context, udp::endpoint(udp::v4(), 0)),
	_resolver(io_context),
	_remote_endpoint(*_resolver.resolve(host, port))
{
	_server_endpoint = udp::endpoint(_remote_endpoint.address(), _remote_endpoint.port());
	_connected = false;
	_nb_player = 0;
}

//! Destructor of the client
void Client::SendConnected()
{
	try
	{
		std::cout << "TESTESTE\n";
		Message msg;
		msg.type = ACTION::CONNECT;
		msg.msgType = MessageType::PLAYER_CONNECTED;
		msg.id_player = _id;
		// std::string messageStr = "CONNECTED";
		// std::memcpy(msg.data.data(), messageStr.c_str(), messageStr.length());
		// msg.data[messageStr.length()] = '\0';
		std::string str("Connected");
		msg.SetStringData("Connected");

		do_send(msg);
	}
	catch (std::exception& ex) {
		std::cerr << "Exception caught: " << ex.what() << std::endl;
	}
}
//! SendDisconnect message to the server
void Client::SendDisconnect()
{
	Message msg;
	msg.id_player = _id;
	msg.type = ACTION::DISCONNECT;
	msg.msgType = MessageType::PLAYER_DISCONNECTED;
	std::string str("Disconnected");
	msg.SetStringData("Disconnected");

	do_send(msg);
}

std::string buildPlayerString(int id, float x, float y, bool isShooting)
{
	std::ostringstream oss;
	oss << "PlayerId=" << id << ";x=" << x << ";y=" << y << ";shoot=" << isShooting << ";";
	return oss.str();
}

//! Update a client, get the position of the player and set it in the message
void Client::UpdateClient(int x, int y, bool isShooting)
{
	Message msg;
	msg.id_player = _id;
	msg.type = ACTION::UPDATE;
	msg.msgType = MessageType::UPDATE_CLIENT;

	std::string updateStr = buildPlayerString(_id, x, y, isShooting);
	msg.SetStringData(updateStr);

	do_send(msg);
}

//! Send the update message to the server
void Client::SendUpdateClient()
{
	Message msg;
	msg.id_player = _id;
	msg.type = ACTION::UPDATE;
	msg.msgType = MessageType::UPDATE_ALL_CLIENTS;

	do_send(msg);
}
//! Parse the info of a client
std::vector<ClientParse> Client::parse_client_info(const std::string& input) {
	std::vector<ClientParse> clients;

	std::stringstream ss(input);
	std::string line;

	while (std::getline(ss, line, '\n')) {
		if (line.empty()) {
			continue;
		}

		// Extract the client ID
		std::size_t id_start_pos = line.find('(') + 1;
		std::size_t id_end_pos = line.find(')');
		int id = std::stoi(line.substr(id_start_pos, id_end_pos - id_start_pos));

		// Extract the x and y positions
		std::size_t x_start_pos = line.find("x = ") + 4;
		std::size_t x_end_pos = line.find(',', x_start_pos);
		float x = std::stof(line.substr(x_start_pos, x_end_pos - x_start_pos));

		std::size_t y_start_pos = line.find("y = ") + 4;
		std::size_t y_end_pos = line.find(',', y_start_pos);
		float y = std::stof(line.substr(y_start_pos, y_end_pos - y_start_pos));

		std::size_t shoot_start_pos = line.find("shoot = ") + 8;
		std::size_t shoot_end_pos = line.length();
		bool shoot = std::stoi(line.substr(shoot_start_pos, shoot_end_pos - shoot_start_pos));

		// Add the client info to the vector
		ClientParse client{ id, x, y, shoot };
		clients.push_back(client);
	}

	return clients;
}


//! Update all the clients
void Client::UpdateAllClients(const std::string& str)
{
	std::vector<ClientParse> clients = parse_client_info(str);

	// Update players
	for (auto& player : clients) {
		bool found = false;
		for (auto& existingPlayer : players) {
			if (existingPlayer._id == player.id) {
				existingPlayer.getComponent<PositionComponent>()->vector = Vector2{player.x, player.y};
				existingPlayer.getComponent<ShootComponent>()->isShooting = player.isShooting;
				found = true;
				break;
			}
		}

		// If the player was not found, add them to the list
		if (!found && player.id != _id) {
			players.push_back(Player{ GREEN, Vector2{player.x, player.y}, player.id });
		}
	}

	if (clients.size() == 1 && players.size() > 0)
		players.clear();

	if (players.size() >= clients.size() && players.size() > 0)
	{
		players.pop_back();
	}

	// Remove disconnected clients
	players.erase(std::remove_if(players.begin(), players.end(),
		[&](const Player& player) {
			bool found = false;
	for (const auto& client : clients) {
		if (client.id == player._id) {
			found = true;
			break;
		}
	}
	return !found;
		}),
		players.end());
}

//Update all Enemies
void Client::UpdateAllEnemies(std::string str)
{
	if (str.find("Client") == 0) {
		return;
	}

	std::istringstream iss(str);
	std::string token;
	std::vector<std::string> tokens;

	while (std::getline(iss, token, ';')) {
		if (token.find("enemies=") != std::string::npos)
			token.erase(0, 8); // remove "enemies=" prefix

		std::stringstream ss_enemy(token);
		std::string id_str = ss_enemy.str().substr(0, ss_enemy.str().find("x"));

		if (id_str.empty() || token.find("x") == std::string::npos || token.find("y") == std::string::npos) {
			// Skip invalid tokens
			continue;
		}

		size_t y_pos = token.find("y");
		if (y_pos != std::string::npos) {
			std::string y_str = token.substr(y_pos + 1);
			size_t non_digit_pos = y_str.find_first_not_of("0123456789.");
			if (non_digit_pos == std::string::npos) {
				y = std::stof(y_str);
			}
			else
				// Non-digit character found after "y"
				continue;
		}
		else
			continue;

		int id = std::stoi(id_str.substr(2));
		float x = 0.0f, y = 0.0f;

		try {
			x = std::stof(token.substr(token.find("x") + 1, token.find("y") - token.find("x") - 1));
			y = std::stof(token.substr(token.find("y") + 1));
		}
		catch (std::exception&) {
			// Skip tokens with invalid coordinates
			continue;
		}

		bool found = false;
		for (auto& enemy : enemies) {
			if (enemy.id == id) {
				enemy.rect.x = x;
				enemy.rect.y = y;
				found = true;
				break;
			}
		}
		if (!found) {
			enemies.push_back(EnemyData{ id, Rectangle{x, y, 50.0f, 50.0f} });
		}

	}

	// Remove any enemies that are not present in the provided string
	std::vector<EnemyData> toRemove;
	for (auto& enemy : enemies) {
		bool found = false;
		iss.clear();
		iss.seekg(0);
		while (std::getline(iss, token, ';')) {
			if (token.empty()) {
				continue;
			}

			std::string idStr = token.substr(2, token.find("x") - 2);

			std::string prefix = "emies=id";
			std::size_t pos = idStr.find(prefix);
			if (pos != std::string::npos) {
				idStr.erase(pos, prefix.length());
			}

			int id = std::stoi(idStr);

			if ((int)enemy.id == id) {
				found = true;
				break;
			}
		}

		if (!found) {
			toRemove.push_back(enemy);
		}
	}

	for (auto& enemy : toRemove) {
		enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	}
}


//! Handle the received data
void Client::Receive()
{
	_socket.async_receive_from(asio::buffer(_recv_buffer), _remote_endpoint,
		[this](std::error_code ec, std::size_t length) {
			if (!ec && length > 0) {
				std::cout << "Handle" << std::endl;

				Message msg;
				std::memcpy(&msg, _recv_buffer.data(), std::min(length, sizeof(Message)));
				std::string dataStr(msg.data.begin(), msg.data.begin() + std::min<size_t>(msg.data.size(), length));
				std::istringstream iss(dataStr);
				int nbChar;
				iss >> nbChar;
				iss.ignore(); // consume the newline character
				std::string str;
				std::getline(iss, str, '\0');
				str = str.substr(0, nbChar);

				std::cout << "string result : " << str << std::endl;

				handle_receive(msg, str);
			}
		});
}

//! Handle the received data
void Client::do_send(const Message& msg)
{
	// Send the message to the server

	_socket.async_send_to(asio::buffer(&msg, sizeof(msg) + 1), _server_endpoint,
		[this](std::error_code ec, std::size_t bytes_sent) {
			if (ec) {
				std::cerr << "Error sending message: " << ec.message() << std::endl;
			}
	Receive();
		});
}

void Client::KillEnemy(int id)
{
	Message msg;
	msg.id_player = _id;
	msg.type = ACTION::UPDATE;
	msg.msgType = MessageType::KILL_ENEMY;

	std::string str = std::to_string(id);
	msg.SetStringData(str);

	do_send(msg);
}

//! Handle the received data
void Client::handle_receive(const Message& message, std::string str)
{
	std::cout << "ID : " << std::to_string(message.id_player) << " MOVE : " << message.msgType << "\n";
	switch (message.msgType) {
	case MessageType::PLAYER_CONNECTED:
		_connected = true;
		_id = message.id_player;
		isConnected = true;
		break;
	case MessageType::UPDATE_ALL_CLIENTS:
		UpdateAllClients(str);
	case MessageType::UPDATE_ALL_ENEMIES:
		UpdateAllEnemies(str);
	}
}
//! Get the connected state
bool Client::getConnected()
{
	return _connected;
}