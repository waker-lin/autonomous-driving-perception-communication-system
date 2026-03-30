// CarCommu.cpp: 实现文件
//

#include"stdafx.h"
#include "pch.h"
#include "CarCommu.h"
#include "afxdialogex.h"
#include "resource.h"
#include "02_TCPClientDlg.h"
#include <fstream>
#include <sstream>
#include "ConnSocket.h"
#include "afxwin.h"


// CarCommu 对话框

IMPLEMENT_DYNAMIC(CarCommu, CDialogEx)

CarCommu::CarCommu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_port(_T(""))
	, m_rcv(_T(""))
	, m_send(_T(""))
{

}

CarCommu::~CarCommu()
{
}

void CarCommu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDX_Text(pDX, IDC_EDIT3, m_rcv);
	DDX_Text(pDX, IDC_EDIT2, m_send);
	DDX_Control(pDX, IDC_EDIT1, m_CsendBuf);
	DDX_Control(pDX, IDC_EDIT2, m_sender);
	DDX_Control(pDX, IDC_EDIT3, m_rcver);
}


BEGIN_MESSAGE_MAP(CarCommu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CarCommu::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CarCommu::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CarCommu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CarCommu::OnBnClickedButton5)
	ON_BN_CLICKED(IDCANCEL, &CarCommu::OnBnClickedCancel)
	
END_MESSAGE_MAP()


// CarCommu 消息处理程序


BOOL CarCommu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	CString col[4] = { _T("时间"),_T("IP"),_T("端口号"),_T("状态") };
	RECT r;	//rect对象用来存储一个矩形框的左上角坐标、宽度和高度。
	m_listCtrl.GetClientRect(&r);	//显示矩形框调用函数要加取地址符号
	for (int i = 0; i < 4; i++)
	{
		m_listCtrl.InsertColumn(i, col[i], LVCFMT_CENTER, (r.right - r.left) / 4);
	}


	m_listCtrl.SetBkColor(RGB(199, 237, 233));	//设置列表框背景颜色
	m_listCtrl.SetTextColor(RGB(18, 53, 85));	//字体颜色
	m_listCtrl.SetTextBkColor(RGB(175, 215, 237));//文字背景色

	m_port1 = 8888;
	//m_ip.SetAddress(127, 0, 0, 1);
	//UpdateData(FALSE);
	//AfxSocketInit();
	/**///ThreadStart();
	// 创建一个套接字对象


	// 尝试连接到服务器
	if (clientSocket.Create() && clientSocket.Connect(_T("127.0.0.1"), 8888))
	{
		// 连接成功，可以发送和接收数据了
		// 在这里编写发送和接收数据的代码
		AfxMessageBox(_T("ok"));

			char recvBuf[512] = { 0 };
			int recvLen = this->clientSocket.Receive(recvBuf, sizeof(recvBuf));
			if (recvLen == SOCKET_ERROR)
			{
				int error = this->clientSocket.GetLastError();
				// 处理错误，可以打印错误信息
				TRACE(_T("Receive failed with error %d\n"), error);
			}
			else if (recvLen > 0)
			{
				AfxMessageBox(_T("接收"));
			}
		//TransferSocketToAnotherThread(clientSocket);
		//ThreadStart();
	}
	else
	{
		// 连接失败，处理错误
		MessageBox(_T("连接服务器失败"));
		clientSocket.Close();
		// 可以通过调用GetLastError()获取错误码，然后根据需要进行处理
	}
	;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CarCommu::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char* send = T2A(m_port);
	clientSocket.Send(send,strlen(send));
	//m_CsendBuf.SetWindowTextW(_T(""));
}


void CarCommu::listInit(char* port)
{
	// TODO: 在此处添加实现代码.
	for (auto it = m_clientList.begin(); it != m_clientList.end(); ++it) {
		CConnSocket* pClientSocket = *it;

		// Assuming CConnSocket has member functions GetPort() and GetIPAddress()
		int port = pClientSocket->m_port;
		CString ipAddress = pClientSocket->m_ip; // Assuming GetIPAddress() returns a std::string
		CString porte;
		porte.Format(_T("%d"), port);
		// Insert the information into the list control
		int nIndex = m_listCtrl.GetItemCount();
		m_listCtrl.SetItemText(nIndex, 0, ipAddress); // Assuming column 0 is for IP address
		m_listCtrl.SetItemText(nIndex, 1, porte);
	}
}


void CarCommu::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	   // 打开 CSV 文件
	m_listCtrl.DeleteAllItems();
	CStringA filePath = "D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\交流端口号.csv";
	std::ifstream file(filePath); // 使用窄字符版本的文件输入流
	if (!file.is_open())
	{
		AfxMessageBox(_T("Failed to open file!"));
		return;
	}

	// 逐行读取 CSV 文件内容，并将其添加到 List Control 中
	bool isFirstLine = true; // 添加一个标志以确定当前是否是第一行
	std::string line;
	while (std::getline(file, line))
	{
		// 如果是第一行，则跳过
		if (isFirstLine)
		{
			isFirstLine = false; // Set the flag to false after processing the first line
			continue; // Skip processing the first line
		}
		// 使用std::stringstream按照逗号分割每一行的数据
		std::stringstream ss(line);
		std::string item;
		int columnIndex = 0;

		// 插入新的一行
		int rowIndex = m_listCtrl.GetItemCount();
		m_listCtrl.InsertItem(rowIndex, _T(""));

		// 逐个读取每个字段，并插入到对应的列中
		while (std::getline(ss, item, ','))
		{
			// 将std::string转换为CString
			CString str(item.c_str());

			// 插入到对应的列
			m_listCtrl.SetItemText(rowIndex, columnIndex, str);

			columnIndex++;
		}
	}
}

