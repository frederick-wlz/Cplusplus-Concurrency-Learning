//
// Created by wanglizhi04 on 2021/11/19.
//

#include <iostream>
#include <thread>
#include <condition_variable>

std::condition_variable cond_var;
std::mutex mtx;
int goods(0);

bool have_goods() {
    return goods != 0;
}

void consume(int num) {
    for(int i=0; i<num; i++) {
        std::unique_lock<std::mutex> lock(mtx);
        cond_var.wait(lock, have_goods);
        goods--;
        std::cout << "Cost one point!" << std::endl;
    }

}

int main() {
    std::thread consumer(consume, 10);
    // 主线程为生产者线程, 生产 10 个物品.
    for (int i = 0; i < 10; ++i) {
        while (have_goods()) {
            std::this_thread::yield();
        }
        std::unique_lock <std::mutex> lock(mtx);
        goods++;
        std::cout << "Produce one point!" << std::endl;
        cond_var.notify_one();
    }

    consumer.join();
    return 0;
}