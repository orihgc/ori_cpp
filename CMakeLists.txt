cmake_minimum_required(VERSION 3.22)
project(ori_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)

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

add_executable(8_1_vector 8_STL/1_vector.cpp)
add_executable(8_2_deque_list 8_STL/2_deque_list.cpp)
add_executable(8_3_adapter 8_STL/3_adapter.cpp)
add_executable(8_4_unordered_container 8_STL/4_unordered_container.cpp)
add_executable(8_5_ordered_container 8_STL/5_ordered_container.cpp)

add_executable(9_1_thread 9_thread/1_thread.cpp)
add_executable(9_2_thread_gc 9_thread/2_thread_gc.cpp)
add_executable(9_3_this_thread 9_thread/3_this_thread.cpp)
add_executable(9_4_call_once 9_thread/4_call_once.cpp)
add_executable(9_5_native_handle 9_thread/5_native_handle.cpp)
add_executable(9_6_lock 9_thread/6_lock.cpp)
add_executable(9_7_condition_variable 9_thread/7_condition_variable.cpp)
add_executable(9_8_atomic 9_thread/8_atomic.cpp)

add_executable(11_1_type 11_new_features/1_availability.cpp)
add_executable(11_3_init_list 11_new_features/2_runtime.cpp)
add_executable(11_3_right_reference 11_new_features/3_right_reference.cpp)
add_executable(11_4_container 11_new_features/4_container.cpp)
add_executable(11_5_smart_ptr 11_new_features/5_smart_ptr.cpp)
add_executable(11_2_exception 11_new_features/6_exception.cpp)

add_executable(12_1_rall 12_geeks/1_rall.cpp)
add_executable(12_2_smart_ptr 12_geeks/2_smart_ptr.cpp)
add_executable(12_3_right_value 12_geeks/3_right_value.cpp)
