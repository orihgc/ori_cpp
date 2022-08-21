
#include <iostream>

using namespace std;

/**
 * const修饰的变量不能再作为左值，初始化完成后，值不能被修改
 *
 * c和c++中的区别:
 * c里面，const修饰的值不叫常量，叫做常变量，可以通过指针修改其内存的值
 * c++里面，const修饰的值必须初始化，叫做常量
 * 编译方式不同：c中const是当作一个变量来编译生成指令的
 * c++中，所有出现const常量名字的地方，都被常量的初始化替换了，所以int array[b]实际上是array[20]
 * */
int main() {

    int a = 10;
    a = 20;

    /**
     * 常量定义: const int b=20;
     * 常变量：const int b=a;
     * */
    const int b = 20;
    int array[b] = {};

    int *p = (int *) &b;
    *p = 30;

    /**
     * c里面输出全是30，因为是一个常变量
     * c++里面输出30 20 30，因为是常量
     * 之所以输出b为20，是因为在编译阶段已经将b替换为20了
     * */
    cout << *p << " " << b << " " << *(&b) << endl;

    return 0;
}
