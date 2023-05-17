
#include <iostream>

using namespace std;

/**
 * C++语言基本提供的四种类型转换方式
 * const_cast: 去掉(指针或者引用)常量属性的一个类型转换
 * static_cast: 提供编译器认为安全的类型转换
 * reinterpret_cast：类似于c风格的强制类型转换，没有安全性
 * dynamic_cast：主要用在继承结构中，可以支持RTTI类型识别的上下转换
 * */

int fun1() {
    const int a = 10;
    int *p1 = (int *) &a;
    ///const_cast只用于去掉常量属性的地方
    int *p2 = const_cast<int *>(&a);
    *p1 = 20;
    cout << "*p1:" << *p1 << endl;
    *p2 = 12;
    cout << "*p2:" << *p2 << endl;
    return 0;
}

int fun2() {

    int a = 10;
    ///static_cast 禁用没有任何联系的两个类之间的强转
    char b = static_cast<int>(a);

    int *p = nullptr;
//    double *d = static_cast<double *>(p);
    cout << "b:" << b << endl;

}

int fun3() {
    int *p = new int(2);
    ///类似与C风格的强制类型转换
    auto *p2 = reinterpret_cast<double *>(p);
    cout << "p2:" << *p2 << endl;
}

class Base {
public:
    virtual void func() = 0;
};

class Derive1 : public Base {
    void func() { cout << "call Derivel1:func" << endl; }
};

class Derive2 : public Base {
public:
    void func() { cout << "call Derivel2:func" << endl; }

    void derive02func() {
        cout << "call Derivel2:derive02func" << endl;
    }
};

void showFunc(Base *p) {
    ///dynamic_cast会检查p指针是否指向的是一个Derive2类型的对象
    ///返回Derive2对象的地址，给pd2；否则返回nullptr
    ///static_cast是编译时期的类型转换，dynamic_cast是运行时期的类型转换，支持RTTI
    auto *pd2 = dynamic_cast<Derive2 *>(p);

    if (pd2 != nullptr) {
        pd2->derive02func();
    } else {
        p->func();
    }
}

int fun4() {
    Derive1 d1;
    Derive2 d2;
    showFunc(&d1);
    showFunc(&d2);
}

int main(){
    return 0;
}