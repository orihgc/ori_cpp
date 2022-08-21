
#include <iostream>

using namespace std;


//region 概念
/**
 * inline内联函数：在编译过程中，没有函数调用开销，在函数的调用点直接把函数的代码进行展开处理了
 * inline函数不再生成相应的函数符号
 *
 * inline只是建议编译器把函数处理成内联函数
 * 不是所有的inline都会被编译器处理成内联函数 比如递归、或者函数过长
 *
 * debug版本上inline不起作用; inline只在release版本下才出现
 * */
//endregion

inline int sum(int x, int y) {
    return x + y;
}

int main() {
    int a = 10;
    int b = 20;
    int ret = sum(a, b);
    return 0;
}
