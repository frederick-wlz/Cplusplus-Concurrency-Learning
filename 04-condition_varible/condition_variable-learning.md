# Condition_variable-Learning
Condition_variable头文件主要包含了与条件变量相关的类和函数。相关的类包括 `std::condition_variable` 和 `std::condition_variable_any`，还有枚举类型 `std::cv_status` 以及函数 `std::notify_all_at_thread_exit()`

## Condition_variable
`condition_variable` 是条件变量，当 `condition_variable` 对象的某个 `wait` 函数被调用的时候，它使用 `unique_lock`(通过 `mutex`) 来锁住当前线程。当前线程会一直被阻塞，直到另外一个线程在相同的 `condition_variable` 对象上调用了 ``notification 函数来唤醒当前线程。

`condition_variable` 对象通常使用 `unique_lock<std::mutex>` 来等待，如果需要使用另外的 `lockable` 类型，可以使用 `condition_variable_any` 类

### 构造函数
> 见案例 demo-01

|类型   | 函数  |
|  :----:  | :----:  |
|default (1) | condition_variable() |
|copy [deleted] (2) | condition_variable (const condition_variable&) = delete |
`condition_variable` 的拷贝构造函数被禁用，只提供了默认构造函数;

### 成员函数
#### wait
> 案例 demo-02

`condition_variable` 提供了两种 `wait()` 函数，当前线程调用 `wait()` 后将被阻塞(此时当前线程应该获得了锁)，直到另外某个线程调用 `notify()` 唤醒了当前线程;
    
|类型   | 函数  |
|  :----:  | :----:  |
|unconditional (1) | void wait (unique_lock<mutex>& lck) |
|predicate (2) | void wait (unique_lock<mutex>& lck, Predicate pred) |
在第一种情况下，在线程被阻塞时，该函数会自动调用 `unlock()` 释放锁，使得其他被阻塞在锁竞争上的线程得以继续执行。另外，一旦当前线程获得通知(notified，通常是另外某个线程调用 `notify` 唤醒了当前线程)，`wait()` 函数也是自动调用 `lock()`，使得锁的状态和 `wait` 函数被调用时相同。

在第二种情况下（即设置了 `Predicate`），只有当 `Predicate` 条件为 `false` 时调用 `wait()` 才会阻塞当前线程，并且在收到其他线程的通知后只有当 `Predicate` 为 `true` 时才会被解除阻塞

#### wait_for
> 案例 demo-03

|类型   | 函数  |
|  :----:  | :----:  |
|unconditional (1) | cv_status wait_for (unique_lock<mutex>& lck, const chrono::duration<Rep,Period>& rel_time) |
|predicate (2) | bool wait_for (unique_lock<mutex>& lck, const chrono::duration<Rep,Period>& rel_time, Predicate pred) |

第一种情况，与 `condition_variable::wait()` 类似，不过 `wait_for` 可以指定一个时间段，在当前线程收到通知或者指定的时间 `rel_time` 超时之前，该线程都会处于阻塞状态。而一旦超时或者收到了其他线程的通知，`wait_for` 返回，剩下的处理步骤和 wait() 类似。

第二种情况，`wait_for` 的重载版本（predicte(2)）的最后一个参数 `pred` 表示 `wait_for` 的预测条件，只有当 `pred` 条件为 `false` 时调用 `wait()` 才会阻塞当前线程，并且在收到其他线程的通知后只有当 `pred`为 `true` 时才会被解除阻塞；

#### wait_until
> 案例 demo-04

|类型   | 函数  |
|  :----:  | :----:  |
|unconditional (1) | cv_status wait_until (unique_lock<mutex>& lck, const chrono::time_point<Clock,Duration>& abs_time) |
|predicate (2) | bool wait_until (unique_lock<mutex>& lck, const chrono::time_point<Clock,Duration>& abs_time, Predicate pred) |
第一种情况， `condition_variable::wait_for` 类似，但是 `wait_until` 可以指定一个时间点，在当前线程收到通知或者指定的时间点 `abs_time` 超时之前，该线程都会处于阻塞状态。而一旦超时或者收到了其他线程的通知，`wait_until` 返回，剩下的处理步骤和 `wait_until()` 类似。

第二种情况，`wait_until` 的重载版本（predicte(2)）的最后一个参数 `pred` 表示 `wait_until` 的预测条件，只有当 `pred` 条件为 false 时调用 `wait()` 才会阻塞当前线程，并且在收到其他线程的通知后只有当 `pred` 为 `true` 时才会被解除阻塞

#### notify_one
> 案例 demo-05

唤醒某个等待(wait)线程。如果当前没有等待线程，则该函数什么也不做，如果同时存在多个等待线程，则唤醒某个线程是不确定的(unspecified)

#### notify_all
> 案例 demo-06

唤醒所有的等待(wait)线程。如果当前没有等待线程，则该函数什么也不做


## condition_variable_any
与 `condition_variable` 类似，只不过 `condition_variable_any` 的 `wait` 函数可以接受任何 `lockable` 参数，而 `condition_variable` 只能接受 `unique_lock<std::mutex>` 类型的参数，除此以外，和 `condition_variable` 几乎完全一样

### 成员函数
#### notify_all_at_thread_exit
函数原型为：`void notify_all_at_thread_exit (condition_variable& cond, unique_lock<mutex> lck)`

当调用该函数的线程退出时，所有在 cond 条件变量上等待的线程都会收到通知





















