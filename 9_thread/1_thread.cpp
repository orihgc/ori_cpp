//
// Created by ByteDance on 2023/4/16.
//
#include "thread"
#include "iostream"

#include <unistd.h>

using namespace std;

void fun(int bh, const string &str) {
    for (int i = 1; i <= 10; ++i) {
        cout << "第" << i << "次: 你好," << bh << " " << str << endl;
        sleep(1);
    }
}

//仿函数
class mythread1 {
public:
    void operator()(int bh, const string &str) {
        for (int i = 1; i <= 10; ++i) {
            cout << "第" << i << "次: 你好," << bh << " " << str << endl;
            sleep(1);
        }
    }
};

class mythread2 {
public:
    static void func(int bh, const string &str) {
        for (int i = 1; i <= 10; ++i) {
            cout << "第" << i << "次: 你好," << bh << " " << str << endl;
            sleep(1);
        }
    }
};

class mythread3 {
public:
    void func(int bh, const string &str) {
        for (int i = 1; i <= 10; ++i) {
            cout << "第" << i << "次: 你好," << bh << " " << str << endl;
            sleep(1);
        }
    }
};

int main() {
    //普通函数创建线程
    thread t1(fun, 1, "hello world!");
    thread t2(fun, 2, "我是一只小小鸟");

    //lambda创建线程
    auto f = [](int bh, const string &str) {
        for (int i = 1; i <= 10; ++i) {
            cout << "第" << i << "次: 你好," << bh << " " << str << endl;
            sleep(1);
        }
    };
    thread t3(f, 3, "我有一只大傻鸟");

    //仿函数
    thread t4(mythread1(), 4, "你有一只大乌龟");

    //用类的静态成员函数创建线程
    thread t5(mythread2::func, 5, "你是一只傻傻鸟");

    //用类的普通成员函数创建线程
    mythread3 myth;
    thread t6(&mythread3::func, &myth, 6, "我是一只傻傻鸟。");///必须先创建类的对象，且保证对象的生命周期比子线程要长

    for (int i = 0; i <= 10; ++i) {
        cout << "第" << i << "次" << endl;
        sleep(1);
    }

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
}