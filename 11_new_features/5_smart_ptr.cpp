//
// Created by ByteDance on 2022/12/18.
//
#include <algorithm>
#include <iostream>

using namespace std;

///region shared_ptr
void foo(std::shared_ptr<int> i) {
    (*i)++;
}

int fun1() {
    // auto pointer = new int(10); // illegal, no direct assignment
    // Constructed a std::shared_ptr
    auto pointer = std::make_shared<int>(10);
    foo(pointer);
    std::cout << *pointer << std::endl; // 11
    // The shared_ptr will be destructed before leaving the scope


    auto pointer2 = pointer; // 引用计数+1
    auto pointer3 = pointer; // 引用计数+1
    int *p = pointer.get();  // 这样不会增加引用计数
    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 3
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 3
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 3

    pointer2.reset();
    std::cout << "reset pointer2:" << std::endl;
    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 2
    std::cout << "pointer2.use_count() = "
              << pointer2.use_count() << std::endl;           // pointer2 已 reset; 0
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 2
    pointer3.reset();
    std::cout << "reset pointer3:" << std::endl;
    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 1
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0
    std::cout << "pointer3.use_count() = "
              << pointer3.use_count() << std::endl;           // pointer3 已 reset; 0
    return 0;
}
///endregion

///region unique_ptr
int fun2() {
    auto pointer = make_unique<int>(10);
    //auto pointer2 = pointer;//非法

}
///endregion


///region weak_ptr
struct A;
struct B;

struct A {
    std::shared_ptr<B> pointer;

    ~A() {
        std::cout << "A 被销毁" << std::endl;
    }
};

struct B {
    std::shared_ptr<A> pointer;

    ~B() {
        std::cout << "B 被销毁" << std::endl;
    }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->pointer = b;
    b->pointer = a;
    cout << a.use_count() << endl;
    cout << b.use_count() << endl;
}

///endregion