//
// Created by orihgc on 2022/8/11.
//

#include <iostream>
#include <cstring>

using namespace std;

class CData {
public:
    ///自定义了构造函数，所以不会产生构造函数
    CData(int y, int m, int d) {
        _year = y;
        _month = m;
        _day = d;
    }

    void show() {
        cout << _year << "年" << _month << "月" << _day << "日" << endl;
    }

private:
    int _year;
    int _month;
    int _day;
};

/**
 * 构造函数的初始化列表
 * */
class ConGoods {
public:
    ///构造函数的初始化列表
    ConGoods(const char *n, int a, double p, CData data) : _data(data), _amount(a), _price(p) {
        strcpy(_name, n);
    }

    ConGoods(const char *n, int a, double p, int y, int m, int d) : _data(y, m, d), _amount(a), _price(p) {
        strcpy(_name, n);
    }

    void show() {
        cout << "name:" << _name << endl;
        cout << "amount:" << _amount << endl;
        cout << "price:" << _price << endl;
        _data.show();
    }

private:
    char _name[20];
    int _amount;
    double _price;
    CData _data;//成员对象 1、分配内存 2、调用构造函数
};

class Test {
public:
    Test(int data = 10) : b(data), a(b) {
    }

    void show() {
        cout << a << endl;
        cout << b << endl;
    }

private:
    ///成员变量的初始化和它们定义的顺序有关，和构造函数初始化列表中出现的先后顺序无关！
    int a;
    int b;
};

int main() {
    Test test;
    test.show();
    return 0;
}