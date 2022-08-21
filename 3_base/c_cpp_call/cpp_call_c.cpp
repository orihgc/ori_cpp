//
// Created by orihgc on 2022/8/9.
//

#include <iostream>

using namespace std;


/**
 * __cplusplus 表示要用c语言方式进行编译
 * */
#ifdef __cplusplus
extern "C" {
#endif
int call_cpp(int a, int b) {
    return a + b;
}

int call_c(int a, int b);

#ifdef __cplusplus
};
#endif

int main() {
    int a = 10, b = 20;
    int res = call_c(a, b);
    cout << res;
}

