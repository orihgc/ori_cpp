//
// Created by orihgc on 2022/8/8.
//

#include <iostream>

using namespace std;

///值传递，这里传递变量的地址
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

///引用传递，通过给变量赋予别名的方式，直接改变引用变量的值
void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

/**
 * 引用和指针的区别
 * 引用是一种更安全的指针
 * 1、引用是必须初始化的，指针可以不初始化
 * 2、定义引用变量和指针变量在汇编上是没有区别的；通过引用变量修改所引用内存的值，和通过指针解引用修改指针指向的内存的值，其底层指令也是一样的
 * 3、引用只有一级引用，没有多级引用;指针可以有多级指针
 *
 * 右值引用
 * 1、int &&c=20; 专门用来引用右值类型，指令上，可以自动产生临时量
 * 2、右值引用本身是一个左值，只能用左值引用来引用它
 * 3、不能用一个右值引用变量，来引用一个左值
 * */
void fun1() {
    int a = 10;
    int *p = &a;
    int &b = a;

    *p = 20;
    cout << a << " " << *p << " " << b << endl;

    b = 30;
    cout << a << " " << *p << " " << b << endl;

    int c = 10;
    int d = 20;


    swap(c, d);

    cout << c << " " << d;
}

/**
 * 引用数组
 * */
void fun2() {
    int array[5] = {};
    int *p = array;

    ///定义引用变量，引用array数组
    int (&q)[5] = array;
    int (*o)[5] = &array;///等同于 int *o=array;

    cout << sizeof(array) << endl;
    cout << sizeof(p) << endl;
    cout << sizeof(q) << endl;
    cout << q[0] << endl;
}

/**
 * 左值引用
 * 右值引用
 * */
void fun3() {
    ///左值,有内存，有名字，值可以修改
    int a = 10;
    int &b = a;
    ///右值，20，没内存，没名字
    int &&c = 20;
    int &e=c;///一个右值引用变量，本身是一个左值

    /// int temp=20; int &d=temp;
    /// 和上面一行的汇编码一样，但是个常量引用
    const int &d = 20;

    cout << c << endl;
}


int main() {
    fun3();
    return 0;
}


