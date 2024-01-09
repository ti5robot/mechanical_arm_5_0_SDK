#ifndef Ti5BASIC_H
#define Ti5BASIC_H

#include <stdio.h>
#include <stdlib.h>

// #include <libudev.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <map>



#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

// #include "can/SingleCaninterface.h"
// #include "can/motortypehelper.h"

#include "Ti5LOGIC.h"
#include "Ti5MOVE.h"

#include "can/tcontrolcanfactor.h"


#define MAX_IP_ADDR_LEN 256 //存储IP地址的最大长度
//#define LOG_PATH "/mnt/hgfs/mechanical_arm/log/daily_logger.log" //log路径
#define INI_PATH "../config.ini" //config.ini文件路径

extern float arr_s[6];

extern bool flag;

extern uint32_t reg_position_kp[6];//位置环比例
extern uint32_t reg_position_kd[6];//位置环微分

extern uint32_t reg_speed_kp[6];    //速度环比例
extern uint32_t reg_speed_ki[6];    //速度环积分

extern uint32_t reg_max_curr_value[6]; //最大正电流
extern uint32_t reg_min_curr_value[6]; //最小负电流

extern uint32_t reg_max_app_speed[6]; //最大正向允许速度
extern uint32_t reg_min_app_speed[6]; //最小负向允许速度

extern uint32_t reg_max_app_position[6];//电机最大正向位
extern uint32_t reg_min_app_position[6];//电机最大负向位

extern uint32_t electricity[6];//电流值
extern uint32_t electric_machinery[6];//电机错误状态
extern uint32_t reg_fault_clear[6];//清除电机错误
extern uint32_t AAA[6];//电机电流值

extern string log_path;//log文件

extern string SDKversion;//SDK version

//查询机械臂是否停止运动
bool inspect_brake();

void exit_progrem();//退出程序

std::string SDK_version();//SDK版本号

std::string ip_address();

// void loggerinfo(string content);//添加log

/*获取usb插入的设备*/
std::string udevice();

void read_ini_information();//读取ini配置文件的内容

void login();//登录can设备

void logout();//登出can设备

/*std::string query_can();
查询can设备号
*/ 
std::vector<std::string> query_can();

//获取电机参数
void get_elc_info();

/*设置电机参数
参数: 
  elc_parameterlist 要设置的对应电机
  elc_value 要设置的n个电机
  parameterType 要设置的项目
  elc_value 新值
*/
void set_elc_info(uint32_t *elc_parameterlist,int elc_num, int parameterType,uint32_t elc_value);

/*获取电机电流值
返回值：true为无异常，false为异常
*/
bool get_electricity_status();

/*获取电机错误状态
  返回值：为电机错误
    0：无错误
    1：软件错误
    2：过压
    4：欠压
    16：启动错误
*/
int get_elektrische_Maschinen_status();

/*将当前角度值设为0点*/
void set_currentangle_to_zeropoints(string filename);

/*清除电机错误*/
void clear_elc_error();

/*
uart485通讯
参数：
  device_485_name：设备
*/
int uart485_communication(char *device_485_name);
uint16_t merge_bytes(uint8_t high, uint8_t low);
void parse_data(const uint8_t *bytes, int32_t *values);
#endif

