
#include <iostream>

using namespace std;

/**
 * 问题一：哪些函数不能实现成虚函数
 *
 * 虚函数依赖
 * 1、虚函数能产生地址，存储在vftable当中
 * 2、对象必须存在(vfptr -> vftable ->虚函数地址)
 *
 * 构造函数
 * 1、不能在构造函数前加virtual
 * 2、构造函数中调用虚函数，也不会发生动态绑定
 *
 * 派生类对象构造过程 先调用的是基类的构造函数，才调用派生类的构造函数
 *
 * static静态成员方法 NO!
 *
 * 问题二：虚析构函数
 * 1、析构函数调用的时候，对象是存在的
 * 2、什么时候把基类的析构函数必须实现成虚函数？
 * 基类的指针指向堆上new出来的派生类对象的时候，delete pb(基类的指针)，
 * 在调用析构函数的时候，必须发生动态绑定，否则会导致派生类的析构函数无法调用
 * */

class Base {
public:
    explicit Base(int data = 10) : ma(data) {
        cout << "Base" << endl;
    }

    virtual ~Base() {
        cout << "~Base" << endl;
    }

    virtual void show() {
        cout << "Base::show()" << endl;
    }

protected:
    int ma;
};

class Derive : public Base {
public:
    explicit Derive(int data) : Base(data), mb(data) {
        cout << "Derive" << endl;
    }


    ///基类的析构函数是虚析构函数，那么派生类都会成为虚析构函数
    ~Derive() {
        cout << "~Derive" << endl;
    }

    void show() {
        cout << "Derive::show()" << endl;

    }

private:
    int mb;
};

void fun(Base* base){

}

int main() {
    string  s{"aabcd"};
    auto m=s.rfind("ab");
            if(m==string::npos){

            }
    cout<<(m==string::npos);

    return 0;
}
