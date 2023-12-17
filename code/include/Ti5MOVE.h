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

#define USLEEPTIME 3000
#define IDNUM 6
#define RCV_Size (IDNUM+2)*4

extern int AT;
extern float AG;//>=4*USLEEPTIME
extern float TG;
extern float scale;
extern float n2p;
extern float mvtime;
extern float j2p;
extern class robotArm1 TH;
extern float min_time;
extern float NMAX;
extern float jstep;
extern bool jstp;
extern uint8_t canidList[IDNUM];
extern float atj[IDNUM];
extern int clientFd;
extern float nplL[4][4];//mfs add 用于linear_move函数机械臂直线运动
extern float bais[6],angl[6];
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


// 定义机械臂结构体
struct Arm {
    double joint1;
    double joint2;
    double joint3;
    double joint4;
    double joint5;
    double joint6;
};
// 定义路径点结构体
struct PathPoint {
    double x;
    double y;
    double z;
    double roll;
    double pitch;
    double yaw;
};

//坐标点x，y，z
struct Point{
	float x;
	float y;
	float z;
	
};

//直线运动规划
// void linear_move();
void linear_move(Point start, Point end,float stepSize);

//直线运动的插点
// 进行插补计算。该函数根据起始点和结束点之间的欧氏距离，将直线分割为一系列均匀间隔的插补点。
void interpolate(Point startPoint, Point endPoint, float stepSize);

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

//机械臂初始化位置
void mechanical_arm_origin();

//机械臂手动模式
void keyboard_controller();

//机械臂关节运动
void joint_movement(const float *arr);

//机械臂坐标运动
void pos_movement(const float *arr);

// 圆弧运动，逆时针是正方向
// 参数：O圆心(围绕哪个点)，U法向量（确定圆是在哪个面转），K圆心角（0~2PI），startN起始点
bool circle_move(float O[3], float U[3],float K, float startN[6]);

//获取当前角度
int current_angle();

//获取当前位姿
int current_pose(float posz[]);

//机械臂刹车
bool brake();

//机械臂是否停止运动
bool IsBrake();

//手动模式记录轨迹
void keyboard_save_point();

// void write_value(float array[]);
void write_value(string filename,float array[6]);
//加载作业程序
void load_program(string filename);

/*
 机械臂手动模式:j
2个数是一组，表示+-，eg：1，2分别是关节1 +，-
*/
void keyboard_controller_j(int a,float jstep);
/*
 机械臂手动模式:pos
2个数是一组，表示+-，eg：1，2分别是坐标x +，-
机械臂手动模式:pos
*/
void keyboard_controller_pos(int a,float xyzstep,float yprstep);

//机械臂画心形
void draw_heart();

#endif
