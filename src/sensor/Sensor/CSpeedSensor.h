#pragma once
#include "CSensor.h"
#include <afxmt.inl>
class CSpeedSensor :
    public CSensor
{
private:
    int minSpeed=20;  // 最小速度
    int maxSpeed=40;  // 最大速度
    int randomSpeed=0;

public:
    // 构造函数，设置速度范围
    CSpeedSensor() {};
    // 实现初始化方法
    bool Initialize() override;

    // 实现启动方法
    bool Start() override;

    // 实现停止方法
    bool Stop() override;

    // 实现获取数据方法
    int GetData() override;

    double GetDate();

};

