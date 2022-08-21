
#include <iostream>
#include <string>

using namespace std;

/**
 * 1、静态的多态：函数重载、模板(函数模板和类模板)
 * 2、动态的多态：
 * 在继承结构中，基类指针（引用）指向派生类对象，通过该指针（引用）调用同名覆盖方法（虚函数），基类指针指向哪个派生类对象，就会调用哪个派生类对象的覆盖方法，成为多态
 * 多态底层是通过动态绑定来实现的 pBase->访问谁的vfptr->访问谁的vftable->当然是对应的派生类对象的方法了
 * */
class Animal {
public:
    Animal(string name) : _name(name) {}

    virtual void bark() {}

protected:
    string _name;
};

class Cat : public Animal {
public:
    Cat(string name) : Animal(name) {}

    void bark() {
        cout << "bark: miao miao!" << endl;
    }
};

class Dog : public Animal {
public:
    Dog(string name) : Animal(name) {

    }

    void bark() {
        cout << "bark: wang wang!" << endl;
    }
};

class Pig : public Animal {
public:
    Pig(string name) : Animal(name) {

    }

    void bark() {
        cout << "bark: pig pig!" << endl;
    }
};

/**
 * 下面的一组bark API方法无法满足设计原则中的开闭原则
 * */
/*
void bark(Cat &cat) {
   cat.bark();
}

void bark(Dog &dog) {
   dog.bark();
}

void bark(Pig &pig) {
   pig.bark();
}
*/

void bark(Animal &animal) {
    animal.bark();
}

/**
 * 是不是虚函数的调用一定就是动态绑定？
 * 在类的构造函数当中，调用虚函数，也是静态绑定(构造函数中调用其他函数(虚),不会发生动态绑定)
 *
 * 如果不是通过指针或引用变量来调用虚函数，那就是静态绑定
 * */

class Base {
public:
    explicit Base(int data = 10) : ma(data) {}

    virtual void show() {
        cout << "Base::show()" << endl;
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
    Cat cat("猫咪");
    Dog dog("二哈");
    Pig pig("佩奇");

    bark(cat);
    bark(dog);
    bark(pig);

    return 0;
}

int fun2() {
    Base base;
    Derive derive(10);

    ///都是动态绑定（必须由指针或引用调用虚函数，才会发生动态绑定）
    Base *p1 = &base;
    p1->show();
    Base *p2 = &derive;
    p2->show();

    ///引用调用虚函数
    Base &rb1 = base;
    Base &rb2 = derive;
    rb1.show();
    rb2.show();

    Derive *p = &derive;
    Derive &rd1 = derive;
    p->show();
    rd1.show();

    Derive *pDerive = (Derive *) &base;
    pDerive->show();

}

int main() {
    fun2();
    return 0;
}
