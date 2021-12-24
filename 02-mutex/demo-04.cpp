//
// Created by wanglizhi04 on 2021/11/15.
//
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void task_1() {
    // 以下两行语句等价于 std::unique_lock<std::mutex> lock(mtx);
    mtx.lock();
    // 使用adopt_lock，mutex应该是一个已经当前线程锁住的mutex对象
    std::unique_lock<std::mutex> lock(mtx, std::adopt_lock);

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "Task_1 has been completed!" << std::endl;
    // unique_lock生命期结束，自动释放锁
}

void task_2() {
    // 使用defer_lock，在初始化的时候并不锁住mutex对象
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    std::cout << "Task_2 is trying to catch the lock!" << std::endl;

    // 等价于 lock.lock();
    mtx.lock();
    std::cout << "Task_2 has been completed!" << std::endl;
    // unique_lock生命期结束，自动释放锁
}

int main() {
    std::thread thr1 = std::thread(task_1);
    std::thread thr2 = std::thread(task_2);

    thr1.join();
    thr2.join();

    return 0;
}


