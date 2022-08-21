
#include <iostream>

using namespace std;


/**
 * 拥有纯虚函数的类，叫作抽象类
 *
 * 抽象类不能再实例化对象了，但是可以定义指针和引用变量
 * */
class Car {
public:
    explicit Car(string name) : _name(name) {}


    double getLeftMiles(double oil) {
        return oil * getMilesPerGallon();
    }

    string getName() {
        return _name;
    }

protected:
    string _name;

    virtual double getMilesPerGallon() = 0;
};

class Bnze : public Car {
public:
    Bnze(string name) : Car(name) {}

    double getMilesPerGallon() {
        return 20.0;
    }
};

class Audi : public Car {
public:
    Audi(string name) : Car(name) {}

    double getMilesPerGallon() {
        return 18.0;
    }
};

class BMW : public Car {
public:
    BMW(string name) : Car(name) {}

    double getMilesPerGallon() {
        return 15.0;
    }
};

void showCarLeftMiles(Car &car, double oil) {
    cout << car.getName() << ":" << car.getLeftMiles(oil) << endl;
}

int main() {
    Bnze b1("奔驰");
    Audi a1("奥迪");
    BMW m1("宝马");

    showCarLeftMiles(b1, 10);
    showCarLeftMiles(a1, 10);
    showCarLeftMiles(m1, 10);
    return 0;
}
