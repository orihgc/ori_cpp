
#include <iostream>

using namespace std;


class Queue {
public:
    Queue(int size = 20) {
        _pQue = new int[size];
        _front = _rear = 0;
        _size = size;
    }

    /**    Queue(const Queue &) = delete;

    Queue &operator=(const Queue &) = delete;*/
    Queue(const Queue &src) {
        _size = src._size;
        _front = src._front;
        _rear = src._rear;
        _pQue = new int[_size];
        for (int i = _front; i != _rear; i = (i + 1) % _size) {
            _pQue[i] = src._pQue[i];
        }
    };

    Queue &operator=(const Queue &src) {
        if (this == &src)return *this;
        delete[] _pQue;
        _size = src._size;
        _front = src._front;
        _rear = src._rear;
        _pQue = new int[_size];
        for (int i = _front; i != _rear; i = (i + 1) % _size) {
            _pQue[i] = src._pQue[i];
        }
    }

    ~Queue() {
        delete[]_pQue;
        _pQue = nullptr;
    }


    void push(int val) {
        if (full())
            resize();
        _pQue[_rear] = val;
        _rear = (_rear + 1) % _size;
    }

    void pop() {
        if (empty())return;
        _front = (_front + 1) % _size;
    }

    int top() {
        return _pQue[_front];
    }

    bool full() {
        return (_rear + 1) % _size == _front;
    }

    bool empty() {
        return _front == _rear;
    }


private:
    int *_pQue;///申请队列的数组空间
    int _front;///指示队头的位置
    int _rear;///指示队尾的位置
    int _size;///队列扩容的总大小

    void resize() {
        int *pTmp = new int[2 * _size];
        int index = 0;
        for (int i = _front; i != _rear; i = (i + 1) % _size) {
            pTmp[index] = _pQue[i];
            index++;
        }
        delete[]_pQue;
        _pQue = pTmp;
        _front = 0;
        _rear = index;
        _size *= 2;
    }

};

int main() {
    Queue queue(5);
    for (int i = 0; i < 20; ++i) {
        queue.push(rand() % 100);
    }
    while (!queue.empty()) {
        cout << queue.top() << endl;
        queue.pop();
    }
    return 0;
}
