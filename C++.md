# 核心

## 进程虚拟地址空间区域划分

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h4v5bup0ksj20np0hqjtw.jpg" alt="image-20220804232248724" style="zoom:50%;" />

- 静态局部变量、静态全局变量、全局变量
  - 初始化过的放在.data段
  - 未初始化的放在.bss段（包括初始化为0的变量）
- 局部变量
  - 普通局部变量不产生符号，只会产生指令，将数据压栈
  - `int a=12`局部变量赋值语句编译后是个指令`mov dword ptr[ebp-4]`，存放在.text段上
  - 指令运行的时候，会在栈上开辟空间存放局部变量
- .text 段主要放指令
- .rodata 只读数据端，例如存放常量字符串
- .data 存放初始化的且不为0的变量
- .bss 存放未初始化的或者初始化为0的变量

- .heap 运行时堆
- stack 端是线程私有的，里面存放各种栈帧

## 函数的调用堆栈的详细过程

```c++
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
```

## 编译和连接原理

- 编译过程

  - 预编译：处理#开头的命令

    `#pragma lib`和`#pragma lib`在连接阶段处理，除此之外的`#开头的命令都在预编译阶段处理`

  - 编译：语法分析、语义分析、词法分析、代码优化，生成相应平台架构下的汇编指令

  - 汇编：生成.o文件，

  - 二进制可重定位的目标文件.o

    elf文件头、.text、.data、.bss、.symbal、.section table

  <!--编译过程中符合不分配虚拟地址-->

- 链接
  - 所有.o文件段的合并，符号表合并后，进行符合解析（所有对符号的引用，都要找到符号定义的地方）
  - 符号的重定位，这是链接的核心
  - 最后就会生成可执行文件

- 编译实操

  - 源码

    main.cpp

  ```c++
  extern int gdata;
  int data = 20;
  
  static int sData=10;
  
  int sub(int a, int b);
  
  int main() {
      int a = data;
      int b = gdata;
      int res = sub(a, b);
      return 0;
  }
  ```

  ​       sub.cpp

  ```c++
  int gdata = 10;
  
  int sub(int a, int b) {
      int temp = a - b;
      return temp;
  }
  ```

  - 符号表

  <img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h4vmpkfkpfj20pu0ccwfk.jpg" alt="image-20220805092412963" style="zoom:50%;" />

  

  <img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h4vmn4zcawj20xw0u0ju2.jpg" alt="image-20220805092153278" style="zoom:50%;" />

- 链接实操

  mian.o和sub.o合并：将.text、.data、.bss段都进行合并

  - 符号解析

    “UND”符号可以出现多个，也就是符号引用可以很多

    但符号的定义只能有一个，符号解析就是所有符合的引用都要找到符号定义的地方

  - 给所有符号分配虚拟地址

  - 符合的重定向，给指令中引用符号的地方都替换为符号正确的地址

  <img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h4vnalri7ij213g0oin0a.jpg" alt="image-20220805094425798" style="zoom:50%;" />

  - 连接成功 objdump -S a.out

  <img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h4vnccujsgj20u00uv0vx.jpg" alt="image-20220805094607128" style="zoom:50%;" />
  
  - a.out 磁盘上
    - .out文件会生成paogram headers，有两个load，告诉系统运行此程序时把哪些内容加载到内存中。
    - .out文件的文件头elf header中存放了程序的入口地址
  
  - out可执行文件的执行过程
    - 根据program headers，加载.text、.data等段中的内容到内存中
    - 格努文件头elf header中的程序入口地址，执行该程序的第一条指令。
  

