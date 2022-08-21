
#include <iostream>

using namespace std;

//region 概念
/**
 * C++为什么支持函数重载，C语言不支持函数重载？
 * C++代码产生函数符号的时候，是由函数名+参数列表组成的
 * C代码产生符号时，是由函数名决定
 *
 * 什么是函数重载？
 * 1、一组函数，函数名相同，参数个数或类型不同，叫函数重载
 * 2、一组函数要称得上重载，一定先是处在同一个作用域中
 * 3、const或者volatile，是怎么影响形参类型的？
 * 4、一组函数，函数名和参数列表都相同，仅仅返回值不同，不叫重载
 *
 * 多态
 * 静态（编译时期）的多态：函数重载、模板
 * 动态（运行时期）的多态：
 *
 * */
//endregion

bool compare(int a, int b) {
    return a > b;
}

bool compare(double a, double b) {
    return a > b;
}

bool compare(const char *a, const char *b) {
    return strcmp(a, b);
}

bool compare(const string &s1, const string &s2) {
    return s1 > s2;
}

int main() {
    return 0;
}
