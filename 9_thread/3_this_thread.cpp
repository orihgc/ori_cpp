//
// Created by ByteDance on 2023/4/16.
//

#include "thread"
#include "iostream"
#include <unistd.h>


using namespace std;

void func(int bh, const string &str) {
    for (int ii = 1; ii <= 10; ii++) {
        cout << "第" << ii << "次表白:亲爱的" << bh << "号，" << str << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    thread t1(func, 3, "我是一只傻傻鸟。");
    thread t2(func, 8, "我有一只小小鸟。");
    cout << "main_thread id:" << this_thread::get_id()<<endl;
    cout << "t1_thread id:" << t1.get_id()<<endl;
    cout << "t2_thread id:" << t2.get_id()<<endl;
//    t1.swap(t2);
//    cout << "t1_thread id:" << t1.get_id()<<endl;
//    cout << "t2_thread id:" << t2.get_id()<<endl;

    for (int ii = 1; ii <= 10; ii++) {
//        this_thread::yield();
        cout << "第" << ii << "次执行任务"<<endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    t1.join();
    t2.join();
    return 0;
}