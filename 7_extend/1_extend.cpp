
#include <iostream>

using namespace std;

/**
 * 1. 继承的本质和原理
 * 继承的本质： 代码的复用
 *
 * 2. 访问限定符
 * 继承方式  基类的访问限定 派生类的访问限定 外部的访问限定
 * public      public       public        Y
 *             protected    protected     N
 *             private      不可见         N      //私有变量只有自己或者友元函数可以访问
 * protected   public       protected     N
 *             protected    protected     N
 *             private      不可见         N
 * private     public       private       N
 *             protected    private       N
 *             private      不可见         N
 *
 * 总结
 * 1、外部只能访问public的成员
 * 2、在继承结构中，派生类可以从基类继承过来private的成员，但是派生类无法直接访问
 * 3、protected和private的区别？在基类中定义的成员，想被派生类访问，但不想被外部访问，那么在基类中，把相关成员定义成protected保护的；
 *    如果派生类和外部都不打算访问，那么，在基类中，就把相关成员定义成private私有的
 *
 * 默认的继承方式是什么？
 * 派生类是用class定义的，则默认是private
 * 派生类是用struct定义的，则默认是public
 * */

class A {
public:
    int ma;
protected:
    int mb;
private:
    int mc;
};

class B : protected A {
public:
    void func() {
        ma;
        mb;

    }

public:
    int md;
protected:
    int me;
    int ma;
private:
    int mf;
};

class C : public B {
    /// 在C里面，ma的访问限定是： 可继承但是，不可见
public:
    void func() {

    }
};

int main() {
    B b;
    return 0;
}
