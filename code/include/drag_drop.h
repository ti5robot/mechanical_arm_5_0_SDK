#ifndef DRAG_DROP_H
#define DRAG_DROP_H

#include "tool.h"
#include "Ti5LOGIC.h"
#include "Ti5BASIC.h"
#include "can/SingleCaninterface.h"
#include "can/motortypehelper.h"
#include <math.h>
#include <stdio.h>




/*重力补偿拖拽示教功能，需要写进接口中*/
extern uint32_t pa[IDNUM];
extern float ang[IDNUM];
extern int status_flag;
// extern uint8_t qqq[6];
/*
   get_angle
*/
extern "C"
{ // 添加：extern C
   bool get_joint_angle();
   /*
      GravityCompensation
   */
   //1kg拖动示教
   float *GravityCompensation(float frr[6]);

   //2kg拖动示教
   float *GravityCompensation_2_kg(float frr[6]);

   // void stop_drag_teaching();
   
   int drag_teaching();
   /*拖动示教  
    参数：
        writemode：角度或者位姿标识,1为角度 ，0为坐标
        filename：文件名*/
   void dragg_teaching(int writemode,string filename);

   void dragg_teaching_2_kg(int writemode,string filename);
} // 添加：extern C
#endif