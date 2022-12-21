//
// Created by ByteDance on 2022/12/18.
//

#include <initializer_list>
#include "iostream"
#include "vector"

using namespace std;

//region 常量
/**
 * nullptr
 * */
void foo(char *) {
    std::cout << "foo(char*) is called" << std::endl;
}

void foo(int i) {
    std::cout << "foo(int) is called" << std::endl;
}

int fun1() {
    if (std::is_same<decltype(NULL), decltype(0)>::value)
        std::cout << "NULL == 0" << std::endl;
    if (std::is_same<decltype(NULL), decltype((void *) 0)>::value)
        std::cout << "NULL == (void *)0" << std::endl;
    if (std::is_same<decltype(NULL), std::nullptr_t>::value)
        std::cout << "NULL == nullptr" << std::endl;

    foo(0);          // 调用 foo(int)
    // foo(NULL);    // 该行不能通过编译
    foo(nullptr);    // 调用 foo(char*)
    return 0;
}

/**
 * constexpr
 *  让用户显式的声明函数或对象构造函数在编译期会成为常量表达式
 *  这个关键字明确的告诉编译器应该去验证 len_foo 在编译期就应该是一个常量表达式
 * */
#define LEN 10

int len_foo() {
    int i = 2;
    return i;
}

constexpr int len_foo_constexpr() {
    return 5;
}

constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

int fun2() {
    char arr_1[10];                      // 合法
    char arr_2[LEN];                     // 合法

    int len = 10;
//     char arr_3[len];                  // 非法

    const int len_2 = len + 1;
    constexpr int len_2_constexpr = 1 + 2 + 3;

    ///因为 C++ 标准中数组的长度必须是一个常量表达式，而对于 len_2 而言，这是一个 const 常数，而不是一个常量表达式
//     char arr_4[len_2];                // 非法
    char arr_4[len_2_constexpr];         // 合法

    /// C++98之前的编译器无法得知len_foo()返回的是一个常数，导致了非法的产生
//     char arr_5[len_foo()+5];          // 非法
    char arr_6[len_foo_constexpr() + 1]; // 合法

    std::cout << fibonacci(10) << std::endl;
    // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    std::cout << fibonacci(10) << std::endl;
    return 0;
}
//endregion

//region 变量及其初始化

//region if/switch变量声明强化
int fun3() {
    std::vector<int> vec = {1, 2, 3, 4};

    // 在 c++17 之前
    const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
    if (itr != vec.end()) {
        *itr = 3;
    }

    // 需要重新定义一个新的变量
    const std::vector<int>::iterator itr2 = std::find(vec.begin(), vec.end(), 3);
    if (itr2 != vec.end()) {
        *itr2 = 4;
    }

    // c++17之后
    // 可以将临时变量放到 if 语句内
    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);
            itr != vec.end()) {
        *itr = 4;
    }

    // 将输出 1, 4, 3, 4
    for (std::vector<int>::iterator element = vec.begin(); element != vec.end();
         ++element)
        std::cout << *element << std::endl;
}
//endregion

//region 初始化列表
/// 在传统 C++ 中，不同的对象有着不同的初始化方法，例如普通数组、 POD （Plain Old Data，即没有构造、析构和虚函数的类或结构体） 类型
/// 都可以使用 {} 进行初始化，也就是我们所说的初始化列表
/// 而对于类对象的初始化，要么需要通过拷贝构造、要么就需要使用 () 进行。 这些不同方法都针对各自对象，不能通用
class Foo {
public:
    int value_a;
    int value_b;

    Foo(int a, int b) : value_a(a), value_b(b) {}
};

int fun4() {
    // before C++11
    int arr[3] = {1, 2, 3};
    Foo foo(1, 2);
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::cout << "arr[0]: " << arr[0] << std::endl;
    std::cout << "foo:" << foo.value_a << ", " << foo.value_b << std::endl;
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}
/// 为解决这个问题，C++11 首先把初始化列表的概念绑定到类型上，称其为 std::initializer_list
/// 允许构造函数或其他函数像参数一样使用初始化列表，这就为类对象的初始化与普通数组和 POD 的初始化方法提供了统一的桥梁

class MagicFoo {
public:
    std::vector<int> vec;

    MagicFoo(std::initializer_list<int> list) {
        for (std::initializer_list<int>::iterator it = list.begin();
             it != list.end(); ++it)
            vec.push_back(*it);
    }

    void foo(std::initializer_list<int> list) {
        for (std::initializer_list<int>::iterator it = list.begin();
             it != list.end(); ++it)
            vec.push_back(*it);
    }
};

