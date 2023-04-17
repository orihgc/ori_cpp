//
// Created by ByteDance on 2023/4/6.
//

#include "iostream"

using namespace std;

class Base {

public:
    Base() {
        cout << __FUNCTION__ << endl;
    };

    ~Base() {
        cout << __FUNCTION__ << endl;
    };

    int y;
    int x;
};

class Child : public Base {

};

class SharedCount {
public:
    explicit SharedCount() : count_(1) {}

    void add_count() {}

    long reduce_count() {
        return --count_;
    };

    long get_count() const {
        return count_;
    };

private:
    long count_;
};


template<typename T>
class SmartPtr {
private:
    T *ptr_;
    SharedCount *shared_count_;
public:
    template<typename U>
    friend
    class SmartPtr;

    explicit SmartPtr(T *ptr = nullptr) : ptr_(ptr) {
        cout << __FUNCTION__ << endl;
        if (ptr) {
            shared_count_ = new SharedCount();
        }
    }

    virtual ~SmartPtr() {
        if (ptr_ && !shared_count_->reduce_count()) {
            delete ptr_;
            delete shared_count_;
        }
        cout << __FUNCTION__ << endl;
    }


    SmartPtr(const SmartPtr &other) {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    };

    template<typename U>
    SmartPtr(SmartPtr<U> &other) {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }

    template<typename U>
    SmartPtr(SmartPtr<U> &&other) {
        ptr_ = other.ptr_;
        if (ptr_) {
            shared_count_ = other.shared_count_;
            other.ptr_ = nullptr;
        }
    }

    template<typename U>
    SmartPtr(SmartPtr<U> &&other, T *ptr) {
        ptr_ = ptr;
        if (ptr_) {
            shared_count_ = other.shared_count_;
            other.ptr_ = other.shared_count_;
        }
    }


    SmartPtr &operator=(SmartPtr rhs) {
        rhs.swap(*this);
        return *this;
    };

    T *release() {
        T *ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void swap(SmartPtr &rhs) {
        std::swap(ptr_, rhs.ptr_);
        std::swap(shared_count_, rhs.shared_count_);
    }

    long use_count() const {
        if (ptr_) {
            return shared_count_->get_count();
        } else {
            return 0;
        }
    }


    T *Get() const { return ptr_; }

    T &operator*() const { return *ptr_; }

    T *operator->() const { return ptr_; }

    explicit operator bool() const { return ptr_; }
};

template<typename T, typename U>
SmartPtr<T> DynamicPointerCast(const SmartPtr<U> &other) {
    T *ptr = dynamic_cast<T *>(other.Get());
    return SmartPtr<T>(other, ptr);
}


int fun1() {
    SmartPtr ptr1{new Base()};
    SmartPtr ptr2{ptr1};//出错
    SmartPtr<Base> ptr3;
    ptr3 = ptr1;//出错
    ptr3 = std::move(ptr1);
    SmartPtr<Base> ptr4{std::move(ptr3)};

    SmartPtr<Child> ptr5{new Child()};
    SmartPtr<Base> ptr6 = std::move(ptr5);


    return 0;
}


class Test {

public:
    explicit  Test() = default;

    ~Test() = default;

    void fun() {
        base = new Base();
        cout << base->x << endl;
    }

    Base *base;
};

int main() {
    Test test;
    test.fun();
}
