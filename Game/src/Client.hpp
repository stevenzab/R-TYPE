/*
** EPITECH PROJECT, 2023
** Client.hpp
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include "../../Common/Message.hpp"
#include "Game.hpp"
#include "Gameplay/Ennemy.hpp"
#include <asio.hpp>

using namespace asio::ip;
#define PORT 1234;
const int MAX_MESSAGE_SIZE = 1024; // Maximum message size in bytes

//! Class Client
struct ClientParse {
	int id;
	float x;
	float y;
	bool isShooting;
};

struct EnemyData {
	int id;
	Rectangle rect;

	bool operator==(const EnemyData& other) const {
		return id == other.id;
	}
};

//! Class Client
class Client {
public:
	//! Constructeur class Client
	Client(asio::io_context& io_context, const std::string& host, const std::string& port);
	void SendConnected();
	void SendData(std::string data);
	void SendDisconnect();
	void SendShoot();
	void Receive();
	void Close();
	bool getConnected();
	void SendUp();
	void SendDown();
	void SendLeft();
	void SendRight();
	void do_send(const Message& msg);
	void KillEnemy(int id);
	void UpdateClient(int x, int y, bool isShooting);
	void UpdateAllClients(const std::string& str);
	void UpdateAllEnemies(std::string str);
	void SendUpdateClient();
	std::vector<ClientParse> parse_client_info(const std::string& input);

	udp::socket _socket;
	int _id;
	std::vector<Player> players;
	std::vector<EnemyData> enemies;
	bool isConnected;
protected:

private:
	void handle_receive(const Message& message, std::string str);
	void LogMsg(const Message& msgToSend);

private:
	// asio::io_context& _io_context;
	udp::resolver _resolver;
	udp::endpoint _remote_endpoint;
	udp::endpoint server_endpoint;
	bool _connected;
	int _nb_player;
	int x;
	int y;
	udp::endpoint _server_endpoint;

	std::array<char, 1024> _recv_buffer;
};

#endif /* !CLIENT_HPP_ */
