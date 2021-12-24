//
// Created by wanglizhi04 on 2021/11/5.
//

#include "demo.h"
#include <thread>
#include <iostream>


int main() {
    // 默认构造，空的线程对象，未运行
    std::thread thr1;

    //  函数初始化构造，创建一个线程对象，可被join
    std::thread thr2(task, 2);

    // 拷贝构造，被禁止
    // std::thread thr3(thr1);

    // 移动构造，调用成功后tmp_thr不再是一个线程对象
    std::thread tmp_thr(task, 4);
    std::thread thr4(std::move(tmp_thr));

    // 未运行 或者 已经不存在的线程对象无法被join
    // thr1.join();
    // thr3.join();
    thr2.join();
    thr4.join();

    std::cout << "The task is finished！" << std::endl;
    return 0;
}

