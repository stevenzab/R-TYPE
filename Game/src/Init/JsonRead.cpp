/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** JsonRead
*/

#include "JsonRead.hpp"

JsonRead::JsonRead(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open JSON file : " << filename << std::endl;
        exit(84);
    }
    try {
        file >> json;
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(84);
    }
}

JsonRead::JsonRead(const nlohmann::json &value)
{
    json = value;
}

JsonRead::~JsonRead()
{
}