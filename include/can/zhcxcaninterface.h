#ifndef ZHCXCANINTERFACE_H
#define ZHCXCANINTERFACE_H

/*
 * Can分析仪调用接口
 * 操作流程
 * 1.打开设备——》2.初始化CAN——》3.启动CAN——》4.发送数据——》使用完成时，5.关闭设备——》0.复位设备，  复位后回到3——
*/
#if defined (_WIN32)
#include "ControlCAN.h"
#else //linux
#include "controlcan.h"
#endif

#include <atomic>
#include <iostream>
#include <functional>

struct CANBoardInfo{
    std::string  hw_Version;  //硬件版本号，例V1.00。
    std::string	fw_Version;  //固件版本号，例V1.00。
    std::string	dr_Version;  //驱动程序版本号，例V1.00。
    std::string	in_Version;  //接口库版本号，例V1.00。
    int	can_Num;     //表示有几路CAN通道。
    std::string  serial_Num; //此板卡的序列号。
    std::string	 hw_Type;  // 硬件类型，比如“USBCAN V1.00”（注意：包括字符串结束符’\0’）
};


struct CanDataStruct
{
    unsigned int canID;
    unsigned char data[8];
    unsigned int dlc;
};




class ZhcxCANInterface
{

public:
    ZhcxCANInterface();


    /******************************************************
    *Summary: 1.打开设备
    *Parameters:
    *     deviceType:  设备类型(USBCAN-2A或USBCAN-2C或CANalyst-II =4,  对应不同的产品型号详见：适配器设备类型定义。)
    *     deviceIndex : 设备索引(比如当只有一个USB-CAN适配器时，索引号为0，这时再插入一个USB-CAN适配器那么后面插入的这个设备索引号就是1，以此类推。)
    *     canIndex :   CAN索引(0:can1 1:can2)
    *     baundRate :  波特率（10kbps，20，40，50，80，83，100，125，200，250，400，500，666，800，1000）
    *Return :  返回值=1，表示操作成功；=0表示操作失败；=-1表示USB-CAN设备不存在或USB掉线。
    *******************************************************/
    int openDevice(UINT deviceType,UINT deviceIndex,UINT canIndex, UINT baundRate);


    /******************************************************
    *Summary: 2.初始化CAN
    *Parameters:
    *Return :  返回值=1，表示操作成功；=0表示操作失败；=-1表示USB-CAN设备不存在或USB掉线。
    *******************************************************/
    int initCAN();


    /******************************************************
    *Summary: 3.启动CAN
    *Parameters:
    *Return :  返回值=1，表示操作成功；=0表示操作失败；=-1表示USB-CAN设备不存在或USB掉线。
    *******************************************************/
    int startCAN();


    /******************************************************
    *Summary: 4.发送数据
    *Parameters:
	*canIndex:  CAN通道索引。第几路 CAN。即对应卡的CAN通道号，CAN1为0，CAN2为1。
	*id :		帧ID。32位变量，数据格式为靠右对齐。
	*remoteFlag :   是否是远程帧。=0时为为数据帧，=1时为远程帧（数据段空）。
	*externFlag     是否是扩展帧。=0时为标准帧（11位ID），=1时为扩展帧（29位ID）。
	*data			CAN帧的数据。由于CAN规定了最大是8个字节，所以这里预留了8个字节的空间，受DataLen约束。如DataLen定义为3，即Data[0]、Data[1]、Data[2]是有效的。
	*len            数据长度 DLC (<=8)，即CAN帧Data有几个字节。约束了后面Data[8]中的有效字节。
    *Return :  返回实际发送的帧数；=-1表示USB-CAN设备不存在或USB掉线。
    *******************************************************/
    bool sendData(UINT canIndex,UINT ID,BYTE remoteFlag,BYTE externFlag,const unsigned char *data,BYTE len);


    /******************************************************
    *Summary: 5.关闭设备
    *Parameters:
    *Return :
    *******************************************************/
    void closeDevice();


    /******************************************************
    *Summary: 0.复位设备，  复位后回到3
    *Parameters:
    *Return :  返回值=1，表示操作成功；=0表示操作失败；=-1表示USB-CAN设备不存在或USB掉线。
    *******************************************************/
    int resetCAN();


    /******************************************************
    *Summary: 获取Can分析仪信息（初始化成功后，能够获取到分析仪信息）
    *Parameters:
    *   CANBoardInfo:分析仪信息地址
    *Return : 返回值=1，表示操作成功；=0表示操作失败；=-1表示USB-CAN设备不存在或USB掉线。
    *******************************************************/
    int getBoardInfo(CANBoardInfo &info);


    int recieveFrame(CanDataStruct &receiveFrame);
    int recieveMultiFrame(CanDataStruct *canDataList);

private:
    inline std::string decIntToHexStr(long long num);

    UINT m_deviceType;
    UINT m_debicIndex;
    UINT m_CANIndex =0;
    UINT m_baundRate;
    UINT m_debicCom;
};


#endif // ZHCXCANINTERFACE_H
