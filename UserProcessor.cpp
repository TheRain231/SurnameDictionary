//
// Created by Денис Громачихин on 15.12.2024.
//

#include "UserProcessor.h"
#include <fstream>
#include <iostream>
#include <mutex>

UserProcessor::UserProcessor(const std::vector<User>& users, int threadCount)
        : users(users), threadCount(threadCount) {}

void UserProcessor::processUsers() {
    for (int i = 0; i < threadCount; ++i) {
        std::cout << "Запуск потока #" << i + 1 << std::endl;
        threads.emplace_back(&UserProcessor::workerThread, this, i + 1); // Передаем номер потока
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void UserProcessor::workerThread(int threadNumber) {
    while (true) {
        User user;
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (users.empty()) {
                std::cout << "Поток #" << threadNumber << " завершает работу (нет пользователей для обработки)." << std::endl;
                return;
            }
            user = users.back();
            users.pop_back();
        }

        // Создание имени файла на основе первой буквы фамилии
        std::string fileName(1, user.lastName[0]);
        fileName += ".txt";

        // Защищенный доступ к файлу
        {
            std::lock_guard<std::mutex> fileLock(fileMutex);  // Мьютекс для синхронизации записи в файлы

            std::ofstream outFile(fileName, std::ios::app);
            if (outFile.is_open()) {
                outFile << user.lastName << " "
                        << user.firstName << " "
                        << user.phoneNumber << std::endl;

                std::cout << "Поток #" << threadNumber << " записал в файл " << fileName
                          << ": " << user.lastName << " "
                          << user.firstName << " "
                          << user.phoneNumber << std::endl;

                outFile.close();
            } else {
                std::cerr << "Поток #" << threadNumber << " не смог открыть файл: " << fileName << std::endl;
            }
        }
    }
}

