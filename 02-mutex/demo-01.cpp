//
// Created by wanglizhi04 on 2021/11/9.
//
#include "./demo.h"
#include <iostream>
#include <thread>
#include <mutex>

volatile int counter(0);
std::mutex mtx;

void task() {
    for (int i=0; i<5; i++) {
        if (mtx.try_lock()) {   // only increase if currently not locked:
            ++counter;
            mtx.unlock();
        }
    }
}

int main () {
    std::thread threads[5];
    for (int i=0; i<5; ++i) {
        threads[i] = std::thread(task);
    }

    for (auto& thr : threads) {
        thr.join();
    }
    std::cout << "The final value is " << counter << std::endl;

    return 0;
}
