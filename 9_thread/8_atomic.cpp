//
// Created by ByteDance on 2023/5/17.
//
#include "iostream"
#include "thread"

using namespace std;

atomic_int aa = 0;

void func() {
    for (int i = 0; i < 100000; ++i) {
        aa++;
    }
}

int main() {
    thread t1(func);
    thread t2(func);
    t1.join();
    t2.join();
    cout << aa;
}
