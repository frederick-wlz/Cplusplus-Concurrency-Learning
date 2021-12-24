//
// Created by wanglizhi04 on 2021/11/9.
//
#include <iostream>
#include <thread>
#include <mutex>

std::timed_mutex time_mtx;

void task() {
    while (!time_mtx.try_lock_for(std::chrono::milliseconds(200))) {
        std::cout << "fail!" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << "success!" << std::endl;
    time_mtx.unlock();
}


int main() {
    std::thread threads[5];
    for (int i=0; i<5; i++) {
        threads[i] = std::thread(task);
    }
    for (auto& thr : threads) {
        thr.join();
    }

    std::cout << "Test over! " << std::endl;
    return 0;
}
