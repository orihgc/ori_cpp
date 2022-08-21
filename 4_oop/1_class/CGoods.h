//
// Created by orihgc on 2022/8/10.
//

#ifndef ORI_CPP_CGOODS_H
#define ORI_CPP_CGOODS_H

const int NAME_LEN = 20;

class CGoods {
private:
    char _name[NAME_LEN];
    double _price;
    int _amount;
public:
    void init(char *name, double price, int amount);

    void show();

    ///如果在class体内提供方法实现，自动处理为内联函数
    void setName(char *name);

    void setPrice(double name);

    void setAmount(int amount);

    const char *getName();

    double getPrice();

    int getAmount();
};

#endif //ORI_CPP_CGOODS_H
