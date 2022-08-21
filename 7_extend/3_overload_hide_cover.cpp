
#include <iostream>

using namespace std;

/**
 * 重载、隐藏、覆盖
 * 1、重载关系
 *    一组函数要重载，必须处在同一个作用域当中，而且函数名字相同，参数列表不同
 * 2、隐藏的关系（作用域的隐藏）
 *    在继承结构当中，派生类的同名成员，把基类的同名成员隐藏掉了
 *
 *
 * 在继承结构中进行上下的类型转换，默认只支持从下到上的类型转换
 * 基类对象和派生类对象之间的转换
 *
 * 基类指针->派生类对象
 * 派生类指针->基类对象
 *
 * */
class Base {
public:
    explicit Base(int data = 10) : ma(data) {}

    void show() {
        cout << "Base::show()" << endl;
    }

    void show(int a) {
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

int fun1() {

    Derive derive(10);
    derive.show();
    derive.Base::show();

    derive.Base::show(1);
//    derive.show(1);
    ///优先找派生类自己的作用域的show名字成员，没有的话才从基类里面找

    return 0;
}

///
int main() {
    Base base(10);
    Derive derive(20);
    ///基类 <- 派生类 可以，从下到上的转换 Y
    base = derive;
    ///派生类 <- 基类 从上到下 N
    //derive = base;

    /// 基类指针 -> 派生类对象 类型从下到上的转换
    Base *p = &derive;
    p->show();
    ///默认只能访问基类的成员
    ((Derive *) p)->show();
    p->show(1);
    /// 派生类指针 -> 基类对象，从上到下的转换 N
    //Derive *derive1 = &base; //不安全，设计内存的非法访问
}
