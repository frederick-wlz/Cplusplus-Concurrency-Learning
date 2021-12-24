//
// Created by wanglizhi04 on 2021/11/11.
//
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void task(int num) {
    mtx.lock();

    // 构造一个 lock_guard 对象， Tag 参数为 std::adopt_lock，表明当前线程已经获得了锁
    // 此后 mtx 对象的解锁操作交由 lock_guard 对象 lck 来管理
    std::lock_guard<std::mutex> lock(mtx, std::adopt_lock);
    std::cout << "I get the lock, my ID is " << num << std::endl;

    // 此处，lock 的生命周期结束之后，mtx 对象会自动解锁。
}

int main() {
    std::thread threads[5];
    for (int i = 0; i < 5; i++) {
        threads[i] = std::thread(task, i + 1);
    }

    for (auto &thr: threads) {
        thr.join();
    }
    return 0;
}