//
// Created by ByteDance on 2022/12/18.
//

#include "iostream"
#include "vector"
#include "array"
#include <tuple>

using namespace std;

//region 线性容器
///region std:array
/// vector的缺点
/// 另外由于 std::vector 是自动扩容的，当存入大量的数据后，并且对容器进行了删除操作，
/// 容器并不会自动归还被删除元素相应的内存，这时候就需要手动运行 shrink_to_fit() 释放这部分内存
void fun1() {
    std::vector<int> v;
    std::cout << "size:" << v.size() << std::endl;         // 输出 0
    std::cout << "capacity:" << v.capacity() << std::endl; // 输出 0

// 如下可看出 std::vector 的存储是自动管理的，按需自动扩张
// 但是如果空间不足，需要重新分配更多内存，而重分配内存通常是性能上有开销的操作
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    std::cout << "size:" << v.size() << std::endl;         // 输出 3
    std::cout << "capacity:" << v.capacity() << std::endl; // 输出 4

// 这里的自动扩张逻辑与 Golang 的 slice 很像
    v.push_back(4);
    v.push_back(5);
    std::cout << "size:" << v.size() << std::endl;         // 输出 5
    std::cout << "capacity:" << v.capacity() << std::endl; // 输出 8

// 如下可看出容器虽然清空了元素，但是被清空元素的内存并没有归还
    v.clear();
    std::cout << "size:" << v.size() << std::endl;         // 输出 0
    std::cout << "capacity:" << v.capacity() << std::endl; // 输出 8

// 额外内存可通过 shrink_to_fit() 调用返回给系统
    v.shrink_to_fit();
    std::cout << "size:" << v.size() << std::endl;         // 输出 0
    std::cout << "capacity:" << v.capacity() << std::endl; // 输出 0

}

/// array的优点
/// 使用 std::array 能够让代码变得更加“现代化”，而且封装了一些操作函数，比如获取数组大小以及检查是否非空，同时还能够友好的使用标准库中的容器算法
void fun2(){
    std::array<int, 4> arr = {1, 2, 3, 4};

    arr.empty(); // 检查容器是否为空
    arr.size();  // 返回容纳的元素数

// 迭代器支持
    for (auto &i : arr)
    {
        // ...
    }

// 用 lambda 表达式排序
    std::sort(arr.begin(), arr.end(), [](int a, int b) {
        return b < a;
    });
    std::sort(arr.begin(),arr.end());

// 数组大小参数必须是常量表达式
    constexpr int len = 4;
    std::array<int, len> arr2 = {1, 2, 3, 4};

// 非法,不同于 C 风格数组，std::array 不会自动退化成 T*
// int *arr_p = arr;
}

/// 兼容c的接口
void foo(int *p, int len) {
    return;
}

void fun3(){
    std::array<int, 4> arr = {1,2,3,4};

// C 风格接口传参
// foo(arr, arr.size()); // 非法, 无法隐式转换
    foo(&arr[0], arr.size());
    foo(arr.data(), arr.size());

// 使用 `std::sort`
    std::sort(arr.begin(), arr.end());
}
///endregion

///region forward_list

///endregion
//endregion

//region 无序容器
//endregion

//region 元组
auto get_student(int id)
{
    // 返回类型被推断为 std::tuple<double, char, std::string>

    if (id == 0)
        return std::make_tuple(3.8, 'A', "张三");
    if (id == 1)
        return std::make_tuple(2.9, 'C', "李四");
    if (id == 2)
        return std::make_tuple(1.7, 'D', "王五");
    return std::make_tuple(0.0, 'D', "null");
    // 如果只写 0 会出现推断错误, 编译失败
}

int main()
{
    auto student = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student) << ", "
              << "成绩: " << std::get<1>(student) << ", "
              << "姓名: " << std::get<2>(student) << '\n';

    double gpa;
    char grade;
    std::string name;

    // 元组进行拆包
    std::tie(gpa, grade, name) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << gpa << ", "
              << "成绩: " << grade << ", "
              << "姓名: " << name << '\n';

    ///std::get 除了使用常量获取元组对象外，C++14 增加了使用类型来获取元组中的对象：
    std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
    std::cout << std::get<std::string>(t) << std::endl;
//    std::cout << std::get<double>(t) << std::endl; // 非法, 引发编译期错误
    std::cout << std::get<3>(t) << std::endl;

}


//endregion



