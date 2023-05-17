//
// Created by ByteDance on 2023/4/24.
//
#include "iostream"

using namespace std;

class Delegate {
    virtual void Fun();
};

class Base : Delegate {
protected:
    Base() {
        cout << __FUNCTION__ << endl;

    };

    virtual void Fun() override {
        cout << __FUNCTION__ << endl;
    }

    virtual ~Base() {
        cout << __FUNCTION__ << endl;
    };
};

class BaseImpl : Base {
public:
    BaseImpl() {
        cout << __FUNCTION__ << endl;

    };

    void Fun() override {
        cout << __FUNCTION__ << endl;
    }

    ~BaseImpl() override {
        cout << __FUNCTION__ << endl;
    };
};

int main() {
    bool base = false;
    bool target = true;
    target |= base;
    cout << target;
}
