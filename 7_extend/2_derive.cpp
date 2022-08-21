
#include <iostream>

using namespace std;

/**
 * 派生类的构造过程
 * 1、派生类从继承可以继承来所有的成员（变量和方法），除了构造函数和析构函数
 * 2、派生类通过调用基类相应的构造函数来进行初始化
 *
 * 派生类从基类继承来的成员的初始化和清理由基类的构造和析构函数负责
 *
 * 派生类对象构造和析构的过程是：
 * 1、派生类调用基类的构造函数，初始化从基类继承来的成员
 * 2、调用派生类自己的构造函数，初始化类自己持有的成员
 * 。。。出派生类对象的作用域
 * 3、调用派生类的析构函数，释放派生类可能占用的外部资源
 * 4、调用基类的析构函数，释放派生类内存中，从基类继承来的成员可能占用的外部资源
 * */
class Base {
public:
    explicit Base(int data = 10) : ma(data) {
        cout << "Base()" << endl;
    }

    ~Base() {
        cout << "~Base()" << endl;

    }

protected:
    int ma;
};

class Derive : public Base {
public:
    explicit Derive(int data) : Base(data), mb(data) {
        cout << "Derive()" << endl;
    }

    ~Derive() {
        cout << "~Derive()" << endl;
    }

private:
    int mb;
};

int main() {

    Derive derive(20);
    return 0;
}
