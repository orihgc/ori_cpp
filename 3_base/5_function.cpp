
#include <iostream>

using namespace std;


/**
 * 1、给默认值的时候从右向左给
 * 2、定义的时候可以给形参默认值，声明处也可以给形参默认值
 * 3、形参给默认值的时候，不管定义处还是声明处，形参默认值只能给一次
 * */
int sum(int a, int b = 20) {
    return a + b;
}

int main() {
    int a = 10;
    int b = 20;

    int ret = sum(a);

    cout << "ret:" << ret << endl;

    return 0;
}
