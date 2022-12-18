
#include <iostream>
#include "SeqStack.h"
#include "SeqStack.cpp"

using namespace std;

/**
 * 对象默认的拷贝构造是做内存的数据拷贝
 * 关键是对象如果占用外部资源，那么浅拷贝就有问题。
 * */
int main() {
    SeqStack s1(10);
    ///出错 浅拷贝，SeqStack中的指针指向堆中的同一块资源，析构时就会出问题
    s1.push(20);
    s1.push(30);
    SeqStack s2 = s1;
    SeqStack s3(s2);

    ///默认的赋值函数，做直接的内存拷贝
    s2 = s1;
    ///自赋值
    s1 = s1;

    return 0;
}
