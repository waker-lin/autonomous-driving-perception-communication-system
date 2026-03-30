
// 02_TCPClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <Windows.h>
#include <WinSock2.h>
#include <winerror.h>
#include "02_TCPClient.h"
#include "02_TCPClientDlg.h"
#include "afxdialogex.h"
#include "ConnSocket.h"
#include "CSpeedSensor.h"
#include "CDistanceSensor.h"
#include "CPerSensor.h"
#include "string.h"
#include "DataSave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02_TCPClientDlg 对话框



CMy02_TCPClientDlg::CMy02_TCPClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY02_TCPCLIENT_DIALOG, pParent)
	, m_port(0)
	, m_sendBuf(_T(""))
	, m_connSocket(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy02_TCPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_IPADDRESS1, m_serverIp);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Control(pDX, IDC_BUTTON1, m_connBtn);
	DDX_Control(pDX, IDC_BUTTON2, m_disConnBtn);
	DDX_Text(pDX, IDC_EDIT3, m_sendBuf);
	DDX_Control(pDX, IDC_BUTTON3, m_sendBtn);
	DDX_Control(pDX, IDC_BUTTON4, m_clearBtn);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Control(pDX, IDC_COMBO1, chuankouhao);
	DDX_Control(pDX, IDC_COMBO2, botelv);
	DDX_Control(pDX, IDC_COMBO3, SensorType);
	DDX_Control(pDX, IDC_MSCOMM2, communications1);
	DDX_Control(pDX, IDC_CHECK1, xuanze);
	DDX_Control(pDX, IDC_MSCOMM1, communications2);
	DDX_Control(pDX, IDC_BUTTON5, SerialStart);
	DDX_Control(pDX, IDC_BUTTON8, SerialStop);
}

BEGIN_MESSAGE_MAP(CMy02_TCPClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy02_TCPClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy02_TCPClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy02_TCPClientDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy02_TCPClientDlg::OnBnClickedButton4)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMy02_TCPClientDlg::OnLvnItemchangedList1)
	//ON_EN_CHANGE(IDC_EDIT3, &CMy02_TCPClientDlg::OnEnChangeEdit3)
	//ON_CBN_SELCHANGE(IDC_COMBO2, &CMy02_TCPClientDlg::OnCbnSelchangeCombo2)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CMy02_TCPClientDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON5, &CMy02_TCPClientDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CMy02_TCPClientDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMy02_TCPClientDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_CHECK1, &CMy02_TCPClientDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON6, &CMy02_TCPClientDlg::OnBnClickedButton6)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMy02_TCPClientDlg 消息处理程序

BOOL CMy02_TCPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_ip.SetAddress(127, 0, 0, 1);
	m_port = 8888;
	UpdateData(FALSE);
	m_disConnBtn.EnableWindow(FALSE);
	m_sendBtn.EnableWindow(FALSE);

	chuankouhao.AddString(_T("毫米波雷达"));
	chuankouhao.AddString(_T("激光雷达"));
	chuankouhao.AddString(_T("行人检测仪"));

	/*chuankouhao.AddString(_T("COM1"));
	chuankouhao.AddString(_T("COM2"));
	chuankouhao.AddString(_T("COM3"));
	chuankouhao.AddString(_T("COM4"));
	chuankouhao.AddString(_T("COM5"));
	chuankouhao.AddString(_T("COM6"));*/

	botelv.AddString(_T("9600"));
	botelv.AddString(_T("38400"));
	botelv.AddString(_T("19200"));

	if (!communications1.get_CommPort())
	{
		SerialStart.EnableWindow(1);
		SerialStop.EnableWindow(0);
	}

	UpdateData(TRUE);
	BYTE a, b, c, d;
	m_ip.GetAddress(a, b, c, d);
	CString ip;
	ip.Format(_T("%d.%d.%d.%d"), a, b, c, d);
	BOOL ret = m_connSocket.Create();
	if (ret)
	{
		ret = m_connSocket.Connect(ip, m_port);
		if (ret)
		{
			m_connBtn.EnableWindow(FALSE);
			m_disConnBtn.EnableWindow(TRUE);
			m_sendBtn.EnableWindow(TRUE);
		}
		else
		{
			MessageBox(_T("连接服务器失败"));
			m_connSocket.Close();
		}
	}
	else
	{
		MessageBox(_T("创建套接字失败"));
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy02_TCPClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy02_TCPClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 连接TCP服务器
void CMy02_TCPClientDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	BYTE a, b, c, d;
	m_ip.GetAddress(a, b, c, d);
	CString ip;
	ip.Format(_T("%d.%d.%d.%d"), a, b, c, d);
	BOOL ret = m_connSocket.Create();
	if (ret)
	{
		ret = m_connSocket.Connect(ip, m_port);
		if (ret)
		{
			m_connBtn.EnableWindow(FALSE);
			m_disConnBtn.EnableWindow(TRUE);
			m_sendBtn.EnableWindow(TRUE);
		}
		else
		{
			MessageBox(_T("连接服务器失败"));
			m_connSocket.Close();
		}
	}
	else
	{
		MessageBox(_T("创建套接字失败"));
	}
}

