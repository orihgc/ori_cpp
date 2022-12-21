//
// Created by ByteDance on 2022/12/18.
//

#include "string"
#include "iostream"
#include <functional>

using namespace std;

//region lambda表达式

///region 基础
///所谓捕获列表，其实可以理解为参数的一种类型，Lambda 表达式内部函数体在默认情况下是不能够使用函数体外部的变量的，
/// 这时候捕获列表可以起到传递外部数据的作用。根据传递的行为，捕获列表也分为以下几种：
/// 1.值捕获
void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // 这时, stored_value == 1, 而 value == 100.
    // 因为 copy_value 在创建时就保存了一份 value 的拷贝
}

/// 2.引用捕获
void lambda_reference_capture() {
    int value = 1;
    auto copy_value = [&value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // 这时, stored_value == 100, value == 100.
    // 因为 copy_value 保存的是引用
}

///3. 隐式捕获
/// 手动书写捕获列表有时候是非常复杂的，这种机械性的工作可以交给编译器来处理，这时候可以在捕获列表中写一个 & 或 = 向编译器声明采用引用捕获或者值捕获.
///
/// 总结一下，捕获提供了 Lambda 表达式对外部值进行使用的功能，捕获列表的最常用的四种形式可以是：
///
/// [] 空捕获列表
/// [name1, name2, ...] 捕获一系列变量
/// [&] 引用捕获, 让编译器自行推导引用列表
/// [=] 值捕获, 让编译器自行推导值捕获列表

/// 4. 表达式捕获
void lambda_expression_capture() {
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
        return x+y+v1+(*v2);
    };
    std::cout << add(3,4) << std::endl;
}

///endregion

///region 泛型lambda

/// auto 关键字不能够用在参数表里，这是因为这样的写法会与模板的功能产生冲突。
/// 但是 Lambda 表达式并不是普通函数，所以在没有明确指明参数表类型的情况下，Lambda 表达式并不能够模板化
/// 从 C++14 开始，Lambda 函数的形式参数可以使用 auto 关键字来产生意义上的泛型
void fun1(){
    auto add = [](auto x, auto y) {
        return x+y;
    };

    add(1, 2);
    add(1.1, 2.2);
}
///endregion
//endregion

//region 函数对象包装器
///region std:function
using foo = void(int); // 定义函数类型, using 的使用见上一节中的别名语法
void functional(foo f) { // 参数列表中定义的函数类型 foo 被视为退化后的函数指针类型 foo*
    f(1); // 通过函数指针调用函数
}

int fun2() {
    auto f = [](int value) {
        std::cout << value << std::endl;
    };
    functional(f); // 传递闭包对象，隐式转换为 foo* 类型的函数指针值
    f(1); // lambda 表达式调用
    return 0;
}

namespace runtime1{
    int foo(int para) {
        return para;
    }

    int fun3() {
        // std::function 包装了一个返回值为 int, 参数为 int 的函数
        std::function<int(int)> func = foo;

        int important = 10;
        std::function<int(int)> func2 = [&](int value) -> int {
            return 1+value+important;
        };
        std::cout << func(10) << std::endl;
        std::cout << func2(10) << std::endl;
    }
}
///endregion

///region std:bind和std::placeholder
/// 而 std::bind 则是用来绑定函数调用的参数的， 它解决的需求是我们有时候可能并不一定能够一次性获得调用某个函数的全部参数，
/// 通过这个函数， 我们可以将部分调用参数提前绑定到函数身上成为一个新的对象，然后在参数齐全后，完成调用。
namespace runtime2{
    int foo(int a, int b, int c) {
        ;
    }
    int fun4() {
        // 将参数1,2绑定到函数 foo 上，
        // 但使用 std::placeholders::_1 来对第一个参数进行占位
        auto bindFoo = std::bind(foo, std::placeholders::_1, 1,2);
        // 这时调用 bindFoo 时，只需要提供第一个参数即可
        bindFoo(1);
    }
}
///endregion
//endregion

int main(){
    runtime2::fun4();
}