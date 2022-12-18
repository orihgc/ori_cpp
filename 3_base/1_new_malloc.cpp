//
// Created by orihgc on 2022/8/5.
//

#include <cstdlib>
#include <new>
#include <iostream>

using namespace std;

/**
 * malloc和free都是C的库函数
 * new和delete，称作运算符
 *
 * new和malloc的区别:
 * 1、new不仅能够内存开辟，还能做初始化操作，而malloc只开辟内存。
 * 2、malloc开辟内存失败，通过返回值和nullptr比较；而new开辟内存失败，是通过抛出bad_alloc类型的异常来判断
 * */
int main() {
    int *p = (int *) malloc(sizeof(int));
    if (p == nullptr)return -1;
    *p = 20;
    free(p);

    try {
        int *p2 = new int(20);
        delete p2;
    } catch (const bad_alloc &e) {
    }

    ///开辟数组
    int *q = (int *) malloc(sizeof(int) * 20);
    if (q == nullptr)return -1;
    free(q);


    //int *q1 = new int[20];
    int *q1 = new int[20]();//会全部初始化为0
    cout << *(q1 + 1) << endl;
    delete[] q1;

    ///new 有多少种
    int *p3 = new int(20);
    int *p4 = new(nothrow) int;///不抛出异常的new
    const int *p5 = new const int(40);///常量指针
    int data = 0;
    int *p6 = new(&data) int(50);///在一个指定内存进行初始化
    
    return 0;
}