// 断开连接
void CMy02_TCPClientDlg::OnBnClickedButton2()
{
	m_connBtn.EnableWindow(TRUE);
	m_disConnBtn.EnableWindow(FALSE);
	m_sendBtn.EnableWindow(FALSE);

	m_connSocket.Close();
}

// 向服务器发送消息
void CMy02_TCPClientDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char * send = T2A(m_sendBuf);
	m_connSocket.Send(send, strlen(send));
}

// 清空消息列表
void CMy02_TCPClientDlg::OnBnClickedButton4()
{
	m_listCtrl.DeleteAllItems();
}

void CMy02_TCPClientDlg::AddMsg(CString msg)
{
	m_listCtrl.InsertItem(0, msg);
}

void CMy02_TCPClientDlg::MyEnableBtn()
{
	m_connBtn.EnableWindow(TRUE);
	m_disConnBtn.EnableWindow(FALSE);
}

void CMy02_TCPClientDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	PortInit(communications1);
	KillTimer(1);
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	if (communications1.get_CommPort())
	{
		SerialStart.EnableWindow(0);
		SerialStop.EnableWindow(1);
		msg.Format(_T("[%d:%d:%d] 串口已开启"), t.wHour, t.wMinute, t.wSecond);
		AddMsg(msg);
	}
	//PortInit(communications2);

	/*int m_McsPortNum = 0; //定义串口号
	CString bote, jiaoyan, tingzhi, shuju; //波特率、校验位、停止位、数据位
	CString PortStr; //设置字符串
	//m_McsPortNum=PortSelect(chuankouhao.GetCurSel());
	m_McsPortNum=PortSelect(chuankouhao.GetCurSel());
	//AfxMessageBox(chuankouhao.GetCurSel());
	//SensorSelect(SensorType.GetCurSel());

	jiaoyan = _T("e");   //无校验位，协议只允许这样写

	//GetDlgItemText(IDC_COMBO3, bote);  //获取波特率
	//GetDlgItemText(IDC_COMBO5, tingzhi);   //获取停止位
	//GetDlgItemText(IDC_COMBO6, shuju);   //获取数据位

	PortStr = bote + _T(",") + jiaoyan;//+ _T(",") + shuju + _T(",") + tingzhi;//将字符串合成

	communications1.put_InBufferSize(2048);  //设置接收缓冲区
		communications1.put_OutBufferSize(2048);  //设置发送缓冲区
	communications1.put_Settings(PortStr); //设置初始化 波特率+校验位+数据位+停止位
	communications1.put_InputMode(1);  //以二进制方式读写

	if (communications1.get_PortOpen())  //返回当前是否有串口打开。true是有串口打开
	{
		communications1.put_PortOpen(FALSE);   //如果有串口打开，则设置串口关闭
	}
	communications1.put_CommPort(m_McsPortNum);  //上述操作保证没有串口打开后，设置需要打开的串口号，为串口打开做准备

	if (!communications1.get_PortOpen())   //如果没有串口打开（没有串口打开返回FALSE），则以下打开串口
	{
		communications1.put_PortOpen(TRUE);  //打开串口
	}
	else
	{
		MessageBox(_T("没有打开串口"), _T("信息提示！"), MB_ICONERROR | MB_OKCANCEL);
	}

	communications1.put_RThreshold(2);  //设置阈值，当接收缓冲区数量达到阈值时，产生onComm事件，启动接收
	communications1.put_SThreshold(2);  //设置阈值，当发送缓冲区数量达到阈值时，进行发送
	communications1.put_InputLen(0); //设置0含义为接收缓冲区中的数据全部读取
	communications1.get_Input();//读取缓冲区的数据*/
}

