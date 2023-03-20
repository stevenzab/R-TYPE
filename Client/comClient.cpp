/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** 
*/

#include "comClient.hpp"

Client::Client(asio::io_context& io_context, const std::string& host, const std::string& port): _socket(io_context) {
    
    asio::ip::udp::resolver resolver(io_context);
        asio::ip::udp::resolver::results_type endpoints = resolver.resolve(host, port);

        _socket.async_connect(*endpoints.begin(), [this](const asio::error_code& error) {
            if (!error) {
                std::cout << "Connected to server" << std::endl;
            }
            else {
                std::cout << "Error connecting to server: " << error.message() << std::endl;
            }
        });

}

void Client::send(const Message& message) {
   _socket.async_send(asio::buffer(&message, sizeof(Message)), [this](const asio::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        std::cout << "Sent message to server" << std::endl;
    }
    else {
        std::cout << "Error sending message to server: " << error.message() << std::endl;
    }   
});

}

void Client::receive(Message& message) {
        _socket.async_receive(asio::buffer(&message, sizeof(Message)), [this, &message](const asio::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                std::cout << "Received message from server" << std::endl;
            }
            else {
                std::cout << "Error receiving message from server: " << error.message() << std::endl;
            }
        });
    }