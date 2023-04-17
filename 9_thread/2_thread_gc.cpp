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
        sleep(1); // 休眠 1 秒
    }
}

int main() {
    // 用普通函数创建线程。
    thread t1(func, 3, "我是一只傻傻鸟。");
    thread t2(func, 8, "我有一只小小鸟。");

    cout << "任务开始。\n";
    for (int ii = 0; ii < 12; ii++) {
        cout << "执行任务中......\n";
        sleep(1); // 假设执行任务需要时间。
    }
    cout << "任务完成。\n";
    t1.detach();
    t2.detach();

    cout << t1.joinable();

}
