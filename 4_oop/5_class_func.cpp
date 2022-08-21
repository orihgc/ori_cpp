
#include <iostream>

using namespace std;

/**
 * 类的各种成员 - 成员方法、变量
 * 普通的成员方法 => 编译器会添加一个this形参变量
 * 1.属于类的作用域
 * 2.调用该方法需要依赖一个对象（常对象是无法调用的 ）
 * 3.可以任意访问对象的私有成员变量 protected、private、public
 *
 * 静态成员方法 => 不会生成this形参变量
 * 1、属于类的作用域
 * 2、调用方法用类名作用域来调用方法
 * 3、可以任意访问对象的私有成员，仅限于不依赖对象的成员 （只能调用其他的static静态成员）
 *
 * const常方法 => const CGoods *this
 * 1、属于类的作用域
 * 2、调用依赖一个对象，普通对象或常对象都可以
 * 3、可以任意访问对象的私有成员，但只能读不能写
 * */


class CDataCopy {
public:
    ///自定义了构造函数，所以不会产生构造函数
    CDataCopy(int y, int m, int d) {
        _year = y;
        _month = m;
        _day = d;
    }

    void show() {
        cout << _year << "年" << _month << "月" << _day << "日" << endl;
    }

    void show()const{
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
class ConGoodsCopy {
public:
    ///构造函数的初始化列表
    ConGoodsCopy(const char *n, int a, double p, CDataCopy data) : _data(data), _amount(a), _price(p) {
        strcpy(_name, n);
        _count++;
    }

    ConGoodsCopy(const char *n, int a, double p, int y, int m, int d) : _data(y, m, d), _amount(a), _price(p) {
        strcpy(_name, n);
        _count++;
    }

    ///普通方法参数有隐藏的 ConGoodsCopy *this
    void show() {
        cout << "name:" << _name << endl;
        cout << "amount:" << _amount << endl;
        cout << "price:" << _price << endl;
        _data.show();
    }

    ///常方法
    void show() const {
        cout << "name:" << _name << endl;
        cout << "amount:" << _amount << endl;
        cout << "price:" << _price << endl;
        _data.show();
    }

    ///访问静态变量，得使用静态成员方法 没有this指针。静态方法无法访问普通的成员变量
    static void showCGoodsCount() {
        cout << "所有商品的种类数量是：" << _count << endl;
    }

private:
    char _name[20];
    int _amount;
    double _price;
    CDataCopy _data;//成员对象 1、分配内存 2、调用构造函数

    static int _count;///不属于对象，而是属于类级别，
};

int ConGoodsCopy::_count = 0;


int main() {
    ConGoodsCopy conGoodsCopy1("商品1", 100, 35.0, 2020, 1, 1);
    conGoodsCopy1.show();
    ConGoodsCopy conGoodsCopy2("商品2", 100, 35.0, 2020, 1, 1);
    conGoodsCopy2.show();
    ConGoodsCopy conGoodsCopy3("商品3", 100, 35.0, 2020, 1, 1);
    conGoodsCopy3.show();
    ConGoodsCopy conGoodsCopy4("商品4", 100, 35.0, 2020, 1, 1);
    conGoodsCopy4.show();

    ConGoodsCopy::showCGoodsCount();

    const ConGoodsCopy conGoodsCopy5("非卖品商品5", 100, 35.0, 2020, 1, 1);
    ///conGoodsCopy5.show(); CGoods::show(&conGoodsCopy5) ConGoodsCopy* <= const ConGoodsCopy*
    conGoodsCopy5.show();
    return 0;
}
