#ifndef TCONTROLCANBASE_H
#define TCONTROLCANBASE_H

#include <memory>
#include "zhcxcaninterface.h"
#include <vector>
#include <thread>

enum   CanState{ SendParameterError=-2,SendFailure=-1,SendSuccess=1,RecieveFailure=-4,RecieveDataFailure =-3, RecieveSuccess=2  };

enum class OpenStateCan{OpenFault=-4, InitFault=-3,StartFault=-2,OpenSuccess=1};


class TControlCANBase
{
public:
    explicit TControlCANBase();
    ~TControlCANBase();


public:
    virtual OpenStateCan openCan(uint32_t deviceType=4,uint32_t deviceIndex=0,uint32_t canIndex=0, uint32_t baundRate=1000)=0 ;

    virtual bool closeCan() =0;

    void setCanID(int canID){ this->canID = canID;}


    virtual int get_motor_run_mode() = 0;  //获取运行模式
    virtual int get_reg_status() = 0;      //获取状态

    virtual int get_current_position() = 0;  //获取当前位置

    virtual int  get_reg_position_kp() =0; //位置环比例
    virtual int  get_reg_position_kd() =0; //位置环微分

    virtual int  get_reg_speed_kp() =0;    //速度环比例
    virtual int  get_reg_speed_ki() =0;    //速度环积分
    virtual int  get_reg_speed_kd() =0;    //速度环微分

    virtual int  get_reg_current_kp() =0; //电流环比例
    virtual int  get_reg_current_ki() =0; //电流环积分
    virtual int  get_reg_current_kd() =0; //电流环微分

    virtual int  get_reg_max_app_accel()=0; //电机最大正向加速度
    virtual int  get_reg_min_app_accel() =0; //电机最小负向加速度

    virtual int  get_reg_max_curr_value() =0; //最大正电流
    virtual int  get_reg_min_curr_value() =0; //最小负电流
    virtual int  get_reg_max_curr_absolute() =0; //电机最大电流绝对值

    virtual int  get_reg_max_app_speed() =0; //最大正向允许速度
    virtual int  get_reg_min_app_speed() =0; //最小负向允许速度

    virtual int  get_position_offset() =0;   //位置偏移

    virtual int  get_reg_max_app_position() =0; //最大正向位置
    virtual int  get_reg_min_app_position() =0; //最大负向位置

    virtual int  get_status() =0; //获取电机状态

    virtual int  get_reg_hardware_version() =0; //获取电机硬件版本号

    virtual std::vector<int>  getErrorInfos() =0;

    virtual int  set_reg_position_kp(int value) =0; //位置环比例
    virtual int  set_reg_position_kd(int value) =0; //位置环微分

    virtual int  set_reg_speed_kp(int value) =0;    //速度环比例
    virtual int  set_reg_speed_ki(int value) =0;    //速度环积分
    virtual int  set_reg_speed_kd(int value) =0;    //速度环微分

    virtual int  set_reg_current_kp(int value) =0; //电流环比例
    virtual int  set_reg_current_ki(int value) =0; //电流环积分
    virtual int  set_reg_current_kd(int value) =0; //电流环微分

    virtual int  set_reg_max_app_accel(int value)=0; //电机最大正向加速度
    virtual int  set_reg_min_app_accel(int value) =0; //电机最小负向加速度

    virtual int  set_reg_max_curr_value(int value) =0; //最大正电流
    virtual int  set_reg_min_curr_value(int value) =0; //最小负电流


    virtual int  set_reg_max_app_speed(int value) =0; //最大正向允许速度
    virtual int  set_reg_min_app_speed(int value) =0; //最小负向允许速度

    virtual int  set_position_offset(int value) =0;   //位置偏移

    virtual int  set_reg_max_app_position(int value) =0; //最大正向位置
    virtual int  set_reg_min_app_position(int value) =0; //最大负向位置

    virtual int set_reg_baud_rate(int value)=0; //设置波特率
    virtual int set_can_id( int id )=0;//设置CanID

    virtual int set_work_mode(int mode,int value) =0; //设置工作模式

    virtual int save_parameter( )=0;//保存参数

    virtual int clearFault() =0; //清除错误

    virtual int stop() = 0; //停止启动

    virtual int request_reg_i_q() =0; //请求读取电流
    virtual int request_reg_speed() =0; //请求读取电流
    virtual int request_reg_current_position() =0; //请求读取电流
    virtual int request_reg_status() =0; //请求读取电流
    virtual int request_reg_bus_voltage() =0; //请求读取电流
    virtual int request_reg_heats_temp()=0;
    virtual int request_reg_temp() =0; //请求读取温度


    int getRegisterData()const {return registerData;}
    std::string getMotorModel()const {return motorModel;}

protected:
    std::shared_ptr<ZhcxCANInterface>  controlCan;
    uint16_t canID = 0;
    uint16_t canIndex = 0;
    int registerData = 0;
    std::string motorModel;


};

#endif // CONTROLCANBASE_H
