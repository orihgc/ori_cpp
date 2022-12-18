//
// Created by orihgc on 2022/8/10.
//

#ifndef ORI_CPP_SEQSTACK_H
#define ORI_CPP_SEQSTACK_H


class SeqStack {

public:
    ///可以带参数，可以提供多个构造函数，叫做构造函数的重载
    SeqStack(int size = 10);

    ///自定义拷贝构造函数
    SeqStack(const SeqStack &src);

    ///赋值函数
    void operator=(const SeqStack &src);

    ///析构函数不带参数，所有析构函数只能有一个
    ~SeqStack();

    void push(int value);

    void pop();

    int top();

    bool empty();

    bool full();

private:
    int *_pStack;///动态开辟数组，存储顺序栈的元素
    int _top;///指向栈顶元素的位置
    int _size;///数组扩容的总大小

    void resize();
};


#endif //ORI_CPP_SEQSTACK_H
