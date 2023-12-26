#ifndef _TI5LOGIC_H_
#define _TI5LOGIC_H_

#include <mathfunc.h>
#include <iostream>
#include <time.h>
#include <cmath>
#include <tool.h>
using namespace std;

class pos_trans
{
private:
	float prcj = 0.017;
	float scd = sin(prcj) * sin(prcj);
	float prc1 = float(int(10000 * sin(prcj) + 1)) / 10000;
	float prc2 = prc1 * (prc1 + 2);
	float prc3 = prc1 * (3 + prc1 + prc1 * prc1) + prc2;

	

protected:
	float P_0[19][3] = {{0, 0, 0}};			// 机械臂按线性顺序的点集
	float jr1[6]={-pi,-pi,-pi,-pi,-pi,-pi};//关节静态角度范围
	float jr2[6]={pi,pi,pi,pi,pi,pi};
	int O[7] = {0};							// 存放坐标系0~6原点分别对应P_0哪个点
	struct ROD
	{
		int i1, i2; // 连杆端点为P_0[i1]和P_0[i2]
		float r;	// 连杆半径
		float l;	// 连杆长度
	};
	ROD rod[18];   // 机械臂按线性顺序的连杆集
	float len[18]; // 数学模型的长度参数（与rod.l独立）
	int rodnum;	   // 连杆总数
	void init_rodindex();
	// 检测两连杆是否碰撞，P1、P2构成一根连杆，半径为r1；P3、P4构成另一根连杆，半径为r2
	bool LLcolsp(float P1[3], float P2[3], float P3[3], float P4[3], float r1, float r2);
	// 若点距和连杆长度一致则认为点坐标值正确
	bool check_Points();
	int gotostep(int now, bool recall, bool *dft);
	// 根据变换矩阵计算位姿
	bool MatrixT2Pos(float T[4][4], bool mend);
	// 根据位姿计算变换矩阵
	void Pos2MatrixT(float T[4][4]);
	bool mendjoints(float j0[6]);
	// 检测所有连杆间的碰撞
	bool check_colsp();
	
	

public:
	int rc = 0;
	float j[6] = {0, 0, 0, 0, 0, 0};	//各关节值
	float pos[6];	//末端动态位姿与初始位姿(x,y,z,yaw,pitch,roll)
	float gap0,gap;
	// 检测逆运动解出的角是否满足原始位姿
	bool checkacc(float T[4][4]);
};

class robotArm1 : public pos_trans
{
private:
	int rball;
	void (robotArm1::*Si2Sj[6])(float *, float *, bool) = {&robotArm1::fromS1toS0, &robotArm1::fromS2toS1, &robotArm1::fromS3toS2, &robotArm1::fromS4toS3, &robotArm1::fromS5toS4, &robotArm1::fromS6toS5};

