//
// Created by Денис Громачихин on 15.12.2024.
//

#include "UserProcessor.h"
#include <iostream>

UserProcessor::UserProcessor(const std::vector<User>& users, int threadCount)
        : users(users), threadCount(threadCount) {}

void UserProcessor::processUsers() {
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back(&UserProcessor::workerThread, this);
    }

    // Ожидаем завершения всех потоков
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void UserProcessor::workerThread() {
    while (true) {
        User user;
        {
            std::lock_guard<std::mutex> lock(mtx);  // Блокировка для работы с очередью пользователей
            if (users.empty()) {
                return;  // Выход из потока, если нет пользователей
            }
            user = users.back();
            users.pop_back();
        }

        // Создание имени файла на основе первой буквы фамилии
        std::string fileName(1, user.lastName[0]);
        fileName += ".txt";

        // Блокировка только нужного мьютекса для данного файла
        std::lock_guard<std::mutex> fileLock(fileMutexes[fileName]);

        // Запись в файл
        std::ofstream outFile(fileName, std::ios::app);
        if (outFile.is_open()) {
            outFile << user.lastName << " "
                    << user.firstName << " "
                    << user.phoneNumber << std::endl;
            outFile.close();
        } else {
            std::cerr << "Не удалось открыть файл: " << fileName << std::endl;
        }
    }
}