int fun5() {
    // after C++11
    MagicFoo magicFoo = {1, 2, 3, 4, 5};

    std::cout << "magicFoo: ";
    for (std::vector<int>::iterator it = magicFoo.vec.begin();
         it != magicFoo.vec.end(); ++it)
        std::cout << *it << std::endl;

    magicFoo.foo({6, 7, 8, 9});

    ///其次，C++11 还提供了统一的语法来初始化任意的对象
    Foo foo2{3, 4};
}

//endregion

//region 结构化绑定
std::tuple<int, double, std::string> f() {
    return std::make_tuple(1, 2.3, "456");
}

int fun6() {
    auto [x, y, z] = f();
    std::cout << x << ", " << y << ", " << z << std::endl;
    return 0;
}
//endregion

//endregion

//region 类型推导
//region auto
void fun7() {
    MagicFoo magicFoo = {1, 2, 3, 4, 5};
    std::cout << "magicFoo: ";
    for (auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
}
///注意auto 还不能用于推导数组类型
//endregion

//region decltype
///decltype 关键字是为了解决 auto 关键字只能对变量进行类型推导的缺陷而出现的。
void fun8() {
    auto x = 1;
    auto y = 2;
    decltype(x + y) z;

    if (std::is_same<decltype(x), int>::value)
        std::cout << "type x == int" << std::endl;
    if (std::is_same<decltype(x), float>::value)
        std::cout << "type x == float" << std::endl;
    if (std::is_same<decltype(x), decltype(z)>::value)
        std::cout << "type z == type x" << std::endl;

    cout<<z<<endl;
}
//endregion

///region 尾返回类型推导
///c++ 14 支持
template<typename T, typename U>
auto add2(T x, U y) -> decltype(x+y){
    return x + y;
}

template<typename T, typename U>
auto add3(T x, U y){
    return x + y;
}

int fun9(){
// after c++11
    auto w = add2<int, double>(1, 2.0);
    if (std::is_same<decltype(w), double>::value) {
        std::cout << "w is double: ";
    }
    std::cout << w << std::endl;

// after c++14
    auto q = add3<double, int>(1.0, 2);
    std::cout << "q: " << q << std::endl;
}
///endregion

///region decltype(auto)
///endregion
//endregion

///region 控制流
///C++17 将 constexpr 这个关键字引入到 if 语句中，允许在代码中声明常量表达式的判断条件
template<typename T>
auto print_type_info(const T& t) {
    if constexpr (std::is_integral<T>::value) {
        return t + 1;
    } else {
        return t + 0.001;
    }
}
int fun10() {
    std::cout << print_type_info(5) << std::endl;
    std::cout << print_type_info(3.14) << std::endl;
}
///endregion

///region 区间for迭代
int fun11() {
    std::vector<int> vec = {1, 2, 3, 4};
    if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) *itr = 4;
    for (auto element : vec)
        std::cout << element << std::endl; // read only

    for (auto &element : vec) {
        element += 1;                      // writeable
    }

    for (auto element : vec)
        std::cout << element << std::endl; // read only
}
///endregion

//region 模板

///region 外部模板

///C++11 引入了外部模板，扩充了原来的强制编译器在特定位置实例化模板的语法
template class std::vector<bool>;          // 强行实例化
extern template class std::vector<double>; // 不在该当前编译文件中实例化模板
///endregion

///region 尖括号">"

///在传统 C++ 的编译器中，>>一律被当做右移运算符来进行处理。但实际上我们很容易就写出了嵌套模板的代码：
std::vector<std::vector<int>> matrix;
///这在传统 C++ 编译器下是不能够被编译的，而 C++11 开始，连续的右尖括号将变得合法，并且能够顺利通过编译。甚至于像下面这种写法都能够通过编译：
template<bool T>
class MagicType {
    bool magic = T;
};

std::vector<MagicType<(1>2)>> magic;
///endregion

///region 类型别名模板

///在了解类型别名模板之前，需要理解『模板』和『类型』之间的不同。仔细体会这句话：模板是用来产生类型的。
/// 在传统 C++ 中，typedef 可以为类型定义一个新的名称，但是却没有办法为模板定义一个新的名称。因为，模板不是类型。例如：
template<typename T, typename U>
class MagicType1 {
public:
    T dark;
    U magic;
};

// 不合法
template<typename T>
//typedef MagicType1<std::vector<T>, std::string> FakeDarkMagic;

///C++11 使用 using 引入了下面这种形式的写法，并且同时支持对传统 typedef 相同的功效：
void fun12(){
    typedef int (*process)(void *);
    using NewProcess = int(*)(void *);

}

template<typename T>
using TrueDarkMagic = MagicType1<std::vector<T>, std::string>;
int fun13() {
    TrueDarkMagic<bool> you;
}

///endregion

///region 变长参数模板

