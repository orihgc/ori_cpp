//
// Created by orihgc on 2022/8/4.
//
#include "iostream"

using namespace std;

int sum(int a, int b) {
    ///push ebp 将main栈帧的地址入栈
    ///mov ebp,esp 将esp赋给ebp 此时ebp指向sum栈帧的栈底
    ///sub esp,4Ch 给sum开辟栈帧空间，将栈帧空间都初始化为0xCCCCCCCC

    /// mov dword prt[ebp-4],0 为temp开辟空间
    /// mov eax,dword prt[ebp+0Ch]
    /// add eax, dword prt[ebp+8]
    /// mov dword prr[ebp-4],eax
    int temp = a + b;
    /// mov eax,dword prt[ebp-4] 将temp值放在eax中返回
    return temp;

    /// mov esp,ebp 回退栈帧
    /// pop ebp 出栈并把值赋给ebp，这样ebp又回到main栈帧的栈底
    /// ret 把出栈的内容放入CPU的PC寄存器中，PC寄存器存放下一行指令的地址，就去运行call sum的下一行指令了。
}

int main() {
    int a = 10; ///mov dword ptr[ebp-4],0Ah
    int b = 20; ///mov dword ptr[ebp-8],14h

    /**
     * 先为res申请4 字节空间 ptr[ebp-0Ch]
     * 一个函数的调用需要从右往左压参数，先压b
     * mov eax,dword prt[ebp-8]
     * push eax
     * mov eax,dword prt[ebp-4]
     * push eax
     *
     * call sum 函数调用指令
     * 1、将这行指令的下一行指令的地址压栈，也就是把第二步的地址入栈
     * 2、add esp,8 释放形参空间
     * 3、mov dword ptr[ebp-0Ch],eax 将sum的结果赋值给res空间
     * */
    int res = sum(a, b);
    cout << res;
    return res;
}


