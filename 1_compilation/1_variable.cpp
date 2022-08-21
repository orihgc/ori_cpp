//
// Created by orihgc on 2022/8/4.
//

using namespace std;

///全局变量，不论是否是静态变量，初始化后的都放在.data段，未初始化的放在.bss段
int gdata1 = 10;
int gdata2 = 0;
int gdata3;

static int gdata4 = 11;
static int gdata5 = 0;
static int gdata6;

int main() {
    int a = 12;
    int b = 0;
    int c;

    static int e = 13;
    static int f = 0;
    static int g;

    return 0;
}