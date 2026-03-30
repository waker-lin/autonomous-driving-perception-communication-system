#include "stdafx.h"
#include "CSpeedSensor.h"
#include "02_TCPClientDlg.h"
#include <cstdlib> // 包含随机数生成所需的头文件

// 构造函数，设置速度范围
//CSpeedSensor::CSpeedSensor(double min, double max) : minSpeed(min), maxSpeed(max) {}
//CSpeedSensor::CSpeedSensor(){}
// 实现初始化方法
bool CSpeedSensor::Initialize()
{
    // 初始化速度传感器,
    maxSpeed = 40;
    minSpeed = 20;
    m_portID = 3;

    return TRUE;
}

// 实现启动方法
bool CSpeedSensor::Start()
{
    // 启动速度传感器的代码
    dlge->communications1.put_PortOpen(true);
    this->GetData();
    return TRUE;
}

// 实现停止方法
bool CSpeedSensor::Stop()
{
    // 停止速度传感器的代码
    dlge->communications1.put_PortOpen(FALSE);

    return TRUE;
}

// 实现获取数据方法
int CSpeedSensor::GetData()
{
    // 生成合理范围内的随机速度
    randomSpeed = minSpeed + (rand() / (double)RAND_MAX) * (maxSpeed - minSpeed);
    return randomSpeed;
}
double CSpeedSensor::GetDate()
{
    return 0;
}

