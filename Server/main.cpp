#include <iostream>
#include <asio.hpp>
#include "Server.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>

const int num_threads = 4;

int main()
{
	std::vector<std::shared_ptr<std::thread>> threads;

	asio::io_context io_context;
	Server server(io_context, 12345);

	for (int i = 0; i < num_threads; ++i) {
		threads.emplace_back(std::make_shared<std::thread>([&]() { io_context.run(); }));
	}

	std::thread enemySpawnThread([&]() { server.spawnEnemies(); });
	std::thread updateEnemiesThread([&]() { server.updateEnemies(); });

	threads.emplace_back(std::make_shared<std::thread>(std::move(enemySpawnThread)));
	threads.emplace_back(std::make_shared<std::thread>(std::move(updateEnemiesThread)));

	std::string hostname = asio::ip::host_name();
	asio::ip::address_v4 ipv4_address = asio::ip::address_v4::any();
	asio::ip::tcp::resolver resolver(io_context);
	asio::ip::tcp::resolver::query query(hostname, "");

	auto endpoints = resolver.resolve(query);

	for (auto it = endpoints.begin(); it != endpoints.end(); ++it) {
    	if (it->endpoint().address().is_v4()) {
			ipv4_address = it->endpoint().address().to_v4();
			break;
    	}
    }

  std::cout << "Server started at " << ipv4_address.to_string() << ":" << "12345" << std::endl;

	for (auto& thread : threads)
	{
		thread->join();
	}

	return 0;
}
