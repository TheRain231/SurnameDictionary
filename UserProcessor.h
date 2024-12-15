//
// Created by Денис Громачихин on 15.12.2024.
//

#ifndef USERPROCESSOR_H
#define USERPROCESSOR_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include "User.h"

class UserProcessor {
public:
    UserProcessor(const std::vector<User>& users, int threadCount);
    void processUsers();

private:
    void workerThread(int threadNumber);

    std::vector<User> users;
    int threadCount;
    std::vector<std::thread> threads;
    std::mutex mtx; // Для защиты users
    std::mutex fileMutex; // Для защиты файлов
};


#endif // USERPROCESSOR_H
