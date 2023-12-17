---
sort: 1
---

# SDK介绍

机械臂控制的代码code中，分别是`include`，`src`，`log`以及`usrlib`。

+ [include](https://github.com/mrhouse-sweet/mechanical_arm_SDK-docs/tree/main/code/include) 存储着机械臂所需的头文件。
+ [src](https://github.com/mrhouse-sweet/mechanical_arm_SDK-docs/tree/main/code/src) 一般控制机械臂的文件放在此处，其中`main.cpp`是一个示例程序。
+ [log](https://github.com/mrhouse-sweet/mechanical_arm_SDK-docs/tree/main/code/log) sdk中存放log的文件夹。
+ [usrlib](https://github.com/mrhouse-sweet/mechanical_arm_SDK-docs/tree/main/code/usrlib)包含SDK所需的so文件

## 1. include

除以下提到的文件外，用户无需查看该文件夹下的其他文件。

### 1.1 mathfunc.h
机械臂的数学模型函数


### 1.2 Ti5BASIC.h

机械臂控制基础库，包含了基本控制以及信息，用户在使用时需要根据自身使用方式自行选择调用。

+ bool inspect_brake();//函数功能：查询机械臂是否停止运动

+ void exit_progrem();//函数功能：退出程序

+ std::string SDK_version();//函数功能：SDK版本号

+ void loggerinfo(string content);//函数功能：添加log

+ void login();//函数功能：登录can设备

+ void logout();//函数功能：登出can设备

+ std::vector<std::string> query_can();//函数功能：查询can设备号

+ void get_elc_info();//函数功能：获取电机参数

+ void set_elc_info(uint32_t *elc_parameterlist,int elc_num, int parameterType,uint32_t elc_value);//设置电机参数

参数: 
  elc_parameterlist 要设置的对应电机，
  elc_value 要设置的第n个电机，
  parameterType 要设置的项目，
  elc_value 新值

### 1.3 Ti5LOGIC.h

该文件是机械臂的算法库，包括正逆解，碰撞检测，规划路径等。
使用方法：根据需求在规划机械臂运动的时候可以调用该库的函数。

### 1.4 Ti5MOVE.h

机械臂运动控制库，包含的功能有直线运动，圆弧运动，机械臂初始化，机械臂手动模式控制，机械臂关节运动，机械臂坐标运动，获取机械臂当前角度值，获取机械臂当前位姿，机械臂刹车，查看机械臂是否停止运动，机械臂手动规划路径点并记录到文件中，机械臂加载路径文件。

+ void mechanical_arm_origin();//机械臂初始化位置

+ void keyboard_controller();//机械臂手动模式

+ void joint_movement(const float *arr);//机械臂关节运动

+ void pos_movement(const float *arr);//机械臂坐标运动

+ bool circle_move(float O[3], float U[3],float K, float startN[6]);// 圆弧运动，逆时针是正方向，参数：O圆心(围绕哪个点)，U法向量（确定圆是在哪个面转），K圆心角（0~2PI），startN起始点

+ int current_angle();//获取当前角度

+ void linear_move(Point start, Point end,float stepSize);//直线运动规划，参数：start：起点 ，end：终点，stepSize：步长

+ int current_pose(float posz[]);//获取当前位姿

+ bool brake();//机械臂刹车

+ bool IsBrake();//机械臂是否停止运动



### 1.5 tool.h

该文件是一些`tool`，具体函数使用及参数请查看该文件。

### 1.6. can
该文件夹包含`can`通讯的头文件，机械臂是通过can通讯与控制机联通的，具体函数功能及参数请查看里面所包含的文件中注释了解函数作用。

## 3.src
### 3.1 main.cpp

该文件是一个简单的示例程序，调用了`Ti5BASIC.h`中的`query_can()`函数，首先查找是否连接了can设备，然后调用`mechanical_arm_origin()`让机械臂回到初始位置，接下来调用`tool.h`中的`show_value()`函数，显示此时的位姿信息，还有一个简单的类似码垛的动作。

### 3.2 gcc.sh

该文件中的内容是编译命令，编译的时候可以使用该命令直接编译，也可以使用g++命令+对应参数直接编译

### 3.2 编译

最后执行`gcc.sh`文件进行编译或通过以下命令进行编译生成可执行文件`move_sov`。(注意：以下路径是默认路径，如果修改了路径要替换成自己的)
```
g++ main.cpp  -L./include -lmylibti5 -L./include/can -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov
```
**运行**:
```
sudo ./move_sov
```
注意机械臂处在一个安全的环境中

## 解算器说明
（1）地面定义为基坐标中z=0的平面。

（2）原始关节角度区间（不考虑碰撞）：逆运动j解集[-pi,pi)，正运动j定义域[-pi,pi]；正运动ypr解集，p属于[-pi,pi)，r、y属于pi/2~pi/2，逆运动ypr定义域[-pi,pi)。

（3）逆运动原始解空间（不考虑碰撞）为半径一定的球，球心坐标随ypr改变。

（4）在末端三个关节自由旋转360度的情况下设置了静态的碰撞区间。

（5）逆运动的解通过对比变换矩阵判断正确性。


## 开发须知
（1）代码中一切角大小相关的量采用弧度制（bais由角度制自动转向弧度制）。

（2）机械臂的一切控制基于robotArm类，传参方式为直接改变TH.j或TH.pos的值。

（3）TH.j与TH.pos代表数学模型的理论值，需要借由bais校准到实际发送的理论值。

（4）相邻两次指令发送时间低于USLEEPTIME可能信息堵塞。

（5）由于电机内部的算法，指令发送的值与实际执行的值有微小误差。

（6）位置环与速度环都是直接控制电机内圈，因此从外到内涉及scale的放缩。“位置环参数”单位为“步”，“速度环参数/100”单位为“圈/秒”。一圈65536步。

（7）move函数的参数mode，值0为各关节位置环直接到达，1为匀速同时到达，2为匀加速度率同时到达。在改变量过小时匀加速度率模式会转成匀速模式。

