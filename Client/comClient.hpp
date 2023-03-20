#include <iostream>
#include <asio.hpp>

#ifndef COMCLIENT_HPP_

#define COMCLIENT_HPP_

struct Message {
    uint8_t type;
    uint16_t length;
    uint8_t player_id;
  //  uint8_t data[MAX_DATA_SIZE];
};

class Client {
public:
    Client(asio::io_context& io_context, const std::string& host, const std::string& port) : _socket(io_context) { };
    ~Client(){};
    void send(const Message& message);
    void receive(Message& message);

private:
    asio::ip::udp::socket _socket;
};
#endif /* !COMCLIENT_HPP_ */