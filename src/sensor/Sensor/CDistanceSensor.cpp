#include "stdafx.h"
#include "CDistanceSensor.h"
bool CDistanceSensor::Initialize()
{
    // 初始化速度传感器,
    maxDistance = 5;
    minDistance = 1;
    m_portID = 5;


    //Start();

    return TRUE;
}

// 实现启动方法
bool CDistanceSensor::Start()
{
    // 启动速度传感器的代码
    dlge->communications1.put_PortOpen(true);
    this->GetData();
    return TRUE;
}

// 实现停止方法
bool CDistanceSensor::Stop()
{
    // 停止速度传感器的代码
    dlge->communications1.put_PortOpen(FALSE);

    return TRUE;
}

// 实现获取数据方法
int CDistanceSensor::GetData()
{
    // 生成合理范围内的随机速度
    randomDistance = minDistance + (rand() / (double)RAND_MAX) * (maxDistance - minDistance);
    return randomDistance;
}

double CDistanceSensor::GetDate()
{
    // 生成合理范围内的随机速度
    randomDistance = minDistance + (rand() / (double)RAND_MAX) * (maxDistance - minDistance);
    return randomDistance;
}
