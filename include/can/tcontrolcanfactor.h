#ifndef TCONTROLCANFACTOR_H
#define TCONTROLCANFACTOR_H


#include <memory>
#include "tcontrolcan.h"

enum class CanType{Can=0, CanOpen=1,CanOpen4=2};//这是一个枚举类，定义了CanType类型，包括Can、CanOpen和CanOpen4三种取值。

class TControlCanFactor{ //这是一个类的声明，它包含了构造函数、成员函数和成员变量的声明。

public:
    explicit TControlCanFactor(CanType type,int canID=1); //这是TControlCanFactor类的构造函数声明，使用explicit关键字标记，可以防止隐式转换。它接受两个参数：type和canID。

public:
    bool open(); //这是TControlCanFactor类的两个成员函数声明，用于打开和关闭控制CAN的连接。
    bool close();

    void setCanID(int canID){ tControlCAN->setCanID(canID);}

    int readParameter(uint8_t requestType, int32_t &recieveData);
    int setParameter(uint8_t requestType, int32_t &recieveData);


    int getStatus();
    int getErrorStatus();
    std::vector<int>  getErrorInfos();
    int saveParameter();

    int clearFault();
    int stop();



private:
    std::shared_ptr<TControlCANBase>  tControlCAN;

};

#endif // TCONTROLCANFACTOR_H
