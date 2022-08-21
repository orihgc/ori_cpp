//
// Created by orihgc on 2022/8/10.
//

#include <cstdlib>
#include "iostream"
#include "SeqStack.h"

using namespace std;

/**
 * 构造函数：定义对象时，自动调用的
 * 析构函数：不带参数，不能重载。
 *
 * .data对象: 程序启动时构造，结束时析构
 * heap：new 时构造，delete析构
 * stack：声明时构造，作用域结束时析构
 * */

SeqStack::SeqStack(int size) {
    cout << this << " SeqStack" << endl;
    _pStack = new int[size];
    _top = -1;
    _size = size;
}

///深拷贝
SeqStack::SeqStack(const SeqStack &src) {
    cout << this << " SeqStack(const SeqStack &src)" << endl;
    _pStack = new int[src._size];
    ///为啥不用memcpy?
    ///数组里是整型是没有问题的，数组内的数据不占用外部资源，则可以使用memcpy，否则只能用for循环
    for (int i = 0; i < src._top; ++i) {
        _pStack[i] = src._pStack[i];
    }
    _top = src._top;
    _size = src._size;
}

///赋值函数重载
void SeqStack::operator=(const SeqStack &src) {
    cout << this << " operator=" << endl;
    ///防止自赋值
    if (this == &src)return;
    ///需要先释放当前对象占用的外部资源
    delete[]_pStack;

    _pStack = new int[src._size];
    for (int i = 0; i < src._top; ++i) {
        _pStack[i] = src._pStack[i];
    }
    _top = src._top;
    _size = src._size;
}

SeqStack::~SeqStack() {
    cout << this << " ~SeqStack" << endl;
    delete[]_pStack;
    _pStack = nullptr;
}

void SeqStack::push(int value) {
    if (full())resize();
    _pStack[++_top] = value;
}

void SeqStack::pop() {
    if (empty())return;
    --_top;
}

int SeqStack::top() {
    return _pStack[_top];
}

bool SeqStack::empty() { return _top == -1; }

bool SeqStack::full() { return _top == _size - 1; }

void SeqStack::resize() {
    int *pTmp = new int[_size * 2];
    for (int i = 0; i < _size; ++i) {
        pTmp[i] = _pStack[i];
    }
    delete[]_pStack;
    _pStack = pTmp;
    _size * 2;
}





//SeqStack seqStack2;

int fun() {
    ///在堆上开辟
    SeqStack *ps = new SeqStack(60);/// malloc 开辟内存，+ SeqStack(60) 构造函数
    ps->push(20);
    delete ps;///先调用ps->~SeqStack() 然后 free(ps)

    ///在栈上开辟
    ///声明一个对象时， 开辟内存，调用构造函数
    SeqStack seqStack(5);
    for (int i = 0; i < 15; ++i) {
        seqStack.push(rand() % 100);
    }
    while (!seqStack.empty()) {
        cout << seqStack.top() << " ";
        seqStack.pop();
    }
    cout << endl;
    SeqStack seqStack1;
    ///出作用域，调用析构函数
    return 0;
}