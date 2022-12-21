//
// Created by ByteDance on 2022/12/18.
//
#include "iostream"
#include "string"

using namespace std;

/**
 * 左值
 * */
int fun1() {
    int a = 1;
    ///左值是有标识符或可取地址的表达式
    int &r1 = a;
    int &r2 = ++a;
    int &r3 = a = 20;
    auto &r4 = cout << "r4" << endl;
    cout << a << endl;

    ///常量只能绑定到常量左值
    const string &str = "hello";
}

/**
 * 纯右值
 * */
int fun2() {
    int b = 2;
    ///纯右值是没有标识符、不可取地址的表达式，也称为临时对象
    ///非引用类型的表达式
    int &&r1 = b++;
    int &&r2 = b + 1;
    auto &&r3 = make_shared<int>(42);
    ///除字符串之外的字面量
    int &&r4 = 42;
    int &&r5 = true;

    ///C++ 11之前，右值可以绑定到常左值引用
    ///类型是右值引用的变量是一个左值

}

/**
 * 类型是右值引用的变量是一个左值
 * */
int fun3() {
    auto *pString = new string("");
    shared_ptr<string> ptr1(pString);
    /// move把一个左值引用强制转换成一个右值引用
    const shared_ptr<string> &ptr2 = std::move(ptr1);
    ///等价于
    const shared_ptr<string> &ptr3 = static_cast<shared_ptr<string> &&>(ptr1);
    ///move(ptr1)可以看作是一个有名字的右值，为了和无名的纯右值区别开来，c++里把这种表达式叫做xvalue将亡值，所以xvalue和pvalue都是右值
}


///region 左值、右值的纯右值、将亡值、右值

/**
* 左值 (lvalue, left value)，顾名思义就是赋值符号左边的值。准确来说， 左值是表达式（不一定是赋值表达式）后依然存在的持久对象。
* 右值 (rvalue, right value)，右边的值，是指表达式结束后就不再存在的临时对象。
* */

/// 而 C++11 中为了引入强大的右值引用，将右值的概念进行了进一步的划分，分为：纯右值、将亡值。

/** 纯右值 (prvalue, pure rvalue):
    纯粹的右值，要么是纯粹的字面量，例如 10, true；要么是求值结果相当于字面量或匿名临时对象，例如 1+2。
    非引用返回的临时变量、运算表达式产生的临时变量、 原始字面量、Lambda 表达式都属于纯右值
    */

/// 字面量除了字符串字面量以外，均为纯右值。而字符串字面量是一个左值，类型为 const char 数组
/// 但是注意，数组可以被隐式转换成相对应的指针类型，而转换表达式的结果（如果不是左值引用）则一定是个右值（右值引用为将亡值，否则为纯右值）
#include <type_traits>

int fun4() {
    // 正确，"01234" 类型为 const char [6]，因此是左值
    const char (&left)[6] = "01234";

    // 断言正确，确实是 const char [6] 类型，注意 decltype(expr) 在 expr 是左值
    // 且非无括号包裹的 id 表达式与类成员表达式时，会返回左值引用
    static_assert(std::is_same<decltype("01234"), const char (&)[6]>::value, "no equal");

    // 错误，"01234" 是左值，不可被右值引用
    // const char (&&right)[6] = "01234";


    const char *p = "01234";  // 正确，"01234" 被隐式转换为 const char*
    const char *&&pr = "01234";  // 正确，"01234" 被隐式转换为 const char*，该转换的结果是纯右值
    // const char*& pl = "01234"; // 错误，此处不存在 const char* 类型的左值
}

/**
 * 将亡值
 * 是 C++11 为了引入右值引用而提出的概念（因此在传统 C++ 中， 纯右值和右值是同一个概念），也就是即将被销毁、却能够被移动的值。
 * */
//auto fun5() {
//    vector<int> temp = {1, 2, 3, 4};
//    return temp;
//}
//
//vector<int> v = fun5();

///endregion

///region 右值引用和左值引用
void reference(std::string &str) {
    std::cout << "左值" << std::endl;
}

