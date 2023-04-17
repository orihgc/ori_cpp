//
// Created by ByteDance on 2023/4/16.
//

#include "thread"
#include "iostream"
#include <unistd.h>


using namespace std;

once_flag onceFlag;//once_flag全局变量，本质是取值为0和1的锁
void once_func(const int bh, const string& str) {
    cout << "once_func() bh= " << bh << ", str=" << str << endl;
}

void func(int bh, const string &str) {
    call_once(onceFlag, once_func,0,"ori");
    for (int ii = 1; ii <= 5; ii++) {
        cout << "第" << ii << "次表白:亲爱的" << bh << "号，" << str << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    thread t1(func, 3, "我是一只傻傻鸟。");
    thread t2(func, 8, "我有一只小小鸟。");

    t1.join();
    t2.join();
    return 0;
}