int CMy02_TCPClientDlg::PortSelect(int m_McsPortNum)//获取combox的选择，并返回端口号
{
	// TODO: 在此处添加实现代码.
	int Num = 0,lastm_McsPortNum;
	bool ref;
	switch (m_McsPortNum)  //获取外部端口号
	{
	case 0:
	{
		m_Sensor = new CSpeedSensor();
		ref = m_Sensor->Initialize();
		if (ref)
		{
			Num = m_Sensor->m_portID;
			//pCom->communications1.
		}
		else
			MessageBox(_T("初始化失败"));
		break;
	}
	case 1:
	{
		m_Sensor = new CDistanceSensor();
		ref = m_Sensor->Initialize();
		if (ref)
		{
			Num = m_Sensor->m_portID;
		}
		else
			MessageBox(_T("初始化失败"));
		break;
	}
	case 2:
	{
		m_Sensor = new CPerSensor();
		ref = m_Sensor->Initialize();
		if (ref)
		{
			Num = m_Sensor->m_portID;
		}
		else
			MessageBox(_T("初始化失败"));
		break;
	}
	default:
		MessageBox(_T("error"));
		break;
	}
	return Num;
}/**/

DataSave* CMy02_TCPClientDlg::SensorSelect(int SensorNum)
{
	DataSave* Data=new DataSave;
	SYSTEMTIME t;
	GetLocalTime(&t);
	
	// TODO: 在此处添加实现代码.
	switch (SensorNum)  //获取传感器
	{
	case 0:
	{
		m_Sensor = new CSpeedSensor();
		Data->Speed = m_Sensor->GetData();
		//m_Sensor->DataCollect(Snum);
		Data->msg.Format(_T("[%d:%d:%d] 速度:%d"), t.wHour, t.wMinute, t.wSecond, Data->Speed);
		Data->msg += "km/h    ";
		delete m_Sensor;
		m_Sensor = NULL;
		return Data;
		break; 
	}
	case 1:
	{
		m_Sensor = new CDistanceSensor();
		Data->Distance = m_Sensor->GetDate();
		Data->msg.Format(_T("[%d:%d:%d] 前车距离:%.2f"), t.wHour, t.wMinute, t.wSecond, Data->Distance);
		Data->msg += "m";
		delete m_Sensor;
		m_Sensor = NULL;
		return Data;
		break;
	}
	case 2:
	{
		m_Sensor = new CPerSensor();
		Data->Person = m_Sensor->GetData();
		Data->msg.Format(_T("[%d:%d:%d] 周围行人:%d"), t.wHour, t.wMinute, t.wSecond, Data->Person);
		Data->msg += "人    ";
		delete m_Sensor;
		m_Sensor = NULL;
		return Data;
		break;
	}
	default:
		return 0;
		break;
	}
}
void CMy02_TCPClientDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	//int Snum = m_Sensor->GetData();
	//CSpeedSensor Speed;
	//int Snum=this->m_Sensor->GetData();
	//int Snum= SensorSelect(SensorType.GetCurSel());
	//SensorTyper=SensorSelect(SensorType.GetCurSel());
	DataSave* data;
	CString msgs;
	data = SensorSelect(chuankouhao.GetCurSel());

	//int Snum = SensorSelect(SensorType.GetCurSel());

	UpdateData(TRUE);
	char buff1[256] = { 0 };
	char buff2[256] = { 0 };
	char buff3[256] = { 0 };
	if (_T("") !=data-> msg)   //如果发送信息不为空，则进行发送操作
	{
		if (communications1.get_PortOpen()&& chuankouhao.GetCurSel()==0)  //保证端口为打开状态
		{
			msgs.Format(_T("%d"), data->Speed);

			communications1.put_Output(COleVariant(msgs));//发送消息

			sprintf_s(buff1, "%s", msgs);

			m_connSocket.Send(buff1,strlen(buff1));

			AddMsg(data->msg);//日志显示
		}
		else if (communications1.get_PortOpen() && chuankouhao.GetCurSel() == 1)  //保证端口为打开状态
		{
			msgs.Format(_T("%.2lf"), data->Distance);

			communications1.put_Output(COleVariant(msgs));
			sprintf_s(buff1, "%s", msgs);

			m_connSocket.Send(buff1, strlen(buff1));

			AddMsg(data->msg);
		}
		else if (communications1.get_PortOpen() && chuankouhao.GetCurSel() == 2)  //保证端口为打开状态
		{
			msgs.Format(_T(" %d"), data->Person);

			communications1.put_Output(COleVariant(msgs));

			sprintf_s(buff1, "%s", msgs);

			m_connSocket.Send(buff1, strlen(buff1));

			AddMsg(data->msg);
		}
		else if (communications2.get_PortOpen())  //保证端口为打开状态
		{

			communications2.put_Output(COleVariant(data->msg));

			AddMsg(data->msg);
		}
		else  //如果端口为关闭状态，则提示串口关闭，需要打开
		{
			MessageBox(_T("串口没有打开，请重新打开串口！"), _T("信息提示！"), MB_ICONERROR | MB_OKCANCEL);
		}
	}
	else  //如果发送EDIT信息为空，则提示错误
	{
		MessageBox(_T("请选择传感器类型！"), _T("信息提示！"), MB_ICONINFORMATION | MB_OKCANCEL);
		return;
	}
	UpdateData(FALSE);/**/
}

