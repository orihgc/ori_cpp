
#include <iostream>
#include <vector>

using namespace std;

/**
 * 迭代器失效问题
 * 1.迭代器为什么会失效
 * a：当容器调用erase方法后，当前位置到容器末尾元素的所有的迭代器全部失效了
 * b：当容器调用insert方法后，当前位置到容器末尾元素的所有的迭代器全部失效了
 *    依然有效         全部失效
 * 首元素 -> 插入点/删除点-> 末尾元素
 * 对insert来说，如果引起容器扩容
 * 则原来容器的所有迭代器就全部失效了
 *
 * 2.迭代器失效后，问题如何解决？
 * 对插入/删除点的迭代器进行更新操作
 *
 * c:不同容器的迭代器是不能进行比较运算的
 * */



int fun1() {
    vector<int> vec;

    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    for (int num: vec) {
        cout << num << " ";
    }
    cout << endl;

    auto it = vec.begin();
    ///把vec容器中所有的偶数全部删除
//    for (; it != vec.end(); ++it) {
//        if (*it % 2 == 0) {
//            vec.erase(it);
//        }
//    }

    while (it != vec.end()) {
        if (*it % 2 == 0) {
            it = vec.erase(it);
        } else {
            ++it;
        }
    }

    for (int num: vec) {
        cout << num << " ";
    }
    cout << endl;


    return 0;
}

int fun2() {
    vector<int> vec;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }
    for (int num: vec) {
        cout << num << " ";
    }
    cout << endl;

    auto it = vec.begin();
    for (; it != vec.end(); ++it) {
        if (*it % 2 == 0) {
            ///这里的迭代器在第一次insert之后，iterator就失效了
            vec.insert(it, *it - 1);
            ++it;
        }
    }

    for (int num: vec) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

int main() {
    fun1();
    return 0;
}
