#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include<sstream>
#include<fstream>
#include<cmath>
#include<iostream>
#include <unistd.h>
#include <cstdlib>

#include "Ti5MOVE.h"
#include "Ti5BASIC.h"
#include "Ti5LOGIC.h"
#include "communication.h"
#include "mathfunc.h"
#include "tool.h"
//#include "clamping_jaw.h"

#include <csignal>
//#include <conio.h>

using namespace std;

float i=11.4373;//机械臂码垛：用坐标点的物体的高

void signalHandler(int signum)
{
    
    char aaa;
    cout << "Interrupt signal (" << signum << ") received.\n";
    aaa = scanKeyboard();
    brake();  
    cout << "stop!!" << endl;
    // switch (aaa)
    // {
    //     case 'b':
    //     {
    //         brake();  
    //         cout << "stop!!" << endl;
    //         break;
    //     }
    // }
    inspect_brake();

    // 清理并关闭
    // 终止程序  
    logout();
    exit(signum);

 
}


//实时补丁，用ubuntu2204 启动实时操作系统



int main()
{
    vector<string> productSerialNumbers = query_can();
    if (productSerialNumbers.empty()) {
        cout << "未找到任何 USB 设备。" << endl;
    } else {
        cout << "找到的 CAN 设备序列号：" << endl;
        for (const string& serialNumber : productSerialNumbers) {
            cout << serialNumber << endl;
        }
    }
    // string qqq=query_can();
    // cout<<"qqq="<<qqq<<endl;
    cout<<"qweqwdsaradasd"<<endl;
    signal(SIGINT, signalHandler);
    login();
    mechanical_arm_origin();
    show_value("pos:",TH.pos);
    cout<<"*************************"<<endl;
    current_angle();
    float qqq[6];
    current_pose(qqq);
    cout<<"*************************"<<endl;
    sleep(3);
    string ip=ip_address();
    
    //////////////////////////////////////机械臂码垛 1kg ：用角度////////////////////////////
    while (1)
    {
        float arr[6] = {-1.51795, 0.348368, -1.81652, 6.64592e-06, -1.0451, -3.79698e-05}; 
        joint_movement(arr);
        brake();
        sleep(0.5);
        // sleep(2);
        // sleep(0.5);

        float arr2[6] = {-1.51795, 0.746512, -1.8414, 0.0497746, -0.572304, 0.024846};
        joint_movement(arr2);
        brake();
        sleep(0.5);
        sleep(1);

        float arr3[6] = {0.472769, -0.423036, -1.96582, 0.0497746, -0.572304, -0.024846};
        joint_movement(arr3);
        brake();

        float arr4[6] = {0.472769, 0.970468, -1.39349, 0.0497746, -0.721608, -0.024846};
        joint_movement(arr4);
        brake();
        sleep(1);
    }
    //////////////////////////////////////机械臂码垛 1kg ：用角度////////////////////////////
    logout();
    return 0;
}
