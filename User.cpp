//
// Created by Андрей Степанов on 12.12.2024.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "User.h"



std::vector<User> User::readUsersFromFile(const std::string& filename) {
    std::vector<User> users;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return users;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string lastName, firstName, middleName, phoneNumber;

        // Парсим строку по разделителю ";"
        if (std::getline(ss, lastName, ';') &&
            std::getline(ss, firstName, ';') &&
            std::getline(ss, phoneNumber)) {
            User user = {lastName, firstName, phoneNumber};
            users.push_back(user);
            } else {
                std::cerr << "Ошибка обработки строки: " << line << std::endl;
            }
    }

    inputFile.close();
    return users;
}