	void init_arm_structure()
	{
		// // rodnum = 8;
		// rod[0].r = 30, rod[1].r = 30, rod[2].r = 24, rod[3].r = 24, rod[4].r = 25, rod[5].r = 0, rod[6].r = 24, rod[7].r = 25;//1kg
		// rod[0].l = 130, rod[1].l = 98.57, rod[2].l = 190, rod[3].l = 98.57, rod[4].l = 65, rod[5].l = sqrt(98.57 * 98.57 + 125 * 125), rod[6].l = 98.57, rod[7].l = 65.2;//1kg，连杆长度

		// rod[0].r = 34, rod[1].r = 34, rod[2].r = 28.7, rod[3].r = 30, rod[4].r = 30, rod[5].r = 0, rod[6].r = 30, rod[7].r = 30;//2kg
		// rod[0].l = 158.6, rod[1].l = 116.5, rod[2].l = 260, rod[3].l = 116.5, rod[4].l = 85, rod[5].l = sqrt( 107* 107 +  174.5* 174.5), rod[6].l =  107, rod[7].l = 87.5;//2kg

		rod[0].r = 45.5, rod[1].r = 45.5, rod[2].r = 53.5, rod[3].r = 40, rod[4].r = 39, rod[5].r = 0, rod[6].r = 39, rod[7].r = 39;//3kg  
		rod[0].l = 190, rod[1].l = 168, rod[2].l = 300, rod[3].l = 168, rod[4].l = 160, rod[5].l = sqrt(140 * 140 + 147 * 147), rod[6].l = 147, rod[7].l = 96;//3kg，连杆长度
	
		init_rodindex();
	}
	// 初始化数学模型参数
	void init_model_structure()
	{
		O[1] = 1, O[2] = 1, O[3] = 4, O[4] = 5, O[5] = 7, O[6] = 8;
		float M=2*pi;
		jr1[0]=-M,jr1[1]=-M,jr1[2]=-M,jr1[3]=-M,jr1[4]=-3*pi/2,jr1[5]=-M;
		jr2[0]=3.2,jr2[1]=M,jr2[2]=M,jr2[3]=M,jr2[4]=pi/2,jr2[5]=M;
		gap=abs(jr1[0]);for(int i=1;i<6;i++) if(abs(jr1[i])>gap) gap=abs(jr1[i]);for(int i=0;i<6;i++) if(abs(jr2[i])>gap) gap=abs(jr2[i]);
		gap0=gap;
		// len[0] = 137, len[1] = 190, len[2] = 65, len[3] = 125, len[4] = 65, len[5] = 98.57, len[6] = 98.57, len[7] = 98.57;//1kg
		// len[0] = 158.6, len[1] = 260, len[2] = 85, len[3] = 174.5, len[4] = 87.5, len[5] = 116.5, len[6] = 116.5, len[7] = 107;//2kg
		len[0] = rod[0].l, len[1] = rod[2].l, len[2] = rod[4].l, len[3] = 140, len[4] = rod[7].l, len[5] = rod[1].l, len[6] = rod[3].l, len[7] = rod[6].l;//3kg
		rball = len[1] + len[2] + len[3];
		P_0[O[1]][0]=0,P_0[O[1]][1]=0,P_0[O[1]][2]=0;fromSn2S0(P_0[O[1]],1);
		forward_move();
	}
	bool checkcalj(float j0[6]);
	void fromSn2S0(float *P0,int n);
	// 求解除六个坐标系原点的其他点
	void getOtherPoints();
	// 点或向量在不同坐标系转换（p=true表示点，p=false表示向量）
	void fromS0toS1(float P0[3], float P[3], bool p);
	void fromS1toS2(float P0[3], float P[3], bool p);
	void fromS2toS3(float P0[3], float P[3], bool p);
	void fromS3toS4(float P0[3], float P[3], bool p);
	void fromS4toS5(float P0[3], float P[3], bool p);
	void fromS1toS0(float P0[3], float P[3], bool p);
	void fromS2toS1(float P0[3], float P[3], bool p);
	void fromS3toS2(float P0[3], float P[3], bool p);
	void fromS4toS3(float P0[3], float P[3], bool p);
	void fromS5toS4(float P0[3], float P[3], bool p);
	void fromS6toS5(float P0[3], float P[3], bool p);
	// // 逆运动解算器
	// bool Pos2J();//mfs 放到了public中
	// 根据角度计算点坐标
	void J2Point();

public:
	robotArm1();
	// 逆运动解算器
	bool Pos2J();
	// 根据角度计算点变换矩阵
	void J2MatrixT(float T[4][4]);
	// 正运动
	bool forward_move();
	// 逆运动
	bool backward_move();
	// 测试fromSi2Sj函数是否正确（是否抄错）
	void testj2p();
};
class robotArm2 : public pos_trans
{
private:
	float dst;
	void (robotArm2::*Si2Sj[6])(float *, float *, bool) = {&robotArm2::fromS1toS0, &robotArm2::fromS2toS1, &robotArm2::fromS3toS2, &robotArm2::fromS4toS3, &robotArm2::fromS5toS4, &robotArm2::fromS6toS5};

	void init_arm_structure()
	{
		rodnum = 7;
		rod[0].r = 80, rod[1].r = 80, rod[2].r = 50, rod[3].r = 50, rod[4].r = 35, rod[5].r = 35, rod[6].r = 35;
		rod[0].l = 160.5, rod[1].l = 190.5, rod[2].l = 714.5, rod[3].l = 147.5, rod[4].l = 636.33, rod[5].l = 125, rod[6].l = 125.5;
		init_rodindex();
	}
	void init_model_structure()
	{
		O[1] = 1, O[2] = 2, O[3] = 3, O[4] = 5, O[5] = 6, O[6] = 7;
		jr1[0]=-pi,jr1[1]=-pi,jr1[2]=-pi,jr1[3]=-pi,jr1[4]=-pi,jr1[5]=-pi;
		jr2[0]=pi,jr2[1]=pi,jr2[2]=pi,jr2[3]=pi,jr2[4]=pi,jr2[5]=pi;
		len[0] = 160.5, len[1] = 190.5, len[2] = 714.5, len[3] = 147.5, len[4] = 636.33, len[5] = 125, len[6] = 125.5;
		dst = len[1] - len[3] + len[5];
		forward_move();
	}
	bool checkcalj(float j0[6]);
	void fromSn2S0(float *P0,int n);
	void getOtherPoints();
	void fromS0toS1(float P0[3], float P[3], bool p);
	void fromS1toS2(float P0[3], float P[3], bool p);
	void fromS2toS3(float P0[3], float P[3], bool p);
	void fromS3toS4(float P0[3], float P[3], bool p);
	void fromS4toS5(float P0[3], float P[3], bool p);
	void fromS1toS0(float P0[3], float P[3], bool p);
	void fromS2toS1(float P0[3], float P[3], bool p);
	void fromS3toS2(float P0[3], float P[3], bool p);
	void fromS4toS3(float P0[3], float P[3], bool p);
	void fromS5toS4(float P0[3], float P[3], bool p);
	void fromS6toS5(float P0[3], float P[3], bool p);
	bool Pos2J();
	void J2Point();

public:
	robotArm2();
	void J2MatrixT(float T[4][4]);
	bool forward_move();
	bool backward_move();
	void testj2p();
};

#endif
