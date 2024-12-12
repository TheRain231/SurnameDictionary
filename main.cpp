#include "User.cpp"
#include <iostream>
#include <vector>

int main() {
    const std::string filename = "input.txt";
    std::vector<User> users = readUsersFromFile(filename);

    for (const auto& user : users) {
        std::cout << "Фамилия: " << user.lastName
                  << ", Имя: " << user.firstName
                  << ", Отчество: " << user.middleName
                  << ", Номер: " << user.phoneNumber << std::endl;
    }

    return 0;
}