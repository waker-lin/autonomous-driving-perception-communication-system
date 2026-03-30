#pragma once
#include "CSensor.h"
class CPerSensor :
    public CSensor
{
private:
    int minPerson = 0;  // 最小速度
    int maxPerson = 8;  // 最大速度
    int randomPerson = 0;

public:
    // 构造函数，设置速度范围
    CPerSensor() {};
    // 实现初始化方法
    bool Initialize() override;

    // 实现启动方法
    bool Start() override;

    // 实现停止方法
    bool Stop() override;

    // 实现获取数据方法
    int GetData() override;

    double GetDate()override;
};

