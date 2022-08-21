
#include <iostream>

using namespace std;


/**
 * 抽象类(有虚函数的类)/虚基类
 * virtual
 * 1、修饰成员方法是虚函数
 * 2、修饰继承方式，是虚继承，被虚继承的类，称作虚基类
 * */
class A {
public:

    virtual void func() {
        cout << "cal A::func" << endl;
    }

    void operator delete(void *ptr) {
        cout << "operator delete p:" << ptr;
        free(ptr);
    }

private:
    int ma;
};

class B : virtual public A {
public:
    void func() {
        cout << "cal B::func" << endl;
    }

    void *operator new(size_t size) {
        void *p = malloc(size);
        cout << "operator new p:" << p << endl;
        return p;
    }

private:
    int mb;
};

int main() {
    //基类指针指向派生类对象，永远指向派生类对象的基类部分
    A *p = new B();
    p->func();
    delete p;
    return 0;
}
