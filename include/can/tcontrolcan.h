#ifndef TCONTROLCAN_H
#define TCONTROLCAN_H

#include "tcontrolcanbase.h"


#define SET_MOTOR_ENABLE 1
#define	SET_MOTOR_DISABLE	2
#define	GET_MOTOR_RUN_MODE 3
#define	GET_REG_I_Q	4
#define	GET_REG_I_Q_REF	5
#define	GET_REG_SPEED	6
#define	GET_REG_SPEED_REF	7
#define	GET_REG_CURRENT_POSITION	8
#define	GET_REG_TARGET_POSITION	9
#define	GET_REG_STATUS	10
#define	SET_FAULT_ACK	11
#define	CMD_ENCODER_ALIGN	12
#define	CMD_RESTORE_PARAMETER	13
#define	CMD_STORE_PARAMETER	14
#define	CMD_RECOVERY_FACTORY_SETTING	15
#define	GET_REG_SPEED_KP	16
#define	GET_REG_SPEED_KI	17
#define	GET_REG_SPEED_KD	51
#define	GET_REG_POSITION_KP	18
#define	GET_REG_POSITION_KI	52
#define	GET_REG_POSITION_KD	19
#define	GET_REG_BUS_VOLTAGE	20
#define	GET_REG_HEATS_TEMP	50
#define	GET_REG_MAX_APP_ACCEL	22
#define	GET_REG_MIN_APP_ACCEL	23
#define	GET_REG_MAX_APP_SPEED	24
#define	GET_REG_MIN_APP_SPEED	25
#define	GET_REG_MAX_APP_POSITION	26
#define	GET_REG_MIN_APP_POSITION	27
#define	GET_REG_MAX_CURR_VALUE	53
#define	GET_REG_MIN_CURR_VALUE	54
#define	GET_REG_MAX_CURR_ABSOLUTE	55
#define	GET_POSITION_OFFSET	84
#define	GET_REG_CURRENT_KP	97
#define	GET_REG_CURRENT_KI	98
#define	GET_REG_CURRENT_KD	99
#define	GET_REG_MOTOR_MODEL 100
#define	GET_REG_HARDWARE_VERSION 101



#define	SET_REG_TARGET_CURRENT	28
#define	SET_REG_TARGET_SPEED	29
#define	SET_REG_TARGET_POSITION	30
#define	SET_REG_TARGET_POSITION_TRAPEZIUM	31
#define	SET_REG_MAX_APP_TORQUE	32
#define	SET_REG_MIN_APP_TORQUE	33
#define	SET_REG_MAX_APP_ACCEL	34
#define	SET_REG_MIN_APP_ACCEL	35
#define	SET_REG_MAX_APP_SPEED	36
#define	SET_REG_MIN_APP_SPEED	37
#define	SET_REG_MAX_APP_POSITION	38
#define	SET_REG_MIN_APP_POSITION	39
#define	SET_REG_SPEED_KP	41
#define	SET_REG_SPEED_KI	42
#define	SET_REG_POSITION_KP	43
#define	SET_REG_POSITION_KI	44
#define	SET_REG_POSITION_KD	45
#define	SET_REG_CAN_ID	46
#define SET_REG_I2T_PROTECTION	47
#define SET_OVER_TEMP_PROTECTION	48
#define	GET_REG_TEMP	49
#define	SET_BAUD_RATE	63
#define	SET_CAL_POSITION	80
#define	SET_MOTOR_EMERGENCY_STOP	82
#define	SET_MOTOR_POSITION_OFFSET	83


class TControlCAN : public TControlCANBase
{
public:
    TControlCAN();

    virtual OpenStateCan openCan(uint32_t deviceType=4,uint32_t deviceIndex=0,uint32_t canIndex=0, uint32_t baundRate=1000) override;
    
    virtual bool closeCan() override;

    virtual int get_motor_run_mode() override;
    virtual int get_reg_status() override;

    virtual int get_current_position() override;

    virtual int  get_reg_position_kp() override;
    virtual int  get_reg_position_kd() override;

    virtual int  get_reg_speed_kp() override;
    virtual int  get_reg_speed_ki() override;
    virtual int  get_reg_speed_kd() override;

    virtual int  get_reg_current_kp() override;
    virtual int  get_reg_current_ki() override;
    virtual int  get_reg_current_kd() override;

    virtual int  get_reg_max_app_accel()override;
    virtual int  get_reg_min_app_accel() override;

    virtual int  get_reg_max_curr_value() override;
    virtual int  get_reg_min_curr_value() override;
    virtual int  get_reg_max_curr_absolute() override;

    virtual int  get_reg_max_app_speed() override;
    virtual int  get_reg_min_app_speed() override;

    virtual int  get_position_offset() override;

    virtual int  get_reg_max_app_position() override;
    virtual int  get_reg_min_app_position() override;

    virtual int  get_reg_hardware_version() override;


    virtual int  get_status() override;
    virtual std::vector<int>  getErrorInfos() override;


    virtual int  set_reg_position_kp(int value)override;
    virtual int  set_reg_position_kd(int value)override;

    virtual int  set_reg_speed_kp(int value) override;
    virtual int  set_reg_speed_ki(int value) override;
    virtual int  set_reg_speed_kd(int value) override;

    virtual int  set_reg_current_kp(int value) override;
    virtual int  set_reg_current_ki(int value) override;
    virtual int  set_reg_current_kd(int value) override;

    virtual int  set_reg_max_app_accel(int value) override;
    virtual int  set_reg_min_app_accel(int value) override;

    virtual int  set_reg_max_curr_value(int value) override;
    virtual int  set_reg_min_curr_value(int value) override;


    virtual int  set_reg_max_app_speed(int value) override;
    virtual int  set_reg_min_app_speed(int value) override;

    virtual int  set_position_offset(int value) override;

    virtual int  set_reg_max_app_position(int value) override;
    virtual int  set_reg_min_app_position(int value) override;

    virtual int set_reg_baud_rate(int value) override;
    virtual int set_can_id( int id ) override;

    virtual int set_work_mode(int mode,int value) override;

    virtual int save_parameter( )override;

    virtual  int clearFault() override;

    virtual int stop() override;

    virtual int request_reg_i_q() override;
    virtual int request_reg_speed() override;
    virtual int request_reg_current_position() override;
    virtual int request_reg_status() override;
    virtual int request_reg_bus_voltage() override;
    virtual int request_reg_heats_temp() override;
    virtual int request_reg_temp() override;

private:
    int sendFrame(uint16_t canID,const uint8_t *frameBuffer,uint32_t size);
    int getParameter(uint8_t requestType);
    int setParameter(uint8_t requestType,int value);

    int send_request(uint8_t requestType);

    void motorVersionIntToString(int version);


};

#endif // TCONTROLCAN_H
