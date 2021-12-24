//
// Created by wanglizhi04 on 2021/11/15.
//
#include <iostream>
#include <thread>
#include <future>

int main() {
    // 默认构造，无任务
    std::packaged_task<int(int)> task;

    // 使用lambda表达式初始化对象
    std::packaged_task<int(int)> task_tmp([](int x){return x*2;});

    // 移动构造
    task = std::move(task_tmp);

    // 获取关联的future对象
    std::future<int> fut = task.get_future();

    // 线程分离，调用task任务
    std::thread(std::move(task), 20).detach();

    // 等待任务完成，读取结果
    int value = fut.get();
    std::cout << "value = " << value << std::endl;
    return 0;
}