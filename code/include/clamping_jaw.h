#ifndef CLAMPING_JAW_H
#define CLAMPING_JAW_H
#include <Python.h>
#include <iostream>

// // 没有参数的夹爪实现
// extern "C" //添加extern "C"
// {
//     /*夹爪合，返回值：成功返回0，失败返回-1*/
//     int clamp_jaw_close();//夹爪合

//     /*夹爪开，返回值：成功返回0，失败返回-1*/
//     int clamp_jaw_open();//夹爪开
// }//添加extern "C"

//下面是夹爪带参数的实现
extern "C" //添加extern "C"
{
    /*夹爪合
        参数pythonPath：夹爪依赖库安装地址
        返回值：成功返回0，失败返回-1*/
    int clamp_jaw_close(const std::string& pythonPath);//夹爪合
    /*夹爪开
        参数pythonPath：夹爪依赖库安装地址
        返回值：成功返回0，失败返回-1*/
    int clamp_jaw_open(const std::string& pythonPath);//夹爪开
}//添加extern "C"


#endif