#ifndef SINGLECANINTERFACE_H
#define SINGLECANINTERFACE_H
#include <memory>
#include <iostream>
#include "can/tcontrolcanbase.h"
#include "can/tcontrolcanfactor.h"
class SCanInterface
{
public:
    static SCanInterface* getInstance();
    bool open() const;
    bool close() const;
    //    parameterList是参数列表,nodeList是关节具体节点.nodeCount是关节长度
    bool getParameter(uint32_t *parameterList, int parameterType,int nodeCount);
    bool getParameter(uint8_t *nodeList,uint32_t *parameterList, int parameterType,int nodeCount);
    //uint32_t a<-getParameter.parameterType;
    bool setParameter(uint32_t *parameterList, int parameterType,int nodeCount);
    bool setParameter(uint8_t *nodeList,uint32_t *parameterList, int parameterType,int nodeCount);
private:
    SCanInterface();
    static SCanInterface* instance;
    std::shared_ptr<TControlCanFactor>  controlCAN;
};


#endif // SINGLECANINTERFACE_H