BEGIN_EVENTSINK_MAP(CMy02_TCPClientDlg, CDialogEx)
	ON_EVENT(CMy02_TCPClientDlg, IDC_MSCOMM2, 1, CMy02_TCPClientDlg::OnOncommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()

void CMy02_TCPClientDlg::OnOncommMscomm1()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString message;
	int Begin=10;
	int Stop=11;
	int connect = 12;
	int pause = 13;
	int conti = 14;
	int discon = 15;
	int all = 16;
	int none=17;

	VARIANT        m_Variant_Rec; //接收类型定义
	COleSafeArray  m_SafeArray_Rec;  //用于处理任意类型和维数数组的类
	LONG           m_DataLenth, nCount;  //定义接收的长度和计数用
	const int      m_RecByteLenth = 2048;
	BYTE           m_RecDataByte[m_RecByteLenth];  //定义接收缓冲区
	CString        m_TemDataStr;  //接收字符串，用于转换后显示
	if (communications1.get_CommEvent() == 2)   //串口事件值为2，表示接收缓冲区字符
	{
		m_Variant_Rec = communications1.get_Input();  //获取缓冲区内容
		m_SafeArray_Rec = m_Variant_Rec;   //把缓冲区内容放到SafeArray数据结构中

		m_DataLenth = m_SafeArray_Rec.GetOneDimSize(); //获取一维数据的长度
		for (nCount = 0; nCount < m_DataLenth; nCount++)
			m_SafeArray_Rec.GetElement(&nCount, m_RecDataByte + nCount); //检索SafeArray中的内容，用不同ncout位置进行指针的偏移量，取出对应位置内容
		//CSpeedShow.SetWindowText(_T(""));

		for (nCount = 0; nCount < m_DataLenth; nCount++)
		{
			BYTE m_Buff = *(char*)(m_RecDataByte + nCount);  //从数组开头进行ncount偏移量，提取对应位置的内容
			m_TemDataStr.Format(_T("%C"), m_Buff); //把相关BYTE内容转化为char
			message += m_TemDataStr;  //把char加入到所显示的字符串中
		}

		if(_ttoi(message) == connect)//判断是否链接
		{
			message.Format(_T("[%d:%d:%d] 传感器连接成功"), t.wHour, t.wMinute, t.wSecond);
			AddMsg(message);

		}
		if(_ttoi(message) == pause)//判断是否停止
		{
			message.Format(_T("[%d:%d:%d] 传感器暂停成功"), t.wHour, t.wMinute, t.wSecond);
			AddMsg(message);
			KillTimer(0);

		}
		if(_ttoi(message) == conti)//判断是否继续
		{
			message.Format(_T("[%d:%d:%d] 传感器继续成功"), t.wHour, t.wMinute, t.wSecond);
			AddMsg(message);
			SetTimer(0, 1000, NULL);
		}
		if(_ttoi(message) == discon)//判断是否继续
		{
			message.Format(_T("[%d:%d:%d] 传感器连接断开"), t.wHour, t.wMinute, t.wSecond);
			AddMsg(message);
		}
		if (_ttoi(message) == Begin)//判断是否持续发送
		{
			message.Format(_T("[%d:%d:%d] 定时检测开启"),t.wHour, t.wMinute, t.wSecond);
			AddMsg(message);
			SetTimer(0, 1000, NULL);
			//SetTimer(1, 1000, NULL);
			//SetTimer(2, 1000, NULL);
		}
		if (_ttoi(message) == Stop)//判断是否停止持续发送
		{
			message.Format(_T("[%d:%d:%d] 定时检测关闭"), t.wHour, t.wMinute, t.wSecond );
			AddMsg(message);
			KillTimer(0);
			//KillTimer(1);
			//KillTimer(2);
		}
		if (_ttoi(message) == all)//判断是否停止持续发送
		{
			message.Format(_T("[%d:%d:%d] 全部传感器开启"), t.wHour, t.wMinute, t.wSecond );
			AddMsg(message);
			//KillTimer(1);
			//KillTimer(2);
		}
		if (_ttoi(message) == none)//判断是否停止持续发送
		{
			message.Format(_T("[%d:%d:%d] 全部传感器关闭"), t.wHour, t.wMinute, t.wSecond );
			AddMsg(message);
			//KillTimer(1);
			//KillTimer(2);
		}
		//AfxMessageBox(SpeedShow);
		//SpeedShow += _T("\r\n");

		UpdateData(FALSE);
	}

	communications1.put_InBufferCount(0);  //取出数据后，进行数据的清零
	communications1.put_OutBufferCount(0);
}

