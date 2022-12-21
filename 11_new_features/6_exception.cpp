//
// Created by ByteDance on 2022/12/18.
//
#include "iostream"

using namespace std;

void throwE() { throw 1; }

void noBlockThrow() { throwE(); }

void blockThrow() noexcept { throwE(); }

int main() {
    try {
        throwE();
    } catch (int) {
        cout << "Found throw" << endl;
    }

    try {
        noBlockThrow();
    } catch (int) {
        cout << "noBlockThrow" << endl;
    }
    /**直接调用中断程序，防止异常传播*/
    blockThrow();
}

