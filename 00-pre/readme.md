## C++相关资料
http://www.open-std.org/jtc1/sc22/wg21/

C++0x/C++11 Support in GCC：http://gcc.gnu.org/projects/cxx0x.html

What is C++0x：https://www2.research.att.com/~bs/what-is-2009.pdf

Overview of the New C++：http://www.artima.com/shop/overview_of_the_new_cpp

Overview of the New C++ (C++0x).pdf：http://ishare.iask.sina.com.cn/f/20120005.html?from=like

A Brief Look at C++0x：http://www.artima.com/cppsource/cpp0x.html

Summary of C++11 Feature Availability in gcc and MSVC：http://www.aristeia.com/C++11/C++11FeatureAvailability.html

C++ 11: Come Closer：http://www.codeproject.com/Articles/344282/Cplusplus-11-Come-Closer

C++11 threads, locks and condition variables： http://www.codeproject.com/Articles/598695/Cplusplus11-threads-locks-and-condition-variables

Move Semantics and Perfect Forwarding in C++11：http://www.codeproject.com/Articles/397492/Move-Semantics-and-Perfect-Forwarding-in-Cplusplus

http://solarianprogrammer.com/categories/C++11/

C++11 Concurrency：http://www.baptiste-wicht.com/2012/03/cpp11-concurrency-part1-start-threads/

http://www.hpl.hp.com/personal/Hans_Boehm/misc_slides/sfacm-cleaned.pdf

http://en.cppreference.com/w/cpp/thread

http://isocpp.org/blog/2012/12/c11-a-cheat-sheet-alex-sinyakov

The Biggest Changes in C++11：http://blog.smartbear.com/c-plus-plus/the-biggest-changes-in-c11-and-why-you-should-care/

Ten C++11 Features Every C++ Developer Should Use：http://www.codeproject.com/Articles/570638/Ten-Cplusplus11-Features-Every-Cplusplus-Developer

C++11 – A Glance [part 1 of n]：http://www.codeproject.com/Articles/312029/Cplusplus11-A-Glance-part-1-of-n

C++11 – A Glance [part 2 of n]：http://www.codeproject.com/Articles/314415/Cplusplus11-A-Glance-part-2-of-n

C++11（及现代C++风格）和快速迭代式开发：http://mindhacks.cn/2012/08/27/modern-cpp-practices/

Lambda Functions in C++11 - the Definitive Guide：http://www.cprogramming.com/c++11/c++11-lambda-closures.html

Better types in C++11 - nullptr, enum classes (strongly typed enumerations) and cstdint：http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html

Rvalue-references-and-move-semantics-in-c++11：http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html

http://www.gotw.ca/publications/index.htm

http://www.devx.com/SpecialReports/Door/38865

Multi-threading in C++0x：http://accu.org/index.php/journals/1584

C++ 0X feature summary cheat sheat：http://www.iesensor.com/blog/2011/05/31/c-0x-feature-summary-cheat-sheat/

Multithreading in C++0x part 1: Starting Threads：http://www.justsoftwaresolutions.co.uk/threading/multithreading-in-c++0x-part-1-starting-threads.html

http://en.cppreference.com/w/cpp/thread

http://www.cplusplus.com/reference/multithreading/


## 与 C++11 多线程相关的头文件
C++11 新标准中引入了五个头文件来支持多线程编程，他们分别是<atomic>, <thread>, <mutex>, <condition_variable> 和 <future>

- <atomic>：该头文主要声明了两个类, std::atomic 和 std::atomic_flag，另外还声明了一套 C 风格的原子类型和与 C 兼容的原子操作的函数。
- <thread>：该头文件主要声明了 std::thread 类，另外 std::this_thread 命名空间也在该头文件中。
- <mutex>：该头文件主要声明了与互斥量(mutex)相关的类，包括 std::mutex 系列类，std::lock_guard, std::unique_lock, 以及其他的类型和函数。
- <condition_variable>：该头文件主要声明了与条件变量相关的类，包括 std::condition_variable 和 std::condition_variable_any。
- <future>：该头文件主要声明了 std::promise, std::package_task 两个 Provider 类，以及 std::future 和 std::shared_future 两个 Future 类，另外还有一些与之相关的类型和函数，std::async() 函数就声明在此头文件中。