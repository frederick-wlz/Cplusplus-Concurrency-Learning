//
// Created by wanglizhi04 on 2021/11/15.
//
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <future>         // std::promise, std::future

std::promise<int> prom;

void task(std::promise<int>& prom) {
    std::future<int> fut = prom.get_future();
    int value = fut.get();
    std::cout << "value: " << value << std::endl;
}

int main ()
{
    std::thread thr1(task, std::ref(prom));
    prom.set_value(10);
    thr1.join();

    prom = std::promise<int>();    // prom 被move赋值为一个新的 promise 对象.

    std::thread thr2 (task, std::ref(prom));
    prom.set_value (20);
    thr2.join();

    return 0;
}