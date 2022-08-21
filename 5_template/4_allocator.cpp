
#include <iostream>

using namespace std;


/**
 * 容器的控件配置器：内存开辟/内存释放，对象构造/对象析构
 * */

///容器的控件配置器，和C++标准库的allocator一样
template<typename T>
struct Allocator {
    ///负责开辟内存
    T *allocate(size_t size) {
        return (T *) malloc(sizeof(T) * size);
    }

    ///内存释放
    void deallocate(void *p) {
        free(p);
    }

    ///负责对象构造
    void construct(T *p, const T &val) {
        new(p) T(val);///定位new
    }

    void destroy(T *p) {
        p->~T();
    }
};

template<typename T, typename Alloc=Allocator<T>>
class Vector {
private:
    T *first;///指向数组起始位置
    T *last;///指向数组中有效元素的后继位置
    T *end;///指向数组空间的后继位置
    Alloc _allocator;///定义容器的空间配置器对象

public:
    Vector(int size = 10, const Alloc &alloc = Allocator<T>()) {
        //需要把内存开辟和对象构造分开处理
//        first = new T[size];
        first = _allocator.allocate(size);
        last = first;
        end = first + size;
    }

    ~Vector() {
//        delete[]first;
        for (T *p = first; p != last; ++p) {
            _allocator.destroy(p);//把first指针指向的数组的有效元素进行析构操作
        }
        _allocator.deallocate(first);//释放堆上的数组内存
        first = last = end = nullptr;
    }

    Vector(const Vector<T> &rhs) {
        int size = rhs.end - rhs.first;
//        first = new T[size];
        first = _allocator.allocate(size);
        int len = rhs.last - rhs.first;
        for (int i = 0; i < len; ++i) {
            _allocator.construct(first + 1, rhs.first[i]);
        }
        last = first + len;
        end = first + size;
    }

    Vector<T> &operator=(const Vector<T> &rhs) {
        if (this == &rhs)return *this;
//        delete[] first;
        for (T *p = first; p != last; ++p) {
            _allocator.destroy(p);//把first指针指向的数组的有效元素进行析构操作
        }
        _allocator.deallocate(first);//释放堆上的数组内存
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
        _allocator.construct(last, val);
        last++;
    }

    void pop_back() {
        if (empty())return;
        --last;///不仅仅只是将指针--，还需要析构删除的元素
        _allocator.destroy(last);
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
//        T *pTmp = new T[2 * size];
        T *pTmp = _allocator.allocate(2 * size);
        for (int i = 0; i < size; ++i) {
            _allocator.construct(pTmp + i, first[i]);
            pTmp[i] = first[i];
        }
        for (T *p = first; p != last; ++p) {
            _allocator.destroy(p);
        }
        _allocator.deallocate(first);
        first = pTmp;
        last = first + size;
        end = first + 2 * size;
    }
};


class VectorTest {
public:
    VectorTest() {
        cout << "VectorTest" << endl;
    }

    ~VectorTest() {
        cout << "~VectorTest" << endl;
    }

    VectorTest(const VectorTest &) {
        cout << "Test(const Test&)" << endl;
    }
};

int main() {
    Vector<VectorTest> vectorT;
    VectorTest t1, t2, t3;
    vectorT.push_back(t1);
    vectorT.push_back(t2);
    vectorT.push_back(t3);

    vectorT.pop_back();

    return 0;
}
