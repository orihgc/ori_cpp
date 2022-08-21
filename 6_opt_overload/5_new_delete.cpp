
#include <iostream>

using namespace std;

/**
 * new和delete
 * 1.malloc和new的区别
 * a: malloc按字节开辟内存 \ new开辟内存时需要指定类型 new int[10]
 *   malloc开辟内存返回的都是 void* 而 operator new -> int*
 * b: malloc只负责开辟空间，new不仅仅有malloc的功能，可以进行数据的初始化
 * c: malloc开辟内存失败返回nullptr指针; new抛出的是bad_alloc类型的异常
 * 2.free和delete的区别
 *   delete: 调用析构函数，再free
 *   free就是内存释放
 *
 *
 * new和delete可以混用吗？
 * 对于普通类型，由于没有析构函数，等同于malloc和free，混用没有任何问题
 * 对于引用类型，有析构函数，为了调用正确的析构函数，那么开辟对象数组的时候，会多开辟4个字节记录对象的个数，则不能将new/delete混用
 * */

/// 先调用operator new开辟内存空间、然后调用对象的构造函数（初始化）
void *operator new(size_t size) {
    void *p = malloc(size);
    if (p == nullptr) {
        throw bad_alloc();
    }
    cout << "operator new addr:" << p << endl;
    return p;
}

///delete p; 调用p指向对象的析构函数，再调用operator delete释放内存空间
void operator delete(void *ptr) {
    cout << "operator delete addr:" << ptr << endl;
    free(ptr);
}

/// 先调用operator new[]开辟内存空间、然后调用对象的构造函数（初始化）
void *operator new[](size_t size) {
    void *p = malloc(size);
    if (p == nullptr) {
        throw bad_alloc();
    }
    cout << "operator new[] addr:" << p << endl;
    return p;
}

///delete[] p; 调用p指向对象的析构函数，再调用operator delete释放内存空间
void operator delete[](void *ptr) {
    cout << "operator delete[] addr:" << ptr << endl;
    free(ptr);
}

class Test {
public:
    Test(int data = 10) {
        cout << "Test()" << endl;
    }

    ~Test() {
        cout << "~Test()" << endl;
    }

private:
};


void fun1() {
    try {
        int *p = new int;
        delete p;

        int *q = new int[10];
        delete[] q;
    } catch (const bad_alloc &err) {
        cerr << err.what() << endl;
    }

}

int main() {

//    Test *pTest = new Test(20);
//    delete pTest;

//    Test *pTest1 = new Test[5];
//    delete[] pTest1;


//    int *pInt = new int[2];
//    delete pInt;

//    Test *pTest = new Test();
//    delete[] pTest;


    return 0;
}
