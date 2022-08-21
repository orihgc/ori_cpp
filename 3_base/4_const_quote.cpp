

#include <iostream>

using namespace std;

//region 概念
/**
 * const和一级指针的结合
 * const和二级（多级）指针的结合
 *
 * const修饰的量常出现的错误：
 * 1、常量不能再作为左值 <= 不可直接修改常量值
 * 2、不能把常量的地址泄露给一个普通的指针或者普通的引用变量 <= 不可间接修改常量的值
 *
 * const和一级指针的结合
 * const int *p 可以任意指向不同的int类型的内存，但不能通过指针间接修改指向内存的值
 * int const *p 同上，建议上面的写法
 * int *const p 这个p指针现在是常量，不能指向其他内存，但是可以通过指针解引用修改指向的内存的值 （编译不过、待确定）
 * const int *const p 既不能修改指针p，也不能修改指针指向的内存*p
 *
 * 总结const和指针的类型转换公式
 * int* <= const int* 错误
 * const int* <= int* 可以
 * */
//endregion

//region const和一级指针

void fun1() {
    const int a = 10;
    const int *p1 = &a;
    int const *p2 = &a;
    ///下面编译不过，编译器不能同意*p=30; 不能通过指针解引用修改常量的值
    //    int *const p3 = &a;
    const int *const p4 = &a;

    int b = 20;
    const int *q2 = &b; ///const int* <= int*
    int *const q1 = &b; ///int* <= int*
    int *q3 = q1;///int* <= int*


    int *o1 = nullptr;
    int *const o2 = nullptr;
    cout << typeid(o1).name() << endl;
    cout << typeid(o2).name() << endl;
    ///const如果右边没有指针*的话，const不参与类型

    int c = 30;
    const int *s1 = &c;
    cout << typeid(s1).name() << endl;
}
//endregion

//region const和二级指针的结合
/**
 * int** <= const int** 是错误的
 * const int** <= int** 是错误的
 *
 * int** <= int* const* 是错误的
 * int *const* <= int** 是可以的
 * */
void fun2() {
    int a = 10;
    int *p = &a;
    /**
     * const int** <= int**
     * 上式如果能够成立的话，表示*q访问的就是p的内存
     * 如果给*q赋值 const int b=20; *q=&b;
     * 这样就把b常量的地址泄露给普通的指针了。
     * */
    //const int **q = &p;

    ///改成常量指针即可
    const int *p1 = &a;
    const int **q2 = &p1;


    cout << sizeof(p) << endl;
}
//endregion

//region const、一级指针、引用的结合使用
int fun3() {

    //写一句代码，在内存的0x0018ff44处写一个4字节的10
    int *&&p = (int *) 0x0018ff44;
    *p = 10;

    int a = 10;
    int *p1 = &a;
    int *&q = p1;


    cout << p;

}
//endregion

int main() {
    fun3();
    return 0;
}
