#ifndef MOTORTYPEHELPER_H
#define MOTORTYPEHELPER_H

namespace MotorTypeHelper{

enum  MotorErrorStatus {
       NotError=0,
       SoftwareError,
       Overvoltage,
       Undervoltage,
       StartupError,
       SpeedFeedbackError,
       Overcurrent,
       EncoderCommunicationError,
       MotorTemperatureTooHigh,
       PCBTemperatureTooHigh
};

enum RequestType{
    MOTOR_RUN_MODE = 1,

    REG_I_Q,
    REG_SPEED,
    REG_CURRENT_POSITION,
    REG_STATUS,
    REG_BUS_VOLTAGE,
    REG_HEATS_TEMP,
    REG_TEMP,

    REG_SPEED_KP	,
    REG_SPEED_KI	,
    REG_SPEED_KD	,
    REG_POSITION_KP	,
    REG_POSITION_KI	,
    REG_POSITION_KD	,
    REG_MAX_APP_ACCEL,
    REG_MIN_APP_ACCEL,
    REG_MAX_APP_SPEED ,
    REG_MIN_APP_SPEED,
    REG_MAX_APP_POSITION,
    REG_MIN_APP_POSITION,
    REG_MAX_CURR_VALUE,
    REG_MIN_CURR_VALUE,
    REG_MAX_CURR_ABSOLUTE,
    REG_CURRENT_KP,
    REG_CURRENT_KI,
    REG_CURRENT_KD,
    REG_POSITION_OFFSET,
    REG_CAN_ID,
    REG_TARGET_CURRENT,
    REG_TARGET_SPEED,
    REG_TARGET_POSITION,
    REG_BAUD_RATE,
    REG_HARDWARE_VERSION,
    REG_MOTOR_MODEL
};
}

#endif // MOTORTYPEHELPER_H
