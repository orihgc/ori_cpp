
#include <iostream>

using namespace std;


/**
 * 类模板=》实现一个C++ STL里面的一个顺序容器 vector向量容器
 * */
template<typename T>
class Vector {
private:
    T *first;///指向数组起始位置
    T *last;///指向数组中有效元素的后继位置
    T *end;///指向数组空间的后继位置
public:
    Vector(int size = 10) {
        //需要把内存开辟和对象构造分开处理
        first = new T[size];
        last = first;
        end = first + size;
    }

    ~Vector() {
        delete[]first;
        first = last = end = nullptr;
    }

    Vector(const Vector<T> &rhs) {
        int size = rhs.end - rhs.first;
        first = new T[size];
        int len = rhs.last - rhs.first;
        for (int i = 0; i < len; ++i) {
            first[i] = rhs.first[i];
        }
        last = first + len;
        end = first + size;
    }

    Vector<T> &operator=(const Vector<T> &rhs) {
        if (this == &rhs)return *this;
        delete[] first;
        int size = rhs.end - rhs.first;
        first = new T[size];
        int len = rhs.last - rhs.first;
        for (int i = 0; i < len; ++i) {
            first[i] = rhs.first[i];
        }
        last = first + len;
        end = first + size;
        return *this;
    }

    ///向容器末尾添加参数
    void push_back(const T &val) {
        if (full())expand();
        *last++ = val;
    }

    void pop_back() {
        if (empty())return;
        --last;
    }

    T back() const {
        return *(last - 1);
    }


    bool full() const {
        return last == end;
    }


    bool empty() const {
        return first == last;
    }

    int size() const {
        return last - first;
    }

private:
    void expand() {
        int size = end - first;
        T *pTmp = new T[2 * size];
        for (int i = 0; i < size; ++i) {
            pTmp[i] = first[i];
        }
        delete[] first;
        first = pTmp;
        last = first + size;
        end = first + 2 * size;
    }
};


int main() {

    Vector<int> vec;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100);
    }

    while (!vec.empty()) {
        cout << vec.back() << endl;
        vec.pop_back();
    }
    return 0;
}
