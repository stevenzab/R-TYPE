# 1. Introduction

The User Datagram Protocol (UDP) is a communication protocol used for sending and receiving data over a network. This document describes the use of UDP for online game messaging, including the message types, actions, and message format.

# 2. Protocol

## 2.1 MessageType

The enum MessageType defines the different types of messages that can be sent between players and the server in the game.

    enum MessageType {
        PLAYER_CONNECTED,
        PLAYER_DISCONNECTED,
        UPDATE_CLIENT,
        UPDATE_ALL_CLIENTS,
        UPDATE_ALL_ENEMIES,
        KILL_ENEMY
    };

    PLAYER_CONNECTED (0) - Indicates that a new player has connected to the game.
    PLAYER_DISCONNECTED (1) - Indicates that a player has disconnected from the game.
    UPDATE_CLIENT (2) - Indicates the player's new position and shot.
    UPDATE_ALL_CLIENTS (3) - Indicate new positions and shoot other players.
    UPDATE_ALL_ENEMIES (4) - Indicate new enemy positions to other players.
    KILL_ENEMY (5) - Indicates that an enemy has been killed.

## 2.2 Action

The enum ACTION defines the different types of actions that can be performed between the client and the server.

    enum ACTION {
        OK,
        KO,
        CONNECT,
        START,
        DISCONNECT,
        PLAYER_MOVE,
        UPDATE,
    };

    OK (0) - Indicates success or acknowledgement of an operation.
    KO (1) - Indicates failure or rejection of an operation.
    CONNECT (2) - Indicates a client's request to connect to the server.
    START (3) - Indicates the server's instruction to start the game.
    DISCONNECT (4) - Indicates a client's request to disconnect from the server.
    PLAYER_MOVE (5) - Indicates that the player make a move.
    UPDATE (6) - Indicates that player change position, shoot and numbers of ennemy.

## 2.3 Message 
The struct Message is the format used for sending messages between the client and server.

    struct Message {
        ACTION type;
        MessageType msgType;
        uint8_t id_player;
        std::array<char, 1024> data;
    };

Message Format:

    4 bytes - ACTION - Indicates the type of action being performed.
    4 bytes - MessageType - Indicates the type of message being sent.
    1 byte - id_player - Indicates the ID of the player who sent the message.
    4 bytes - size - Indicates the size of the data payload.
    n bytes - data - The payload of the message.

## 3. Conclusion

UDP is a simple and lightweight protocol that is commonly used for applications that require fast, low-latency data transmission, such as online gaming, real-time streaming, and VoIP (Voice over Internet Protocol) services. This document specifies the use of UDP for online game messaging, including the message types, actions, and message format.