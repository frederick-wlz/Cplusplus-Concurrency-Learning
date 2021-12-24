# Future-Learning
`future` 头文件中包含了以下几个类和函数
1. Promise 类：std::promise, std::package_task
2. Futures 类：std::future, shared_future.
3. Providers 函数：std::async()
4. 其他类型：std::future_error, std::future_errc, std::future_status, std::launch

## Promise类

promise 对象可以保存某一类型 T 的值，该值可被 future 对象读取（可能在另外一个线程中），因此 promise 也提供了一种线程同步的手段。在 promise 对象构造时可以和一个共享状态（通常是std::future）相关联，并可以在相关联的共享状态(std::future)上保存一个类型为 T 的值。

可以通过 get_future 来获取与该 promise 对象相关联的 future 对象，调用该函数之后，两个对象共享相同的共享状态(shared state)

promise 对象是异步 Provider，它可以在某一时刻设置共享状态的值。
future 对象可以异步返回共享状态的值，或者在必要的情况下阻塞调用者并等待共享状态标志变为 ready，然后才能获取共享状态的值。

### 构造函数
> 案例 demo-01

|类型   | 构造函数  |
|  :----:  | :----:  |
|default (1) | promise() |
|with allocator (2) | promise (allocator_arg_t aa, const Alloc& alloc) |
|copy [deleted] (3) | promise (const promise&) = delete |
|move (4) | promise (promise&& x) noexcept |
1. 默认构造函数，初始化一个空的共享状态。
2. 带自定义内存分配器的构造函数，与默认构造函数类似，但是使用自定义分配器来分配共享状态。
3. 拷贝构造函数，被禁用。
4. 移动构造函数。 operater= 只有 move 语义，因为 std::promise 对象是禁止拷贝的。

### 相关成员函数
1. get_future
该函数返回一个与 promise 共享状态相关联的 future 。返回的 future 对象可以访问由 promise 对象设置在共享状态上的值或者某个异常对象。只能从 promise 共享状态获取一个 future 对象。在调用该函数之后，promise 对象通常会在某个时间点准备好(设置一个值或者一个异常对象)，如果不设置值或者异常，promise 对象在析构时会自动地设置一个 future_error 异常(broken_promise)来设置其自身的准备状态。上面的例子中已经提到了 get_future，此处不再重复。

2. set_value
设置共享状态的值，此后 promise 的共享状态标志变为 ready
    |类型   | 函数  |
    |  :----:  | :----:  |
    | generic template (1) | void set_value (const T& val) |
    | generic template (1) | void set_value (T&& val) |
    | specializations (2) | void promise<R&>::set_value (R& val) |
    | specializations (2) | void promise<void>::set_value (void) | 

3. set_exception
为 promise 设置异常，此后 promise 的共享状态变标志变为 ready

4. set_value_at_thread_exit
设置共享状态的值，但是不将共享状态的标志设置为 ready，当线程退出时该 promise 对象会自动设置为 ready。如果某个 std::future 对象与该 promise 对象的共享状态相关联，并且该 future 正在调用 get，则调用 get 的线程会被阻塞，当线程退出时，调用 future::get 的线程解除阻塞，同时 get 返回 set_value_at_thread_exit 所设置的值。注意，该函数已经设置了 promise 共享状态的值，如果在线程结束之前有其他设置或者修改共享状态的值的操作，则会抛出 future_error( promise_already_satisfied )。

5. std::promise::swap
交换 promise 的共享状态;

## Packaged_task类
`packaged_task` 包装一个可调用的对象，并且允许异步获取该可调用对象产生的结果，从包装可调用对象意义上来讲，`std::packaged_task` 与 `std::function` 类似，只不过 `std::packaged_task` 将其包装的可调用对象的执行结果传递给一个 `std::future` 对象（该对象通常在另外一个线程中获取 `std::packaged_task` 任务的执行结果）；

`packaged_task` 对象内部包含了两个最基本元素： 
1. 被包装的任务(stored task)，任务(task)是一个可调用的对象，如函数指针、成员函数指针或者函数对象；
2. 共享状态(shared state)，用于保存任务的返回值，可以通过 std::future 对象来达到异步访问共享状态的效果。

`std::packaged_task` 对象是异步 Provider，它在某一时刻通过调用被包装的任务来设置共享状态的值。
`std::future` 对象是一个异步返回对象，通过它可以获得共享状态的值，当然在必要的时候需要等待共享状态标志变为 ready。
`std::packaged_task` 的共享状态的生命周期一直持续到最后一个与之相关联的对象被释放或者销毁为止。

### 构造函数
|类型   | 函数  |
|  :----:  | :----:  |
|default (1) | packaged_task() noexcept |
|initialization (2) | explicit packaged_task (Fn&& fn) |
|with allocator (3) | explicit packaged_task (allocator_arg_t aa, const Alloc& alloc, Fn&& fn) |
|copy [deleted] (4) | packaged_task (const packaged_task&) = delete |
|move (5) | packaged_task (packaged_task&& x) noexcept |
1. 默认构造函数，初始化一个空的共享状态，并且该 packaged_task 对象无包装任务。
2. 初始化一个共享状态，并且被包装任务由参数 fn 指定。
3. 带自定义内存分配器的构造函数，与默认构造函数类似，但是使用自定义分配器来分配共享状态。
4. 拷贝构造函数，被禁用。
5. 移动构造函数。

