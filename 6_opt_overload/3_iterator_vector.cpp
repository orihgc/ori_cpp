
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
    T *_first;///指向数组起始位置
    T *_last;///指向数组中有效元素的后继位置
    T *_end;///指向数组空间的后继位置
    Alloc _allocator;///定义容器的空间配置器对象

public:
    Vector(int size = 10, const Alloc &alloc = Allocator<T>()) {
        //需要把内存开辟和对象构造分开处理
//        _first = new T[size];
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }

    ~Vector() {
//        delete[]_first;
        for (T *p = _first; p != _last; ++p) {
            _allocator.destroy(p);//把first指针指向的数组的有效元素进行析构操作
        }
        _allocator.deallocate(_first);//释放堆上的数组内存
        _first = _last = _end = nullptr;
    }

    Vector(const Vector<T> &rhs) {
        int size = rhs._end - rhs._first;
//        _first = new T[size];
        _first = _allocator.allocate(size);
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; ++i) {
            _allocator.construct(_first + 1, rhs._first[i]);
        }
        _last = _first + len;
        _end = _first + size;
    }

    Vector<T> &operator=(const Vector<T> &rhs) {
        if (this == &rhs)return *this;
//        delete[] _first;
        for (T *p = _first; p != _last; ++p) {
            _allocator.destroy(p);//把first指针指向的数组的有效元素进行析构操作
        }
        _allocator.deallocate(_first);//释放堆上的数组内存
        int size = rhs._end - rhs._first;
        _first = new T[size];
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; ++i) {
            _first[i] = rhs._first[i];
        }
        _last = _first + len;
        _end = _first + size;
        return *this;
    }

    ///向容器末尾添加参数
    void push_back(const T &val) {
        if (full())expand();
        _allocator.construct(_last, val);
        _last++;
    }

    void pop_back() {
        if (empty())return;
        --_last;///不仅仅只是将指针--，还需要析构删除的元素
        _allocator.destroy(_last);
    }

    T back() const {
        return *(_last - 1);
    }


    bool full() const {
        return _last == _end;
    }


    bool empty() const {
        return _first == _last;
    }

    int size() const {
        return _last - _first;
    }

    T &operator[](int index) {
        if (index < 0 || index >= size()) {
            throw "OutOfRangeException";
        }
        return _first[index];
    }

    class iterator {
    private:
        T *_ptr;

    public:
        explicit iterator(T *ptr = nullptr) : _ptr(ptr) {}

        bool operator!=(const iterator &it) const {
            return _ptr != it._ptr;
        }

        void operator++() {
            _ptr++;
        }

        T &operator*() { return *_ptr; }
    };

    iterator begin() { return iterator(_first); }

    iterator end() { return iterator(_last); }

private:
    void expand() {
        int size = _end - _first;
//        T *pTmp = new T[2 * size];
        T *pTmp = _allocator.allocate(2 * size);
        for (int i = 0; i < size; ++i) {
            _allocator.construct(pTmp + i, _first[i]);
            pTmp[i] = _first[i];
        }
        for (T *p = _first; p != _last; ++p) {
            _allocator.destroy(p);
        }
        _allocator.deallocate(_first);
        _first = pTmp;
        _last = _first + size;
        _end = _first + 2 * size;
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

int fun1() {
    Vector<VectorTest> vectorT;
    VectorTest t1, t2, t3;
    vectorT.push_back(t1);
    vectorT.push_back(t2);
    vectorT.push_back(t3);

    vectorT.pop_back();

    return 0;
}

int main() {

    Vector<int> vec;
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    int size = vec.size();
    for (int i = 0; i < size; ++i) {
        cout << vec[i] << " ";

    }
    cout << endl;

    auto it = vec.begin();
    while (it != vec.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    for (int val :vec) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
