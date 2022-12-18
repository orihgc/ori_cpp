cmake_minimum_required(VERSION 3.22)
project(ori_cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(4_oop/2_constructor)

add_executable(3_1_new_malloc 3_base/1_new_malloc.cpp)
add_executable(3_2_quote 3_base/2_quote.cpp)
add_executable(3_3_const 3_base/3_const.cpp)
add_executable(3_4_const_quote 3_base/4_const_quote.cpp)
add_executable(3_5_function 3_base/5_function.cpp)
add_executable(3_6_inline 3_base/6_inline.cpp)
add_executable(3_7_function_reload 3_base/7_function_reload.cpp)


add_executable(4_1_class 4_oop/1_class/CGoods.cpp)
add_executable(4_2_constructor 4_oop/2_constructor/SeqStack.cpp)
add_executable(4_3_copy_CopySeqStack 4_oop/3_copy/CopySeqStack.cpp)
add_executable(4_3_copy_Queue 4_oop/3_copy/Queue.cpp)
add_executable(4_3_copy_String 4_oop/3_copy/String.cpp)
add_executable(4_4_constructor_init_list 4_oop/4_constructor_init_list/ConGoods.cpp)
add_executable(4_5_class_func 4_oop/5_class_func.cpp)
add_executable(4_6_class_quote 4_oop/6_class_quote.cpp)

add_executable(5_1_func_template 5_template/1_func_template.cpp)
add_executable(5_2_class_template 5_template/2_class_template.cpp)
add_executable(5_3_vector_template 5_template/3_vector_template.cpp)
add_executable(5_4_allocator 5_template/4_allocator.cpp)

#继承
add_executable(1_extend 7_extend/1_extend.cpp)
#构造过程
add_executable(2_derive 7_extend/2_derive.cpp)
#重载、隐藏、覆盖
add_executable(3_overload_hide_cover 7_extend/3_overload_hide_cover.cpp)
#虚函数
add_executable(4_virtual 7_extend/4_virtual.cpp)
#动态绑定
add_executable(5_polymorphism 7_extend/5_polymorphism.cpp)
#抽象类
add_executable(6_abstract 7_extend/6_abstract.cpp)
#虚基类
add_executable(7_multi_extend 7_extend/7_multi_extend.cpp)
#虚继承
add_executable(8_diamond_extend 7_extend/8_diamond_extend.cpp)
#虚析构函数
add_executable(9_virtual_destruct 7_extend/9_virtual_destruct.cpp)
#类型转换
add_executable(10_type_conversion 7_extend/10_type_conversion.cpp)
