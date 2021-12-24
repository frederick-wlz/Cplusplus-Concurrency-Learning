//
// Created by wanglizhi04 on 2021/11/17.
//

#include <iostream>                // std::cout
#include <thread>                // std::thread, std::this_thread::yield
#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable

std::mutex mtx;
std::condition_variable cv;

int cargo = 0;
bool shipment_available()
{
    return cargo != 0;
}

// 消费者线程.
void consume(int n) {
    std::cout << "111" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::unique_lock <std::mutex> lck(mtx);
        std::cout << "333" << std::endl;
        cv.wait(lck, shipment_available);
        std::cout << "###" << std::endl;
        std::cout << cargo << '\n';
        cargo = 0;
    }
}

int main()
{
    std::thread consumer_thread(consume, 10); // 消费者线程.
    std::cout << "222" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "444" << std::endl;
    // 主线程为生产者线程, 生产 10 个物品.
    for (int i = 0; i < 10; ++i) {
        std::cout << "555" << std::endl;
        while (shipment_available())
            std::this_thread::yield();
        std::cout << "666" << std::endl;
        std::unique_lock <std::mutex> lck(mtx);
        std::cout << "%%%" << std::endl;
        cargo = i + 1;
        cv.notify_one();
    }

    consumer_thread.join();

    return 0;
}