void CMy02_TCPClientDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_Sensor = new CSpeedSensor;
	//m_Sensor->Stop();
	KillTimer(0);
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	communications1.put_PortOpen(FALSE);
	if (communications1.get_CommPort())
	{
		SerialStart.EnableWindow(1);
		SerialStop.EnableWindow(0);
		msg.Format(_T("[%d:%d:%d] 串口已关闭"), t.wHour, t.wMinute, t.wSecond);
		AddMsg(msg);
	}
}


void CMy02_TCPClientDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (xuanze.GetCheck() == TRUE)   //如果进行了选择，则把自动发送变量赋值
	{

		if (communications1.get_PortOpen() == TRUE)  //端口打开状态
		{
			xuanze.EnableWindow(TRUE);
			//SetTimer(0, 1000, NULL); //开启定时器，1000毫秒一次
			//SetTimer(1, 3000, NULL);
			//SetTimer(2, 3000, NULL);
			//AfxMessageBox(_T("error1"));
		}
	}
	/*else
	{
		if (communications1.get_PortOpen() == false)
		{
			xuanze.EnableWindow(FALSE);
		}
	}*/
}

void CMy02_TCPClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此处添加实现代码.
	CString m_AutoSendText;
	DataSave* Data = new DataSave;
	SYSTEMTIME t;
	string sen;
	GetLocalTime(&t);

	char buff1[100] = { 0 };
	//AfxMessageBox(_T("1"));

	if (communications1.get_PortOpen() == true)
	{
		switch (chuankouhao.GetCurSel())
		//switch (nIDEvent)
		{
		case 0:
			//if (xuanze.GetCheck())
			{
				m_Sensor = new CSpeedSensor();
				Data->Speed = m_Sensor->GetData();
				Data->msg.Format(_T("[%d:%d:%d] 速度:%d"), t.wHour, t.wMinute, t.wSecond, Data->Speed);
				Data->msg += "km/h    ";
				m_AutoSendText.Format(_T(" %d"), Data->Speed);
				communications1.put_Output(COleVariant(m_AutoSendText));
				sprintf_s(buff1, "%d", Data->Speed);
				m_connSocket.Send(buff1, strlen(buff1));
				AddMsg(Data->msg);
			}
			break;
		case 1:
			//if (xuanze.GetCheck())
			{
				m_Sensor = new CDistanceSensor();
				Data->Distance = m_Sensor->GetDate();
				Data->msg.Format(_T("[%d:%d:%d] 前车距离:%.2lf"), t.wHour, t.wMinute, t.wSecond, Data->Distance);
				Data->msg += "m";
				m_AutoSendText.Format(_T(" %.2lf"), Data->Distance);
				communications1.put_Output(COleVariant(m_AutoSendText));
				sprintf_s(buff1, "%.2lf", Data->Distance);
				m_connSocket.Send(buff1, strlen(buff1));
				AddMsg(Data->msg);
			}
			break;
		case 2:
			//if (xuanze.GetCheck())
			{
				m_Sensor = new CDistanceSensor();
				Data->Person = m_Sensor->GetData();
				Data->msg.Format(_T("[%d:%d:%d] 周围行人:%d"), t.wHour, t.wMinute, t.wSecond, Data->Person);
				Data->msg += "人    ";
				m_AutoSendText.Format(_T(" %d"), Data->Person);
				communications1.put_Output(COleVariant(m_AutoSendText));

				//strncpy_s(szBuf, sizeof(szBuf), it->dData.c_str(), sizeof(it->dData) - 1);
				sprintf_s(buff1,"%d", Data->Person);
				m_connSocket.Send(buff1, strlen(buff1));
				AddMsg(Data->msg);
			}
			break;
		default:
			break;
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMy02_TCPClientDlg::PortInit(CMSCOMM2& communication)
{
	// TODO: 在此处添加实现代码.
	int m_McsPortNum = 0; //定义串口号
	CString bote, jiaoyan, tingzhi, shuju; //波特率、校验位、停止位、数据位
	CString PortStr; //设置字符串
	//m_McsPortNum=PortSelect(chuankouhao.GetCurSel());
	m_McsPortNum = PortSelect(chuankouhao.GetCurSel());
	communication.put_InBufferSize(2048);  //设置接收缓冲区
	communication.put_OutBufferSize(2048);  //设置发送缓冲区
	communication.put_Settings(PortStr); //设置初始化 波特率+校验位+数据位+停止位
	communication.put_InputMode(1);  //以二进制方式读写

	if (communication.get_PortOpen())  //返回当前是否有串口打开。true是有串口打开
	{
		communication.put_PortOpen(FALSE);   //如果有串口打开，则设置串口关闭
	}
	communication.put_CommPort(m_McsPortNum);  //上述操作保证没有串口打开后，设置需要打开的串口号，为串口打开做准备

	if (!communication.get_PortOpen())   //如果没有串口打开（没有串口打开返回FALSE），则以下打开串口
	{
		communication.put_PortOpen(TRUE);  //打开串口
	}
	else
	{
		MessageBox(_T("没有打开串口"), _T("信息提示！"), MB_ICONERROR | MB_OKCANCEL);
	}

	communication.put_RThreshold(2);  //设置阈值，当接收缓冲区数量达到阈值时，产生onComm事件，启动接收
	communication.put_SThreshold(2);  //设置阈值，当发送缓冲区数量达到阈值时，进行发送
	communication.put_InputLen(0); //设置0含义为接收缓冲区中的数据全部读取
	communication.get_Input();//读取缓冲区的数据*/

}void CMy02_TCPClientDlg::PortInit(CMSCOMM1& communication)
{
	// TODO: 在此处添加实现代码.
	int m_McsPortNum = 0; //定义串口号
	CString bote, jiaoyan, tingzhi, shuju; //波特率、校验位、停止位、数据位
	CString PortStr; //设置字符串
	//m_McsPortNum=PortSelect(chuankouhao.GetCurSel());
	m_McsPortNum = PortSelect(chuankouhao.GetCurSel());
	communication.put_InBufferSize(2048);  //设置接收缓冲区
	communication.put_OutBufferSize(2048);  //设置发送缓冲区
	communication.put_Settings(PortStr); //设置初始化 波特率+校验位+数据位+停止位
	communication.put_InputMode(1);  //以二进制方式读写

	if (communication.get_PortOpen())  //返回当前是否有串口打开。true是有串口打开
	{
		communication.put_PortOpen(FALSE);   //如果有串口打开，则设置串口关闭
	}
	communication.put_CommPort(m_McsPortNum);  //上述操作保证没有串口打开后，设置需要打开的串口号，为串口打开做准备

	if (!communication.get_PortOpen())   //如果没有串口打开（没有串口打开返回FALSE），则以下打开串口
	{
		communication.put_PortOpen(TRUE);  //打开串口
	}
	else
	{
		MessageBox(_T("没有打开串口"), _T("信息提示！"), MB_ICONERROR | MB_OKCANCEL);
	}

	communication.put_RThreshold(2);  //设置阈值，当接收缓冲区数量达到阈值时，产生onComm事件，启动接收
	communication.put_SThreshold(2);  //设置阈值，当发送缓冲区数量达到阈值时，进行发送
	communication.put_InputLen(0); //设置0含义为接收缓冲区中的数据全部读取
	communication.get_Input();//读取缓冲区的数据*/
}


void CMy02_TCPClientDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listCtrl.DeleteAllItems();

}