void reference(std::string &&str) {
    std::cout << "右值" << std::endl;
}

int fun5() {
    std::string lv1 = "string,"; // lv1 是一个左值
    // std::string&& r1 = lv1; // 非法, 右值引用不能引用左值
    std::string &&rv1 = std::move(lv1); // 合法, std::move可以将左值转移为右值
    std::cout << rv1 << std::endl; // string,

    const std::string &lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
    // lv2 += "Test"; // 非法, 常量引用无法被修改
    std::cout << lv2 << std::endl; // string,string,

    std::string &&rv2 = lv1 + lv2; // 合法, 右值引用延长临时对象生命周期
    rv2 += "Test"; // 合法, 非常量引用能够修改临时变量
    std::cout << rv2 << std::endl; // string,string,string,Test

    reference(rv2); // 输出左值

    return 0;
}
///endregion

///region 右值引用的使用场景

class A {
public:
    A() : m_ptr(new int(0)) {
        cout << "constructor A" << endl;
    }


    A(const A &a) : m_ptr(new int(*a.m_ptr)) {
        cout << "copy constructor A" << endl;
    }

    /// 移动构造
    A(A &&a) : m_ptr(a.m_ptr) {
        a.m_ptr = nullptr; // 为防止a析构时delete data，提前置空其m_ptr
        cout << "move constructor A" << endl;
    }

    ~A() {
        cout << "destructor A,m_ptr" << m_ptr << endl;
        delete m_ptr;
        m_ptr = nullptr;
    }

private:
    int *m_ptr;
};

// 为了避免返回值优化，此函数故意这样写
A Get(bool flag) {
    A a;
    A b;
    cout << "ready return" << endl;
    if (flag) {
        return a;
    } else {
        return b;
    }
}

int fun6() {
    {
        ///这里的a和返回的b会指向同一个指针m_ptr，在析构时导致重复删除该指针
        A a = Get(false); // 运行报错
    }
    cout << "main finish" << endl;
    return 0;
}

///region 移动语义move
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

class MyString {
private:
    char *m_data;
    size_t m_len;

    void copy_data(const char *s) {
        m_data = new char[m_len + 1];
        memcpy(m_data, s, m_len);
        m_data[m_len] = '\0';
    }

public:
    //构造函数
    MyString() {
        m_data = NULL;
        m_len = 0;
    }

    //构造函数
    MyString(const char *p) {
        m_len = strlen(p);
        copy_data(p);
    }

    //拷贝构造函数
    MyString(const MyString &str) {
        m_len = str.m_len;
        copy_data(str.m_data);
        std::cout << "Copy Constructor is called! source: " << str.m_data << std::endl;
    }

    //重载=
    MyString &operator=(const MyString &str) {
        if (this != &str) {
            m_len = str.m_len;
            copy_data(str.m_data);
        }
        std::cout << "Copy Assignment  is called! source: " << str.m_data << std::endl;
        return *this;
    }

    //移动构造函数
    MyString(MyString &&str) {
        std::cout << "Move Constructor is called! source: " << str.m_data << std::endl;
        m_len = str.m_len;
        m_data = str.m_data; //避免了不必要的拷贝
        str.m_len = 0;
        str.m_data = NULL;
    }

    //重载=
    MyString &operator=(MyString &&str) {
        std::cout << "Move Assignment  is called! source: " << str.m_data << std::endl;
        if (this != &str) {
            m_len = str.m_len;
            m_data = str.m_data; //避免了不必要的拷贝
            str.m_len = 0;
            str.m_data = NULL;
        }
        return *this;
    }

    virtual ~MyString() {
        if (m_data) free(m_data);
    }
};

int main() {
    MyString a;
    a = MyString("Hello");            // Move Assignment 因为a已经创建了，所以走=，而不是构造函数
    MyString b = a;                    // Copy Constructor
    MyString c = std::move(a);        // Move Constructor std::move将左值转为右值
    std::vector<MyString> vec;
    vec.push_back(MyString("World"));   // Move Constructor
    return 0;
}
///endregion

///endregion
