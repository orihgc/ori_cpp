//
// Created by ByteDance on 2023/4/17.
//
#include "mutex"
#include "iostream"
#include "thread"

using namespace std;
//region 互斥锁
mutex mtx;
int a;

void func() {
    for (int i = 0; i < 100000; ++i) {
        cout << "线程" << this_thread::get_id() << "申请加锁......." << endl;
        mtx.lock();
        cout << "线程" << this_thread::get_id() << "加锁成功" << endl;
        a++;
        this_thread::sleep_for(chrono::seconds(5));
        mtx.unlock();
        cout << "线程" << this_thread::get_id() << "释放了加锁" << endl;
        this_thread::sleep_for(chrono::seconds(1));

    }
}

int test1() {
    timed_mutex tm;
    tm.try_lock_for(chrono::seconds(10));
    thread t1(func);
    thread t2(func);
    t1.join();
    t2.join();
    return 0;
}
//endregion

//region 递归互斥锁

class AA {
private:
    //递归锁
    recursive_mutex m_mutex_;
public:
    void fun1() {
        m_mutex_.lock();
        cout << "调用了fun1()" << endl;
        m_mutex_.unlock();
    }

    void fun2() {
        m_mutex_.lock();
        cout << "调用了fun2()" << endl;
        fun1();
        m_mutex_.unlock();
    }
};
//endregion

//region lock_guard
/**
 *
 * */

void fun3() {
    for (int i = 0; i < 100000; ++i) {
        lock_guard<mutex> lockGuard(mtx);
        a++;
    }
}

//endregion

int main() {
    thread t1(&fun3);
    thread t2(&fun3);
    t1.join();
    t2.join();
    cout<<a;
}


