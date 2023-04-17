
#include <iostream>
#include "vector"

using namespace std;

/**
 * vector 向量容器
 * 底层数据结构：动态开辟的数组，每次以原来空间大小的2倍进行扩容
 *
 * vector<int> vec;
 * 增加:
 * vec.push_back(20);末尾添加元素O(1)
 * 导致容器扩容时，会新开辟一个2倍的空间，并把原来的空间元素拷贝进新的空间
 * vec.insert(it,20); it迭代器指向的位置添加一个元素。O(n)
 * 在中间插入元素时，插入点后的元素都得向后移动。
 *
 * 删除:
 * vec.pop_back();末尾删除元素O(1)
 * vec.erase(it);删除迭代器指向的元素O(n)
 * 删除点后面所有的元素都得向前移动
 *
 * 查询
 * operator[] 下标的随机访问vec[5] O(1)
 * iterator 迭代器进行遍历
 * find for_each
 * foreach => 通过迭代器来实现的 C++11的语法糖
 *
 * 注意：对容器进行连续插入或者删除操作(insert/erase)，一定要更新迭代器，否则第一次insert或者erase完成。迭代器就失效了
 *
 * 常用方法介绍:
 * size()
 * empty()
 * reserve() 给vector预留空间.不会添加新的元素
 * resize() 重置大小，容器扩容 不仅给容器开辟指定大小的空间，还会添加新的元素
 * swap  两个容器进行元素交换
 *
 * */

void fun1(){
    vector<int> vec;//vector<string> vec;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    int size = vec.size();
    for (int i = 0; i < size; ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;

    ///把vec容器中所有偶数删除
    auto it2 = vec.begin();
    while (it2 != vec.end()) {
        if (*it2 % 2 == 0) {
            //vec.erase(it2);///此时it2失效了
            it2 = vec.erase(it2);
        } else {
            ++it2;
        }
    }

    ///通过迭代器遍历
    auto it1 = vec.begin();
    while (it1 != vec.end()) {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;

    ///给vector容器中所有的奇数前面都添加一个小于奇数1的偶数
    for (it1 = vec.begin(); it1 != vec.end(); ++it1) {
        if (*it1 % 2 != 0) {
            it1 = vec.insert(it1, *it1 - 1);
            ++it1;
        }
    }

    for (it1=vec.begin();it1!=vec.end();++it1){
        cout << *it1 << " ";

    }
    cout << endl;
}

int main() {
    vector<int> vec;//vector<string> vec;
    vec.reserve(20);//给vector容器预留空间
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    for (int i : vec) {
        cout<<i<<" ";
    }
    cout<<endl;
    vec.resize(30);
    for (int i : vec) {
        cout<<i<<" ";
    }
    return 0;
}
