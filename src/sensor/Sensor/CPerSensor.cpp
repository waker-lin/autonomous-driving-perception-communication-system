#include "stdafx.h"
#include "CPerSensor.h"
bool CPerSensor::Initialize()
{
    // 初始化速度传感器,
    maxPerson = 8;
    minPerson = 0;
    m_portID = 7;

    return TRUE;
}

// 实现启动方法
bool CPerSensor::Start()
{
    // 启动速度传感器的代码
    dlge->communications1.put_PortOpen(true);
    this->GetData();
    return TRUE;
}

// 实现停止方法
bool CPerSensor::Stop()
{
    // 停止速度传感器的代码
    dlge->communications1.put_PortOpen(FALSE);

    return TRUE;
}

// 实现获取数据方法
int CPerSensor::GetData()
{
    // 生成合理范围内的随机速度
    randomPerson = minPerson + (rand() / (double)RAND_MAX) * (maxPerson - minPerson);
    return randomPerson;
}

double CPerSensor::GetDate()
{
    return 0;
}