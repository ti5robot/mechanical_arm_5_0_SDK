#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include "Ti5MOVE.h"
#include "Ti5BASIC.h"
#include "Ti5LOGIC.h"
#include "communication.h"
#include "mathfunc.h"
#include "tool.h"
#include "clamping_jaw.h"
#include "drag_drop.h"

#include <csignal>

using namespace std;

string filename;
// string device_485_name;
char device[] = "/dev/ttyUSB0";

void signalHandler(int signum)
{

    char aaa;
    cout << "Interrupt signal (" << signum << ") received.\n";

    brake();
    cout << "stop!!" << endl;
    inspect_brake();
    logout();
    exit(signum);
}

int main()
{
    vector<string> productSerialNumbers = query_can();
    if (productSerialNumbers.empty())
    {
        cout << "未找到任何 USB 设备，请插入设备后重试！" << endl;
        exit(0);
    }
    else
    {
        cout << "找到的 CAN 设备序列号：";
        for (const string &serialNumber : productSerialNumbers)
        {
            cout << serialNumber << endl;
        }
    }
    // string qqq=query_can();
    // cout<<"qqq="<<qqq<<endl;
    string ip = ip_address();
    cout << "ip=" << endl;

    signal(SIGINT, signalHandler);
    login();
    cout << "login success" << endl;
    mechanical_arm_origin();
    sleep(3);
    brake();

    int cnt = 5;
    while (cnt--)
    {
        TH.j[0] = 1.2;
        TH.j[1] = -0.68;
        TH.j[2] = 1.2;
        TH.j[3] = 1.48;
        TH.j[4] = 1.56;
        TH.j[5] = 1.32;
        move_to_joint();
        show_value("TH.j= ", TH.j);
        show_value("pos:", TH.pos);

        mechanical_arm_origin();
        show_value("TH.j= ", TH.j);
        show_value("pos:", TH.pos);

        TH.pos[0] = 150;
        TH.pos[1] = 250;
        TH.pos[2] = 223.455;
        TH.pos[3] = -2.02142;
        TH.pos[4] = -3.13438;
        TH.pos[5] = 0.0495672;
        move_to_pos();
        show_value("TH.j= ", TH.j);
        show_value("pos:", TH.pos);
        sleep(3);
        TH.pos[0] = 250;
        TH.pos[1] = 250;
        TH.pos[2] = 223.455;
        TH.pos[3] = -2.02142;
        TH.pos[4] = -3.13438;
        TH.pos[5] = 0.0495672;
        move_to_pos();
        show_value("TH.j= ", TH.j);
        show_value("pos:", TH.pos);
        sleep(3);
        TH.pos[0] = 350;
        TH.pos[1] = 250;
        TH.pos[2] = 223.455;
        TH.pos[3] = -2.02142;
        TH.pos[4] = -3.13438;
        TH.pos[5] = 0.0495672;
        move_to_pos();
        show_value("TH.j= ", TH.j);
        show_value("pos:", TH.pos);
        sleep(3);

        TH.pos[0] = 450;
        TH.pos[1] = 250;
        TH.pos[2] = 223.455;
        TH.pos[3] = -2.02142;
        TH.pos[4] = -3.13438;
        TH.pos[5] = 0.0495672;
        move_to_pos();
        show_value("TH.j= ", TH.j);
        show_value("pos:", TH.pos);

        sleep(10);

        mechanical_arm_origin();
        show_value("TH.j= ", TH.j);
        show_value("pos:", TH.pos);
    }

    logout();
    return 0;
}
