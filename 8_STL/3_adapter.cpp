//
// Created by ByteDance on 2023/4/11.
//

#include "iostream"
#include "stack"
#include "queue"


using namespace std;

/**
 * stack 底层依赖的是deque
 *
 * queue 底层依赖的是deque
 * 为啥不用vector？
 * 对于queue来说，需要支持尾部插入，头部删除，依赖vector，其出队效率低
 * vector需要大量的连续内存，deque只需要分段的内存，当存储大量数据时，deque对内存的利用率更好一些
 *
 * priority_queue 默认是大根堆
 * 底层依赖vector: 大根堆
 *
 * */
int main() {
    stack<int> s1;
    for (int i = 0; i < 20; ++i) {
        s1.push(::rand() % 100 + 1);
    }

    while (!s1.empty()){
        cout<<s1.top()<<" ";
        s1.pop();
    }

    cout<<endl;

    queue<int> que;
    for (int i = 0; i < 20; ++i) {
        que.push(::rand() % 100 + 1);
    }

    while (!que.empty()){
        cout<<que.front()<<" ";
        que.pop();
    }
    cout<<endl;

    priority_queue<int> pri_que;
    for (int i = 0; i < 20; ++i) {
        pri_que.push(::rand() % 100 + 1);
    }

    while (!pri_que.empty()){
        cout<<pri_que.top()<<" ";
        pri_que.pop();
    }
    return 0;
}
