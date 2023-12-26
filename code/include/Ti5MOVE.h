#ifndef TI5MOVE_H
#define TI5MOVE_H

#include "communication.h"
#include <unistd.h>
#include <cstdlib>
#include "can/SingleCaninterface.h"
#include "can/motortypehelper.h"
#include <vector>
#include "tool.h"
#include "Ti5LOGIC.h"
// #include "Ti5BASIC.h"

#define USLEEPTIME 3000  //socket单条指令通信间隔（微秒）
#define IDNUM 6 //机械臂关节总数
#define RCV_Size (IDNUM+2)*4

extern int AT;  //启停时变速的采样次数
extern float AG;    //启停时变速的采样间距（秒），须>=4*USLEEPTIME
extern float TG;    //启停变速运动时长
extern float scale; //电机内圈与外圈的速度比
extern float n2p;   //内圈转速到步速的转化系数
extern float mvtime;
extern float j2p;   //电机外圈角度到内圈步数的转化
extern class robotArm1 TH;  //机械臂类（正逆运动解算器的接口）
extern float min_time;
extern float NMAX;  //所有电机内核最大转速值（(NMAX/100)圈/秒）
extern float jstep;
extern bool jstp;
extern uint8_t canidList[IDNUM];
extern float atj[IDNUM];
extern int clientFd;
extern float nplL[4][4];// add 用于linear_move函数机械臂直线运动
extern float bais[6],angl[6];   //bais[6]:实际位置相较于理论位置的偏置
// extern char* filename;//数据点存储文件

struct Coordinate {
    double x;
    double y;
    double z;
    double r;
	double p;
	double ry;
};

struct Point3D {
    double x;
    double y;
    double z;
};
// 计算两个向量的点积
//double dotProduct(const Point3D& v1, const Point3D& v2);

// 计算两个向量的叉乘
//Point3D crossProduct(const Point3D& v1, const Point3D& v2);

// 计算三维空间中圆弧上的插值点
/*void calculateArcPoints3D(const Point3D& center, const Point3D& start, const Point3D& end,
                          const Point3D& normal, double radius, int numPoints);*/


/*定义机械臂结构体*/
struct Arm {
    double joint1;
    double joint2;
    double joint3;
    double joint4;
    double joint5;
    double joint6;
};
/*定义路径点结构体*/
struct PathPoint {
    double x;
    double y;
    double z;
    double roll;
    double pitch;
    double yaw;
};

/*坐标点x，y，z*/
struct Point{
	float x;
	float y;
	float z;
	
};


void setn(float npL[IDNUM]);

void movebyn(float npL[IDNUM]);

void rest(int mode);

void ACTmove(float tm,int mode,float nparameterList[][IDNUM]);

void UPRmove(float tm,int mode,float nparameterList[][IDNUM]);

float calcuk(int nmax);

float calcuvmax(int gap,float tm);

float steppersecond(float t,float k,int nmax);

void plan_move(int mode);

bool move_to_joint(int mode);

bool move_to_pos(int mode);

void Upper_controller();

/*机械臂初始化位置*/
void mechanical_arm_origin();

/*直线运动规划*/
void linear_move(Point start, Point end,float stepSize);

/*直线运动的插点
进行插补计算。该函数根据起始点和结束点之间的欧氏距离，将直线分割为一系列均匀间隔的插补点。
*/
void interpolate(Point startPoint, Point endPoint, float stepSize);

/*机械臂手动模式*/
void keyboard_controller();

/*机械臂关节运动
参数：
    *arr：存放坐标点的数组
*/
void joint_movement(const float *arr);

/*机械臂坐标运动
参数：
    *arr：存放坐标点的数组
*/
void pos_movement(const float *arr);

/*圆弧运动，逆时针是正方向
参数：
    O圆心(围绕哪个点)
    U法向量（确定圆是在哪个面转）
    K圆心角（0~2PI）
    startN起始点
*/
bool circle_move(float O[3], float U[3],float K, float startN[6]);

/*获取当前角度*/
int current_angle();

/*获取当前位姿
eg:
    float qqq[6];
    current_pose(qqq);
*/
int current_pose(float posz[]);

/*机械臂刹车*/
bool brake();

/*机械臂是否停止运动*/
bool IsBrake();

/*手动模式记录轨迹*/
void keyboard_save_point();

// void write_value(float array[]);
/*将数据记录下来写入文件
参数：
    pj_flag：角度或者位姿标识,1为角度 ，0为坐标
    filename：存储文件名
    array[6]：被保存的值
*/
void write_value(int pj_flag,string filename,float array[6]);

/*加载作业程序
参数：
    flag：角度或者位姿标识,1为角度 ，0为坐标
    filename：存放数值的文件
    mode：0 为各关节位置环直接到达，1 为匀速同时到达，2 为匀加速度率同时到达。
          在改变量过小时匀加速度率模式会转成匀速模式。
*/
void load_program(int flag,int mode,string filename);

/*
机械臂手动模式:j
参数：
    a：2个数是一组，表示+-，eg：1，2分别是关节1 +，-
    jstep：每次运动的时候增减值
*/
void keyboard_controller_j(int a,float jstep);

/*
机械臂手动模式:pos
参数：
    a:2个数是一组，表示+-，eg：1，2分别是坐标x +，-
    xyzstep:每次运动的时候xyz增减值,单位是毫米
    yprstep:每次运动的时候rpy增减值，单位是弧度
    eg：keyboard_controller_pos(1,1,0.02);
*/
void keyboard_controller_pos(int a,float xyzstep,float yprstep);

//机械臂画心形
void draw_heart();

#endif
