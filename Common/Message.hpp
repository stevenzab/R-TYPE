/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <iostream>
#include <asio.hpp>
#include <string>

enum MessageType {
	PLAYER_CONNECTED,
	PLAYER_DISCONNECTED,
	UPDATE_CLIENT,
	UPDATE_ALL_CLIENTS,
	UPDATE_ALL_ENEMIES,
	KILL_ENEMY
};


enum ACTION {
    OK,
    KO,
    CONNECT,
    START,
    DISCONNECT,
    PLAYER_MOVE,
    UPDATE,
};


struct Message {
	ACTION type;
	MessageType msgType;
	uint8_t id_player;
	std::array<char, 1024> data;

	void SetStringData(const std::string& str) {
		std::string sizeStr = std::to_string(str.size()) + "\n";
		std::string remix = sizeStr + str;
		std::size_t size = std::min(remix.length(), data.size());
		std::memcpy(data.data(), remix.c_str(), size);
	}
};


#endif /* !MESSAGE_HPP_ */
