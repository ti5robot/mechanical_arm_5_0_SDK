#ifndef SINGLECANINTERFACE_H
#define SINGLECANINTERFACE_H
#include <memory>
#include <iostream>

class TControlCanFactor;

class SCanInterface
{
public:
    static SCanInterface* getInstance();
    bool open() const;
    bool close() const;
//parameterList：存放参数值 parameterType: 参数类型（见下表）  nodeCount:电机个数 （关节长度）nodeList：存放电机（关节）具体节点
    bool getParameter(uint32_t *parameterList, int parameterType,int nodeCount);
    bool getParameter(uint8_t *nodeList,uint32_t *parameterList, int parameterType,int nodeCount);
    bool setParameter(uint32_t *parameterList, int parameterType,int nodeCount);
    bool setParameter(uint8_t *nodeList,uint32_t *parameterList, int parameterType,int nodeCount);
   // bool clearFault();//清除电机错误
 // bool saveParameter();
private:
    SCanInterface();
    static SCanInterface* instance;
    std::shared_ptr<TControlCanFactor>  controlCAN;
};


#endif // SINGLECANINTERFACE_H
