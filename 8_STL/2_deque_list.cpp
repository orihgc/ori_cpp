//
// Created by ByteDance on 2023/4/11.
//
#include "iostream"
#include "vector"
#include "deque"
#include "list"

using namespace std;

/**
 * deque: 双端队列容器
 * 底层数据结构：动态开辟的二维数组，一维数组从2开始，以2倍的方式进行扩容，每次扩容后，原来第二维的数组，从新的第一维数组的下标old_size/2开始存放。
 * 上下都预留相同的空间，方便支持首位元素的添加
 *
 * deque<int> deq;
 * 增加：
 * deq.push_back();
 * deq.push_front();
 * deq.insert(it,20);
 *
 * 删除
 * deq.pop_back()
 * deq.pop_front()
 * deq.erase(it)
 *
 * 查询
 * iterator(连续的insert和erase一定要考虑迭代器失效的问题)
 *
 * list: 链表容器
 * 底层数据结构：双向的循环链表
 * list<int> ls;
 * 增加：
 * ls.push_back();
 * ls.push_front();
 * ls.insert(it,20); O(1)的操作
 * 对于链表来说，查询操作效率比较慢
 *
 * 删除
 * ls.pop_back()
 * ls.pop_front()
 * ls.erase(it)
 *
 * 查询
 * iterator(连续的insert和erase一定要考虑迭代器失效的问题)
 *
 * */


/**
 * vector特点：动态数组，内存是连续的，2倍的方式进行扩容
 *
 * vector和deque之间的区别？
 * vector需要的内存空间必须是连续的，deque可以分块进行数据存储，不需要内存空间必须连续
 * 由于deque的内存空间不是连续的，造成进行元素的insert和erase，造成元素移动的时候比vector要慢
 *
 * vector和list之间的区别？
 * 1、vector底层是动态开辟的数组 list底层是双向链表
 *
 *
 *
 * */
int main(){


}
