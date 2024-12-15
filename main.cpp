#include <iostream>
#include <vector>
#include "UserProcessor.h"
#include "User.h"

int main() {
    const std::string filename = "input.txt";
    std::vector<User> users = User::readUsersFromFile(filename);

    for (const auto& user : users) {
        std::cout << "Фамилия: " << user.lastName
                  << ", Имя: " << user.firstName
                  << ", Номер: " << user.phoneNumber << std::endl;
    }

    const int threadCount = 4; // Количество потоков
    UserProcessor processor(users, threadCount);
    processor.processUsers();

    return 0;
}