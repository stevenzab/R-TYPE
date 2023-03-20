/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-danny.duong
** File description:
** JsonRead
*/

#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#ifndef JSONREAD_HPP_
#define JSONREAD_HPP_

class JsonRead {
    public:
        JsonRead(const std::string& filename);
        JsonRead(const nlohmann::json &value);
        ~JsonRead();
        template<typename T>
        T getValueJson(const std::string& value) const {
            if (!json.contains(value))
                throw std::invalid_argument("Key not found in JSON object");
            return json[value].get<T>();
        };
        nlohmann::json getJsonValue() const {return json;};
        nlohmann::json getValueJsonFromString(const std::string& value) const {return json[value];};
    protected:
    private:
        nlohmann::json json;
};

#endif /* !JSONREAD_HPP_ */
