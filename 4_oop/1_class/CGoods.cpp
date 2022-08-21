//
// Created by orihgc on 2022/8/10.
//

#include "CGoods.h"
#include "iostream"

int CGoods::getAmount() {

}

const char *CGoods::getName() {

}

double CGoods::getPrice() {

}

void CGoods::init(char *name, double price, int amount) {
    strcpy(_name, name);
    _price = price;
    _amount = amount;
}

void CGoods::setAmount(int amount) {

}

void CGoods::setPrice(double name) {

}

void CGoods::show() {
    std::cout << _name << std::endl;
    std::cout << _price << std::endl;
    std::cout << _amount << std::endl;

}

void CGoods::setName(char *name) {

}

int main() {
    auto *pGoods = new CGoods();
    const char a[] = "hello";
    pGoods->init("hello", 24.0, 10);
    pGoods->show();

    return 0;
}