### 相关成员函数
1. valid：检查当前 packaged_task 是否和一个有效的共享状态相关联，对于由默认构造函数生成的 packaged_task 对象，该函数返回 false，除非中间进行了 move 赋值操作或者 swap 操作
2. get_future：返回一个与 packaged_task 对象共享状态相关的 future 对象。返回的 future 对象可以获得由另外一个线程在该 packaged_task 对象的共享状态上设置的某个值或者异常。
3. std::packaged_task::operator()(Args... args) 
   调用该 packaged_task 对象所包装的对象(通常为函数指针，函数对象，lambda 表达式等)，传入的参数为 args. 调用该函数一般会发生两种情况：
      - 如果成功调用 packaged_task 所包装的对象，则返回值（如果被包装的对象有返回值的话）被保存在 packaged_task 的共享状态中。
      - 如果调用 packaged_task 所包装的对象失败，并且抛出了异常，则异常也会被保存在 packaged_task 的共享状态中。 
   
      以上两种情况都使共享状态的标志变为 ready，因此其他等待该共享状态的线程可以获取共享状态的值或者异常并继续执行下去。 
   由于被包装的任务在 packaged_task 构造时指定，因此调用 operator() 的效果由 packaged_task 对象构造时所指定的可调用对象来决定：
   - 如果被包装的任务是函数指针或者函数对象，调用 std::packaged_task::operator() 只是将参数传递给被包装的对象。
   - 如果被包装的任务是指向类的非静态成员函数的指针，那么 std::packaged_task::operator() 的第一个参数应该指定为成员函数被调用的那个对象，剩余的参数作为该成员函数的参数。
   - 如果被包装的任务是指向类的非静态成员变量，那么 std::packaged_task::operator() 只允许单个参数
4. make_ready_at_thread_exit：该函数会调用被包装的任务，并向任务传递参数，类似 std::packaged_task 的 operator() 成员函数。但是与 operator() 函数不同的是，make_ready_at_thread_exit 并不会立即设置共享状态的标志为 ready，而是在线程退出时设置共享状态的标志。
如果与该 packaged_task 共享状态相关联的 future 对象在 future::get 处等待，则当前的 future::get 调用会被阻塞，直到线程退出。而一旦线程退出，future::get 调用继续执行，或者抛出异常。
注意，该函数已经设置了 promise 共享状态的值，如果在线程结束之前有其他设置或者修改共享状态的值的操作，则会抛出 future_error
5. swap：交换 packaged_task 的共享状态。
6. reset：重置 packaged_task 的共享状态，但是保留之前的被包装的任务

## Future类
`future` 可以用来获取异步任务的结果，因此可以把它当成一种简单的线程间同步的手段。`future` 通常由某个 `Provider` 创建，你可以把 `Provider` 想象成一个异步任务的提供者，`Provider` 在某个线程中设置共享状态的值，与该共享状态相关联的 `future` 对象调用 `get`（通常在另外一个线程中） 获取该值，如果共享状态的标志不为 `ready`，则调用 `future::get` 会阻塞当前的调用者，直到 `Provider` 设置了共享状态的值（此时共享状态的标志变为 ready），`future::get` 返回异步任务的值或异常（如果发生了异常）。

一个有效(valid)的 `future` 对象通常由以下三种 `Provider` 创建，并和某个共享状态相关联。`Provider` 可以是函数或者类，分别是：

- `std::async` 函数；
- `std::promise::get_future`，`get_future` 为 `promise` 类的成员函数；
- `std::packaged_task::get_future`，此时 `get_future` 为 `packaged_task` 的成员函数；
一个 `future` 对象只有在有效(valid)的情况下才有用(useful)，由 `future` 默认构造函数创建的 `future` 对象不是有效的（除非当前非有效的 future 对象被 move 赋值另一个有效的 future 对象）。

### 构造函数
`future` 一般由 `std::async`, `std::promise::get_future`, `std::packaged_task::get_future` 创建，不过也提供了构造函数，如下表所示：

|类型   | 函数  |
|  :----:  | :----:  |
|default (1) | future() noexcept |
|copy [deleted] (2) | future (const future&) = delete |
|move (3) | future (future&& x) noexcept |
`future` 的拷贝构造函数是被禁用的，只提供了默认的构造函数和 `move` 构造函数。另外，`future` 的普通赋值操作也被禁用，只提供了 `move` 赋值操作；

