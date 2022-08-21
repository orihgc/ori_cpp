
#include <iostream>

using namespace std;


class Test1 {
public:
    void fun() {
        cout << "call Test::func" << endl;
    }

    int ma;

    static void static_func() {
        cout << "Test::static_func" << endl;
    }

    static int mb;
};

int Test1::mb;

int main() {
    Test1 t1{};
    auto *t2 = new Test1();


    ///无法从"int Test1::*"转换为"int *"
//    int *p1 = &Test1::ma;
    ///成员变量指针
    int Test1::*p = &Test1::ma;

    t1.*p = 20;
    cout << t1.ma << endl;

    t2->*p = 30;
    cout << t2->ma << endl;

    ///静态成员变量的指针
    int *p1 = &Test1::mb;
    *p1 = 40;
    cout << Test1::mb << endl;

    ///成员方法的指针
    void (Test1::*pf1)() = &Test1::fun;
    (t1.*pf1)();
    (t2->*pf1)();

    ///静态成员方法的指针
    void (*pf2)() = &Test1::static_func;
    (*pf2)();
    return 0;
}
