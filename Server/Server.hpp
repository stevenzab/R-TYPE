/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Serveur
*/

#define TEST_HPP_
#include <iostream>
#include <array>
#include <asio.hpp>
#include <vector>
#include <set>
#include <chrono>
#include <thread>
#include <random>
#include "../Common/Message.hpp"

using asio::ip::udp;

struct PlayerFromServer {
	udp::endpoint endpoint;
	int id;
	float x;
	float y;
	bool isShooting;
};

class Enemy {
public:
	Enemy(int id, float x, float y) : id(id), _x(x), _y(y) {}
	float _x, _y;
	int id;
};

class Server {
public:
	void updateEnemies();
	void spawnEnemies();
	Server(asio::io_context& io_context, unsigned short port);
	~Server();
	void start_receive();
	void StopServer();
	void start_send();
	void handle_receive(const Message& msg, udp::endpoint endpointRcv);
	void handle_send(std::error_code const& error, std::size_t bytes_sent);
	void do_receive();
	void handle_connect(const Message& msg, udp::endpoint endpointRcv);
	void send_other_clients(const Message& msg, udp::endpoint endpointRcv);
	void handle_move(Message, udp::endpoint endpointTcv);
	void handle_disconnect(const Message&, udp::endpoint endpointRcv);
	void UpdateClient(const std::string& msg, udp::endpoint endpointRcv);
	void UpdateAllClients(const Message& msg, udp::endpoint endpointRcv);
	void RemoveEnemy(std::string dataString);
	void handle_receive(const Message& msg, udp::endpoint endpointRcv, std::string dataString);

private:
	asio::io_context& _io_context;
	udp::socket _socket;
	udp::endpoint _recv_endpoint;
	std::vector<PlayerFromServer> _clients;
	std::array<char, 1024> _recv_buffer;
	std::vector<Enemy> _enemies;
	std::mutex _enemyMutex;
};
