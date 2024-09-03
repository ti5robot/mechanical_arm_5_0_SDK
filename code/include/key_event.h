#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <pthread.h>

#include "Ti5MOVE.h"
#define INPUT_DEVICE "/dev/input/event3"

extern const char *Joystick_command;//获取手柄信息，将手柄设备信息存放文件
extern const char *Joystick_file_path;//手柄设备信息存放文件
extern char *Joystick_file_buff;
extern int Joystick_number;//event号
extern char Joystick_event_string[20]; // 用于存储找到的手柄事件名称
extern char Joystick_input_device[50]; // 用于存储手柄设备路径
#define DBG_PRINTF printf

int find_event();

extern int fd;

// 检查指定的按键是否被按下
int is_button_pressed(int code);

// 监控按键状态的线程函数
void *monitor_buttons(void *arg);

//手柄控制机械臂
void *key_control(void *arg);

//执行程序
bool start_key();


