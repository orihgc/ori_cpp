//
// Created by ByteDance on 2023/4/6.
//
#include "iostream"

using namespace std;


class Shape {
public:
    int x = 12;

    explicit Shape() {
        cout << __FUNCTION__ << endl;
    }

    ~Shape() {
        cout << __FUNCTION__ << endl;
    }
};

class Circle : public Shape {
};

Shape *createShape() {
    return new Circle();
}

class ShapeWrapper {
private:
    Shape *ptr_;
public:
    explicit ShapeWrapper(Shape *ptr = nullptr) : ptr_(ptr) {}
    virtual ~ShapeWrapper() {delete ptr_;}
    Shape *Get() const { return ptr_; }
};

int main() {
    ShapeWrapper shapeWrapper;
//    cout << shapeWrapper.Get()->x << endl;
}