### 成员函数
- `get`：当与该 `future` 对象相关联的共享状态标志变为 `ready` 后，调用该函数将返回保存在共享状态中的值，如果共享状态的标志不为 `ready`，则调用该函数会阻塞当前的调用者，而此后一旦共享状态的标志变为 `ready`，`get` 返回 `Provider` 所设置的共享状态的值或者异常（如果抛出了异常）
- `valid`：检查当前的 `future` 对象是否有效，即释放与某个共享状态相关联。一个有效的 `future` 对象只能通过 `std::async`, `std::future::get_future` 或者 `std::packaged_task::get_future` 来初始化。另外由 `future` 默认构造函数创建的 `future` 对象是无效(invalid)的，当然通过 `future::move` 赋值后该 `future` 对象也可以变为 `valid`
- `wait`：等待与当前 `future` 对象相关联的共享状态的标志变为 `ready`，如果共享状态的标志不是 `ready`（此时 Provider 没有在共享状态上设置值（或者异常）），调用该函数会被阻塞当前线程，直到共享状态的标志变为 ready。
一旦共享状态的标志变为 `ready`，`wait` 函数返回，当前线程被解除阻塞，但是 `wait` 并不读取共享状态的值或者异常
- `wait_for`：与`wait`函数不同，`wait_for` 可以设置一个时间段 `rel_time`，如果共享状态的标志在该时间段结束之前没有被 `Provider` 设置为 `ready`，则调用 `wait_for` 的线程被阻塞，在等待了 `rel_time` 的时间长度后 `wait_for` 返回，返回值如下：
  - `future_status::ready`	共享状态的标志已经变为 ready，即 Provider 在共享状态上设置了值或者异常。
  - `future_status::timeout`	超时，即在规定的时间内共享状态的标志没有变为 ready。
  - `future_status::deferred`	共享状态包含一个 deferred 函数。
- `wait_until`：与`wait`函数不同，`wait_until` 可以设置一个时间段 `abs_time`，如果共享状态的标志在该时间段结束之前没有被 `Provider` 设置为 `ready`，则调用 `wait_for` 的线程被阻塞，在等待了 `abs_time` 的时间长度后 `wait_for` 返回，返回值同 `wait_for` 返回值；

### 相关枚举类型

- `future_errc`
  
    |类型   | 取值  | 描述 | 
  |  :----:  | :----:  | :----:  | 
  |broken_promise|	0	|与该 std::future 共享状态相关联的 std::promise 对象在设置值或者异常之前一被销毁 |
  |future_already_retrieved | 	1|	与该 std::future 对象相关联的共享状态的值已经被当前 Provider 获取了，即调用了 std::future::get 函数|
  |promise_already_satisfied |	2|	std::promise 对象已经对共享状态设置了某一值或者异常|
  |no_state	| 3	|无共享状态|
  
- `future_status`：`future_status` 类型主要用在 `future`中的 `wait_for` 和 `wait_until` 两个函数

    |类型   | 取值  | 描述 |
    |  :----:  | :----:  | :----:  |
    |uture_status::ready |	0	| wait_for(或wait_until) 因为共享状态的标志变为 ready 而返回|
    |future_status::timeout	| 1	 | 超时，即 wait_for(或wait_until) 因为在指定的时间段（或时刻）内共享状态的标志依然没有变为 ready 而返回| 
    |future_status::deferred |	2| 	共享状态包含了 deferred 函数 |

- `launch`：该枚举类型主要是在调用 std::async 设置异步任务的启动策略的

    |类型  |  描述 |
    |  :----:  | :----:  |
    |launch::async	|Asynchronous: 异步任务会在另外一个线程中调用，并通过共享状态返回异步任务的结果（一般是调用 std::future::get() 获取异步任务的结果）|
    |launch::deferred	|Deferred: 异步任务将会在共享状态被访问时调用，相当与按需调用（即延迟(deferred)调用）|

## std::shared_future 介绍
`shared_future` 与 `future` 类似，但是 `shared_future` 可以拷贝、多个 `shared_future` 可以共享某个共享状态的最终结果(即共享状态的某个值或者异常)。`shared_future` 可以通过某个 `future` 对象隐式转换（参见 std::shared_future 的构造函数），或者通过 `future::share` 显示转换，无论哪种转换，被转换的那个 `future` 对象都会变为无效`not-valid`.

### 构造函数

|类型   | 函数  |
|  :----:  | :----:  |
|default (1) | shared_future() noexcept |
|copy (2) | shared_future (const shared_future& x) |
|move (3) | shared_future (shared_future&& x) noexcept |
|move from future (4) | shared_future (future<T>&& x) noexcept |

### 成员函数
见`future`成员函数

## Async
> 案例 demo-04

### 函数原型
|类型   | 函数  |
|  :----:  | :----:  |
|unspecified policy (1) | future<typename result_of<Fn(Args...)>::type> async(Fn&& fn, Args&&... args) |
|specific policy (2) | future<typename result_of<Fn(Args...)>::type> async(launch policy, Fn&& fn, Args&&... args) |

表格中两组 `async` 的不同之处是第一类 `async` 没有指定异步任务（即执行某一函数）的启动策略(`launch policy`)，而第二类函数指定了启动策略，详见 `launch` 枚举类型，指定启动策略的函数的 `policy` 参数可以是`launch::async`，`launch::deferred`，以及两者的按位或( | )。
`async` 的 `fn` 和 `args` 参数用来指定异步任务及其参数。另外，`async` 返回一个 `future` 对象，通过该对象可以获取异步任务的值或异常（如果异步任务抛出了异常）
















