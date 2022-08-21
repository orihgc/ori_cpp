
#include <iostream>

using namespace std;

/**
 * 虚继承
 * 解决派生类有间接基类多份数据的问题
 * 好处，可以做更多代码的复用
 * */
class A {
public:
    explicit A(int data) : ma(data) {
        cout << "A()" << endl;
    }

    ~A() {
        cout << "~A()" << endl;
    }

protected:
    int ma;
};

class B : virtual public A {
public:
    explicit B(int data) : A(data), mb(data) {
        cout << "B()" << endl;
    }

    ~B() {
        cout << "~B()" << endl;
    }

protected:
    int mb;
};

class C : virtual public A {
public:
    explicit C(int data) : A(data), mc(data) {
        cout << "C()" << endl;
    }

    ~C() {
        cout << "~C()" << endl;
    }

protected:
    int mc;
};

class D : public B, public C {
public:
    explicit D(int data) : A(data), B(data), C(data), md(data) {
        cout << "D()" << endl;
    }

    ~D() {
        cout << "~D()" << endl;
    }

protected:
    int md;
};

int main() {

    D d(10);

    cout << sizeof(D) << endl;
    return 0;
}