/// 在 C++11 之前，无论是类模板还是函数模板，都只能按其指定的样子， 接受一组固定数量的模板参数；
/// 而 C++11 加入了新的表示方法， 允许任意个数、任意类别的模板参数，同时也不需要在定义时将参数的个数固定。
template<typename... Ts> class Magic;

template<typename... Ts>
void magic1(Ts... args) {
    std::cout << sizeof...(args) << std::endl;
}

void fun14() {
    magic1();
    magic1(1, 2, "");
    magic1(0.1, 2, "");
}

/// 其次，对参数进行解包，到目前为止还没有一种简单的方法能够处理参数包，但有两种经典的处理手法：

/// 1.递归模板函数
/// 递归是非常容易想到的一种手段，也是最经典的处理方法。这种方法不断递归地向函数传递模板参数，进而达到递归遍历所有模板参数的目的：
template<typename T0>
void printf1(T0 value) {
    std::cout << value << std::endl;
}
template<typename T, typename... Ts>
void printf1(T value, Ts... args) {
    std::cout << value << std::endl;
    printf1(args...);
}

/// 2.变参模板展开
/// 在 C++17 中增加了变参模板展开的支持，于是你可以在一个函数中完成 printf 的编写
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}

/// 3.初始化列表展开
/// 递归模板函数是一种标准的做法，但缺点显而易见的在于必须定义一个终止递归的函数。
template<typename T, typename... Ts>
auto printf3(T value, Ts... args) {
    std::cout << value << std::endl;
    (void) std::initializer_list<T>{([&args] {
        std::cout << args << std::endl;
    }(), value)...};
}
///endregion

///region 折叠表达式
template<typename ... T>
auto sum(T ... t) {
    return (t + ...);
}
int fun15() {
    std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}
///endregion

///region 非类型模板参数推导
/// 在这种模板参数形式下，我们可以将 100 作为模板的参数进行传递
template <typename T, int BufSize>
class buffer_t {
public:
    T& alloc();
    void free(T& item);
private:
    T data[BufSize];
};

void fun16(){
    buffer_t<int, 100> buf; // 100 作
}

/// C++17 引入了这一特性，我们的确可以 auto 关键字，让编译器辅助完成具体类型的推导
template <auto value> void foo() {
    std::cout << value << std::endl;
    return;
}

int main() {
    foo<10>();  // value 被推导为 int 类型
}

///endregion

//endregion

//region 面向对象
///region 委托构造
///使得构造函数可以在同一个类中一个构造函数调用另一个构造函数，从而达到简化代码的目的
class Base {
public:
    int value1;
    int value2;

    Base() {
        value1 = 1;
    }

    Base(int value) : Base() { // 委托 Base() 构造函数
        value2 = value;
    }
};
///endregion

///region 继承构造
///在传统 C++ 中，构造函数如果需要继承是需要将参数一一传递的，这将导致效率低下。C++11 利用关键字 using 引入了继承构造函数的概念：
#include <iostream>
class Base2 {
public:
    int value1;
    int value2;
    Base2() {
        value1 = 1;
    }
    Base2(int value) : Base2() { // 委托 Base() 构造函数
        value2 = value;
    }
};
class Subclass : public Base2 {
public:
    using Base2::Base2; // 继承构造
};
///endregion

///region 显示虚函数重载
struct Base3 {
    virtual void foo(int);
};
struct SubClass3: Base3 {
    virtual void foo(int) override; // 合法
//    virtual void foo(float) override; // 非法, 父类没有此虚函数
};
///final 则是为了防止类被继续继承以及终止虚函数继续重载引入的。
struct Base4 {
    virtual void foo() final;
};
struct SubClass4 final: Base4 {
}; // 合法

//struct SubClass5 : SubClass4 {}; // 非法, SubClass1 已 final

struct SubClass6: Base4 {
//    void foo(); // 非法, foo 已 final
};
///endregion

///region 显示禁用默认函数
namespace default_fun {
    class Magic {
    public:
        Magic() = default; // 显式声明使用编译器生成的构造
        Magic &operator=(const Magic &) = delete; // 显式声明拒绝编译器生成构造
        Magic(int magic_number);
    };
}
///endregion

///region 强类型枚举
enum class new_enum : unsigned int {
    value1,
    value2,
    value3 = 100,
    value4 = 100
};

template<typename T>
std::ostream& operator<<(
        typename std::enable_if<std::is_enum<T>::value,
                std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

void fun17(){
    if (new_enum::value3 == new_enum::value4) {
        // 会输出
        std::cout << "new_enum::value3 == new_enum::value4" << std::endl;
    }

    std::cout << new_enum::value3 << std::endl;
}
///endregion
//endregion

