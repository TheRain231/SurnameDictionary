#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip> // Для std::fixed и std::setprecision
#include "UserProcessor.h"
#include "User.h"

void processWithThreads(const std::vector<User>& users, int threadCount, const std::string& filename) {
    std::cout << "Обработка файла: " << filename << " с использованием " << threadCount << " потоков..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    // Инициализация обработчика с нужным количеством потоков
    UserProcessor processor(users, threadCount);
    processor.processUsers();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Вывод времени
    std::cout << "Время обработки "<< filename<<" с " << threadCount << " потоками: "
              << std::fixed << std::setprecision(6) << duration.count() << " секунд.\n" << std::endl;
}

int main() {
    const std::vector<std::string> filenames = {"input1m.txt"};

    for (const auto& filename : filenames) {
        std::vector<User> users = User::readUsersFromFile(filename);

        // Тесты с разным количеством потоков от 1 до 10
        for (int threadCount = 1; threadCount <= 5; ++threadCount) {
            processWithThreads(users, threadCount, filename);
        }
        std::cout<<"\n\n\n"<<std::endl;
    }

    return 0;
}
