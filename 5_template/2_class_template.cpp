
#include <iostream>

using namespace std;

///类型参数默认值
template<typename T=int>
///模板名+类型参数列表=类名称
class TempSeqStack { //模板名称
public:
    ///构造和析构函数名不用加参数列表，其他出现模板的地方都加上类型参数列表
    explicit TempSeqStack(int size = 10) : _pStack(new T[size]), _top(0), _size(size) {}

    ~TempSeqStack() {
        delete[]_pStack;
        _pStack = nullptr;

    }

    TempSeqStack(const TempSeqStack<T> &stack) : _top(stack._top), _size(stack._size) {
        _pStack = new T(_size);
        for (int i = 0; i < _top; ++i) {
            _pStack[i] = stack._pStack[i];
        }
    }

    TempSeqStack<T> &operator=(const TempSeqStack<T> &stack) {
        if (this == &stack)return *this;

        delete[]_pStack;

        _top = stack._top;
        _size = stack._size;
        _pStack = new T[_size];
        for (int i = 0; i < _top; ++i) {
            _pStack[i] = stack._pStack[i];
        }
        return *this;
    }

    void push(const T val);

    void pop() {
        if (empty())return;
        _top--;
    };

    ///只读操作接口，建议写成常方法
    T top() const {
        if (empty())throw "stack is empty";///抛异常也代表函数逻辑结束
        return _pStack[_top - 1];
    };

    bool full() const {
        return _top == _size;
    };

    bool empty() const {
        return _top == 0;
    };


private:
    T *_pStack;
    int _top;
    int _size;

    ///顺序栈底层数组按2倍的方式扩容
    void expand() {
        T *pTmp = new T[_size * 2];
        for (int i = 0; i < _top; ++i) {
            pTmp[i] = _pStack[i];
        }
        delete[]_pStack;
        _pStack = pTmp;
        _size *= 2;
    }
};

template<typename T>
void TempSeqStack<T>::push(const T val) {
    if (full()) {
        expand();
    }
    _pStack[_top++] = val;
}

int main() {
    ///类模板的选择性实例化
    ///模板类 class SeqStack<int>{}
    TempSeqStack<> tempSeqStack(10);
    return 0;
}

