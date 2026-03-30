#pragma once
#include "CSensor.h"
class CDistanceSensor :
    public CSensor
{
private:
    int minDistance = 1;  // 最小车距
    int maxDistance = 10;  // 最大车距
    double randomDistance = 0;

public:
    // 构造函数，设置速度范围
    CDistanceSensor() {}; 
        // 实现初始化方法
    bool Initialize() override;

    // 实现启动方法
    bool Start() override;

    // 实现停止方法
    bool Stop() override;

    // 实现获取数据方法
    int GetData()override;

    double GetDate();

};

