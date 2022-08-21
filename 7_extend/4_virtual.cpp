
#include <iostream>

using namespace std;


/**
 * 虚函数
 * 1、如果类里面定义了虚函数，那么编译阶段，编译器给这个类型产生一个唯一的vftable虚函数表；虚函数表中主要存储的内容就是RTTI指针和虚函数的地址
 * RTTI（run-time type information）运行时的类型信息
 * 当程序运行时，每一张虚函数表都会加载到内存的.rodata区
 *
 * 2、一个类里面定义了虚函数，那么这个类定义的对象，其运行时，内存中开始部分，多存储一个vfptr虚函数指针，指向相应类型的虚函数表vftable。
 * 一个类型定义的n个对象，它们的vfptr指向的都是同一张虚函数表
 *
 * 3、一个类里面虚函数的个数，不影响对象内存大小(vfptr)，影响的是虚函数表的大小
 *
 * 4、如果派生类中的方法和基类继承来的某个方法，返回值、函数名、参数列表都相同，而且基类的方法是virtual虚函数，那么派生类的方法自动处理成虚函数
 *    派生类中虚函数表里放的派生类show的地址，这就是覆盖：虚函数表中虚函数地址的覆盖
 *
 * 覆盖
 * 基类和派生类的方法，返回值、函数名以及参数列表相同，而且基类的方法是虚函数，那么派生类的方法就自动处理成虚函数，它们之间是覆盖关系
 *
 * */
class Base {
public:
    explicit Base(int data = 10) : ma(data) {}

    virtual void show() {
        cout << "Base::show()" << endl;
    }

    virtual void show(int a) {
        cout << "Base::show(int)" << endl;
    }


protected:
    int ma;
};

class Derive : public Base {
public:
    explicit Derive(int data) : Base(data), mb(data) {
    }

    void show() {
        cout << "Derive::show()" << endl;

    }

private:
    int mb;
};

int main() {
    Derive d(50);
    Base *p = &d;
    ///如果 show是普通函数，就进行静态绑定 call Base::show
    ///如果 show是虚函数，就进行动态绑定
    ///mov eax,dword ptr[pb]
    ///mov eax,dword ptr[eax]
    ///call ecx(虚函数的地址) //运行时才知道寄存器里的地址，就是动态绑定
    p->show();  ///静态(编译时期)的绑定(函数调用)
    ///由于Base里的show是虚函数，得动态绑定
    p->show(1);

    cout << sizeof(Base) << endl; ///4
    cout << sizeof(Derive) << endl;///8

    cout << typeid(p).name() << endl; ///class Base *
    cout << typeid(*p).name() << endl; ///Base

    return 0;
}
