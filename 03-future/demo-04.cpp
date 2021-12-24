//
// Created by wanglizhi04 on 2021/11/17.
//

#include <iostream>
#include <thread>
#include <future>

void task(char letter, int time) {
    for (int i=0; i<10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << letter;
    }
}

int main() {
    std::cout << "Use the lanuch::async" << std::endl;
    std::future<void> task_1 = std::async(std::launch::async, task, '@', 100);
    std::future<void> task_2 = std::async(std::launch::async, task, '#', 100);
    task_1.get();
    task_2.get();
    std::cout << "\n\n";

    std::cout << "Use the lanuch::deferred" << std::endl;
    std::future<void> task_3 = std::async(std::launch::deferred, task, '@', 100);
    std::future<void> task_4 = std::async(std::launch::deferred, task, '#', 100);
    task_3.get();
    task_4.get();

    return 0;
}