#Thread-Learning 
> std::thread 在 <thread> 头文件中声明，因此使用 std::thread 时需要包含 <thread> 头文件。

## thread构造函数
> 案例参考demo-01

|类型   | 构造函数  |
|  :----:  | :----:  |
|default (1) | thread() noexcept; |
|initialization (2) | explicit thread (Fn&& fn, Args&&... args); |
|copy [deleted] (3) | thread (const thread&) = delete;|
|move (4) | thread (thread&& x) noexcept; |

1. 默认构造函数，创建一个空的 thread 执行对象。
2. 初始化构造函数，创建一个 thread对象，该 thread对象可被 joinable，新产生的线程会调用 fn 函数，该函数的参数由 args 给出。
3. 拷贝构造函数(被禁用)，意味着 thread 不可被拷贝构造。
4. move 构造函数，move 构造函数，调用成功之后 x 不代表任何 thread 执行对象。

注意：可被 joinable 的 thread 对象必须在他们销毁之前被主线程 join 或者将其设置为 detached.

## move 赋值操作
> 案例参考demo-02

|类型   | 构造函数  |
|  :----:  | :----:  |
| move (1) | thread& operator= (thread&& rhs) noexcept; |
| copy [deleted] (2) |thread& operator= (const thread&) = delete; |

1. move 赋值操作，如果当前对象不可 joinable，需要传递一个右值引用(rhs)给 move 赋值操作；如果当前对象可被 joinable，则 terminate() 报错。
2. 拷贝赋值操作被禁用，thread 对象不可被拷贝。

## 成员函数
### get_id : 获取线程 ID。
### joinable : 检查线程是否可被 join。
### join : Join 线程。
### detach : Detach 线程
### swap : Swap 线程 。
### native_handle : 返回 native handle。
### hardware_concurrency [static] : 检测硬件并发特性。