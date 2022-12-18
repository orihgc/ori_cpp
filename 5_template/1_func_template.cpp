//
// Created by orihgc on 2022/8/16.
//

#include <iostream>

using namespace std;


/**
 * C++函数模板
 * 模板的意义： 对类型也可以进行参数化了
 * int sum(int a,int b){return a+b}
 *
 * 函数模板
 * 模板的实例化 <= 函数调用点进行实例化
 * 模板函数  <= 才是要经过编译器所编译的
 *
 * 模板类型参数 typename/class
 * 模板非类型参数
 *
 * 模板的实参推演 => 可以根据用户传入的实参的类型，来推导出模板类型参数的具体类型
 * 模板的特例化 => 不是编译器提供的，而是用户提供的
 *
 * 模板函数、模板的特例化、非模板函数的重载关系
 *
 * 模板代码不能在一个文件中定义，在另一个文件中使用的。
 * 模板代码调用之前，一定要看到模板定义的地方，这样的话，模板才能够进行正常的实例化，产生能够被编译器编译的代码
 * 如果非要在不同文件中定义和使用则通过
 * template bool compare<int>(int,int);
 * 告诉编译器，进行指定类型的实例化
 * 所以模板代码都是放在头文件当中，然后在源文件当中直接#include包含。
 *
 * */

///函数模板
///定义一个模板参数列表
template<typename T>
bool compare(T a, T b) {
    return a > b;
}

///模板的特例化
///针对compare模板，提供const char*类型的特例化版本
template<>
bool compare<const char *>(const char *a, const char *b) {
    cout << "compare char*" << endl;
    return strcmp(a, b) > 0;
}

///非模板函数
bool compare(const char *a, const char *b) {
    cout << "normal compare char*" << endl;
    return strcmp(a, b) > 0;
}


/**
 * 在函数调用点，编译器用用户指定的类型，从原模板实例化一份函数代码出来
 * */
int fun1() {
    ///函数调用点
    compare<int>(1, 2);
    compare<double>(2.0, 1.0);
    ///模板的实参推演
    compare(20, 30);
    ///
    cout << compare<int>(30, 30.0) << endl;

    ///针对某些类型不满足需求，则提供函数模板的特例化版本
    compare("caa", "bbb");///编译器优先把compare处理成函数名字，没有的话，才去找compare模板
    cout << compare<const char *>("caa", "bbb");
    return 0;
}

/**
 * 函数模板
 * SIZE 模板的非类型参数 都是常量，只能使用，而不能修改
 * */
template<typename T, int SIZE>
void sort(T *arr) {
    for (int i = 0; i < SIZE - 1; ++i) {
        for (int j = 0; j < SIZE - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}


int fun2() {
    int arr[] = {12, 5, 7, 89, 32, 21, 35};
    const int size = sizeof(arr) / sizeof(arr[0]);
    sort<int, size>(arr);
    for (const auto &item: arr) {
        cout << item << endl;
    }
    return 0;
}

int main(){
    fun2();
    return 0;
}