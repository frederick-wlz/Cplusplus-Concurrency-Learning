//
// Created by wanglizhi04 on 2021/11/9.
//

//
// Created by wanglizhi04 on 2021/11/5.
//

#include "demo.h"
#include <thread>
#include <iostream>

int main() {
    std::thread thr5 = std::thread(task, 5);;
    thr5.join();
    std::cout << "The task is finished！" << std::endl;
    return 0;
}