void CarCommu::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char* send = T2A(m_send);
	int flag = clientSocket.Send(send, strlen(send));
	if (!flag)
	{
		AfxMessageBox(_T("发送失败"));
	}
	if (!flag)
	{
		AfxMessageBox(_T("发送失败"));
	}
	m_sender.SetWindowTextW(_T(""));
}

CConnSocket& CarCommu::quote(CConnSocket& Con)
{
	// TODO: 在此处添加实现代码.
	
	return Con;
}

void CarCommu::OnBnClickedButton5()
{
	
	
}

DWORD WINAPI process(LPVOID pParam)
{
	
	/*CString ip = _T("127.0.0.1");

	if (p_Mainprocess == NULL)
	{
		//TerminateThread(p_Mainprocess->handle_Thread, 0);
		return 0;
	}

	// Assuming m_port1 is correctly set to 8888
	UINT port = 8888;

	BOOL ret = p_Mainprocess->m_connSocket1.Create();
	if (ret)
	{
		ret = p_Mainprocess->m_connSocket1.Connect(ip, port);

		if (ret)
		{
			AfxMessageBox(_T("连接成功"));
			// Connection successful
			// m_connBtn.EnableWindow(FALSE);
			// m_disConnBtn.EnableWindow(TRUE);
			// m_sendBtn.EnableWindow(TRUE);
		}
		else
		{
			AfxMessageBox(_T("Failed to connect to the server. Please check the server availability and port."));
			p_Mainprocess->m_connSocket1.Close();
		}
	}
	else
	{
		AfxMessageBox(_T("Failed to create a socket."));
	}*/
	CarCommu* p_Mainprocess =(CarCommu*) pParam;
	/*AfxSocketInit();
	if (p_Mainprocess->clientSocket.Create() && p_Mainprocess->clientSocket.Connect(_T("127.0.0.1"), 8811))
	{
		// 连接成功，可以发送和接收数据了
		// 在这里编写发送和接收数据的代码
		AfxMessageBox(_T("okl"));
		//p_Mainprocess->ThreadStart();
	}
	else
	{
		// 连接失败，处理错误
		p_Mainprocess->MessageBox(_T("连接服务器失败"));
		p_Mainprocess->clientSocket.Close();
		// 可以通过调用GetLastError()获取错误码，然后根据需要进行处理
	}*/
	//CAsyncSocket* pNewSocket = new CAsyncSocket;
	//pNewSocket->Attach(p_Mainprocess->hSocket); // 关联套接字
	while (true)
	{
		bool flag = true;
		if (flag)
		{
			//AfxMONreessageBox(_T("while"));
		}
		flag = false;
		char recvBuf[512] = { 0 };
		int recvLen = p_Mainprocess->clientSocket.Receive(recvBuf, sizeof(recvBuf));
		CString msg;
		SYSTEMTIME t;
		GetLocalTime(&t);
		p_Mainprocess->m_rcv = recvBuf;

		if (recvLen > 0)
		{
			// 成功接收到数据
			CString receivedData(recvBuf, recvLen);
			msg.Format(_T("成功接收到数据：%s"), receivedData);
			//AfxMessageBox(msg);
			p_Mainprocess->m_rcv = receivedData;
		}
	}
}
void CarCommu::ThreadStart()
{
	// TODO: 在此处添加实现代码.
	handle_Thread = CreateThread(NULL, 0, process, this, 0, 0);
	if (handle_Thread == NULL)
		MessageBox(_T("创建线程失败"));
	else
	{
		//m_ButtonStartTh.EnableWindow(0);
		//m_ButtonstopTh.EnableWindow(1);
		MessageBox(_T("开始采集"));
	}
}


void CarCommu::OnReceive(int nErrorCode)
{
	// 本函数由框架调用，通知套接字缓冲中有数据，可以调用Receive成员函数取出
	char recvBuf[512] = { 0 };
	int recvLen = this->clientSocket.Receive(recvBuf, sizeof(recvBuf));
	AfxMessageBox(_T("recvBuf"));

	CSocket::OnReceive(nErrorCode);
}

// 在拥有 socket 的线程中执行
void CarCommu::TransferSocketToAnotherThread(CSocket pSocket)
{
	// 调用 Detach 方法，将 socket 从 C++ 对象中分离
	SOCKET hSocket = pSocket.Detach();

	// TODO: 将 hSocket 和其他信息传递给另外一个线程

	// 在另外一个线程中执行以下代码
	// 创建新的 CAsyncSocket 对象，并调用 Attach 方法
	CSocket* pNewSocket = new CSocket;
	pNewSocket->Attach(hSocket);

	// 现在 pNewSocket 就在另外一个线程中可用了
	// 可以在另外一个线程中继续使用 pNewSocket 对象
}


void CarCommu::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	TerminateThread(handle_Thread, 0);
	CDialogEx::OnOK();

}
