#pragma once
#include"02_TCPClientDlg.h"
#include"string"
#include<vector>

using namespace std;
class CSensor
{
public:
    CMy02_TCPClientDlg *dlge=NULL;
    CSensor *pCSensor = NULL;

    int m_portID;
    string m_Bund;
    string m_DataBit;
    string m_StopBit;
    string m_CheckBit;
    double m_iData;
    

;
    vector<string> m_Data;//储存传感器信息

    /*CSensor();
    ~CSensor();
    CSensor(int ,string );//初始化串口
    //virtual ~CSensor();*/
    virtual void modify(int portID, string Bund);//修改串口

    // 初始化传感器(串口号，波特率等）
    virtual bool Initialize() = 0;

    // 启动传感器
    virtual bool Start() = 0;

    // 停止传感器
    virtual bool Stop() = 0;

    // 获取传感器数据
    virtual int GetData()=0;

    virtual double GetDate()=0;

    virtual void DataCollect(double iData);
};

