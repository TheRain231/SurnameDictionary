//
// Created by Денис Громачихин on 15.12.2024.
//

#ifndef SURNAMEDICTIONARY_USER_H
#define SURNAMEDICTIONARY_USER_H

#include <string>

class User {
public:
    std::string lastName;
    std::string firstName;
    std::string phoneNumber;

    static std::vector<User> readUsersFromFile(const std::string& filename);
};

#endif //SURNAMEDICTIONARY_USER_H
