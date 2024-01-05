#ifndef EXAMPLE_H
#define EXAMPLE_H
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include<sstream>
#include<fstream>
#include<cmath>

#include <unistd.h>


#include "Ti5MOVE.h"
#include "Ti5BASIC.h"
#include "Ti5LOGIC.h"
#include "communication.h"
#include "mathfunc.h"
#include "tool.h"
#include "clamping_jaw.h"

#include <csignal>


/*倒水demo*/
void pour_water();

/*直线运动demo*/
void linear_motion(); 

/*demo_1
    机械臂码垛动作：用角度
*/
void demo_1();

/*demo_2
    机械臂码垛 1kg ：用角度
*/
void demo_2();

/*demo_3
    3kg机械臂码垛：用坐标点，随着物体高度的增加最后位置改变
*/
void demo_3();

/*倒水修改版*/
void demo_4();

/*倒水修改版2.0*/
void demo_5();

/*倒水修改版3.0*/
void demo_6();
#endif

// #include <stdio.h>
// #include <unistd.h> // 包含 read 函数
// #include <string.h> // 包含 memcpy 函数

// int main() {
//     int fd = /* 你的文件描述符 */;

//     while (1) {
//         // 接收数据
//         char recv_buf[100];
//         int n = read(fd, recv_buf, sizeof(recv_buf));
//         if (n > 0) {
//             printf("recv_buf[0]=%02X\n", (unsigned char)recv_buf[0]);
//             if ((unsigned char)recv_buf[0] == 0xAA) {
//                 float result[25];  // 新的 float 数组
//                 int result_index = 0;

//                 for (int i = 1; i < n; i += 2) {
//                     if (i + 1 < n) { // 确保有足够的字节来读取
//                         // 假设数据是大端格式
//                         unsigned char highByte = recv_buf[i];
//                         unsigned char lowByte = recv_buf[i+1];
//                         // 将两个字节合并为一个 16 位的无符号整数
//                         unsigned short value = (highByte << 8) | lowByte;
                        
//                         // TODO: 这里需要根据实际的数据格式来转换
//                         // 如果 value 就是你想要的浮点数的话，可以直接赋值给 result
//                         // 但如果 value 需要进一步转换为浮点数，你需要实现这个转换逻辑
//                         result[result_index] = (float)value; // 这里只是一个示例

//                         result_index++;
//                     }
//                 }

//                 // 打印数据
//                 for (int i = 0; i < result_index; i++) {
//                     printf("i= %d, len=%ld, Received data: %.2f\n", i, sizeof(result), result[i]);
//                 }
//             }
//         }
//     }

//     return 0;
// }