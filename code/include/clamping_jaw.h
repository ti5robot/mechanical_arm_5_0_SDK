#ifndef CLAMPING_JAW_H
#define CLAMPING_JAW_H
#include <Python.h>
#include <iostream>


extern "C" //添加extern "C"
{
    int clamp_jaw_close();//夹爪合
    int clamp_jaw_open();//夹爪闭
}//添加extern "C"

//下面是夹爪带参数的实现
// extern "C" //添加extern "C"
// {
//     int clamp_jaw_close(const std::string& pythonPath);//夹爪合
//     int clamp_jaw_open(const std::string& pythonPath);//夹爪闭
// }//添加extern "C"


#endif