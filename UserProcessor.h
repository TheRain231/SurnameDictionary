//
// Created by Денис Громачихин on 15.12.2024.
//

#ifndef USERPROCESSOR_H
#define USERPROCESSOR_H

#include <vector>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <fstream>
#include "User.h"

class UserProcessor {
public:
    // Конструктор
    UserProcessor(const std::vector<User>& users, int threadCount);

    // Метод для обработки пользователей
    void processUsers();

private:
    // Метод, выполняемый каждым потоком
    void workerThread();

    // Очередь пользователей для обработки
    std::vector<User> users;

    // Мьютекс для синхронизации доступа к очереди пользователей
    std::mutex mtx;

    // Список потоков
    std::vector<std::thread> threads;

    // Количество потоков
    int threadCount;

    // Словарь для хранения мьютексов для каждого файла
    std::unordered_map<std::string, std::mutex> fileMutexes;
};

#endif // USERPROCESSOR_H

