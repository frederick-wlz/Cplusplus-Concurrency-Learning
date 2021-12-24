//
// Created by wanglizhi04 on 2021/11/5.
//
#include <iostream>
#include <thread>

void task() {
    std::cout << "Hello world!" << std::endl;
}

int main() {
    std::thread thr(task);
    thr.join();

    return 0;
}
