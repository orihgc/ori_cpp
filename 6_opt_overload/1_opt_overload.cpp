//
// Created by orihgc on 2022/8/18.
//
#include <iostream>

using namespace std;

/**
 * C++运算符重载，使对象的运算表现得和编译器内置类型一样
 *
 * */
/// * 复数类
class CComplex {
public:
    CComplex(int r = 0, int i = 0) : mreal(r), mimage(i) {
    }

    ///加法运算符重载函数
    ///指导编译器怎么做类对象的加法操作
    CComplex operator+(const CComplex &src) {
//        CComplex comp;
//        comp.mreal = this->mreal + src.mreal;
//        comp.mimage = this->mimage + src.mimage;
//        return comp;
        return CComplex(this->mreal + src.mreal, this->mimage + src.mimage);
    }

    ///前置++
    CComplex &operator++() {
        mreal += 1;
        mimage += 1;
        return *this;
    }

    ///后置++
    CComplex operator++(int) {
//        CComplex comp = *this;
//        mreal += 1;
//        mimage += 1;
//        return comp;
        return CComplex(mreal++, mimage++);
    }

    void operator+=(const CComplex &src) {
        mreal += src.mreal;
        mimage += src.mimage;
    }

    void show() {
        cout << "read:" << mreal << endl << "image:" << mimage << endl;
    }

private:
    int mreal;
    int mimage;

    ///友元函数
    friend CComplex operator+(const CComplex &lhs, const CComplex &rhs);

    friend ostream &operator<<(ostream &out, const CComplex &src);

};

CComplex operator+(const CComplex &lhs, const CComplex &rhs) {
    return (CComplex(lhs.mimage + rhs.mimage, lhs.mreal + rhs.mreal));
}

ostream &operator<<(ostream &out, const CComplex &src) {
    cout << "read:" << src.mreal << endl << "image:" << src.mimage << endl;
}

int main() {
    CComplex comp1(10, 20);
    CComplex comp2(10, 20);
    /// comp1.operator+(comp2)
    CComplex comp3 = comp1 + comp2;
    ///等价于
    CComplex comp4 = comp1.operator+(comp2);
    comp3.show();


    CComplex comp5;
    /// 20生成临时对象
    comp5 = comp1 + 20;
    ///等价于
    comp5 = comp1.operator+(CComplex(20));
    comp5.show();


    /// 编译器做对象运算的时候，会调用对象的运算符重载函数（优先调用成员方法）；如果没有成员方法
    /// 就在全局作用域找合适的运算符重载函数
    /// :: operator(30,comp1)
    CComplex comp6 = 30 + comp1;
    comp6.show();


    comp6 = comp1++;
    comp1.show();
    comp6.show();
    comp6 = ++comp1;
    comp1.show();
    comp6.show();

    comp1 += comp2;
    comp1.show();

    //由于对象在右边，一定不是成员方法
    //cout ::operator<<(cout,comp1)<<endl;
    //ostream& operator<<(ostream &out,const CComplex &src)<<endl;
    cout << comp1 << comp2 << endl;
    return 0;
}

template<typename T>
void show(T a) {
    cout << a << endl;
}
