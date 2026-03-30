// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "02_TCPServer.h"
#include "ServerSocket.h"
#include "02_TCPServerDlg.h"
#include "string"
#include <fstream>

using namespace std;
// CServerSocket

CServerSocket::CServerSocket(CMy02_TCPServerDlg* dlg)
{
	m_dlg = dlg;
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数

// 新的连接请求来了，该函数将被回调
void CServerSocket::OnAccept(int nErrorCode)
{
	// 由框架调用，通知监听套接字现在可以调用Accept成员函数来接收悬挂的（pending）连接请求。
	CConnSocket * client = new CConnSocket(m_dlg);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	int addrLen = sizeof(addr);

	// 获取通信套接字
	Accept(*client,(SOCKADDR*)&addr,&addrLen);
	char* ip = inet_ntoa(addr.sin_addr);
	client->SetClientAddr(CString(ip), addr.sin_port);
	m_clientList.push_back(client);//利用list存放

	// 界面添加连接消息
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d:连接服务器成功!"),t.wHour,t.wMinute,t.wSecond,CString(ip),addr.sin_port);
	m_dlg->AddMsg(msg);

	// Assuming CConnSocket has member functions GetPort() and GetIPAddress()
	CString porte,time;
	string port;
	porte.Format(_T("%d"), client->m_port);
	time.Format(_T("[%d:%d:%d]"), t.wHour,t.wMinute,t.wSecond);
	// Insert the information into the list control
	int nIndex = m_dlg->m_listCtrl1.GetItemCount();

	m_dlg->m_listCtrl1.InsertItem(nIndex, _T(""));//要有这个，不然显示不了

	m_dlg->m_listCtrl1.SetItemText(nIndex, 1, client->m_ip); // Assuming column 0 is for IP address
	m_dlg->m_listCtrl1.SetItemText(nIndex, 2, porte); // Column 1 for port
	m_dlg->m_listCtrl1.SetItemText(nIndex, 0, time); // Column 1 for port
	m_dlg->m_listCtrl1.SetItemText(nIndex, 3, _T("在线")); // Column 1 for port

	//SelectSend(port);


	CStringA fixedFilePath1 = "D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\端口号储存.csv";
	std::ofstream SaveFile1(fixedFilePath1,ios::app);
	if (!SaveFile1.is_open())
	{
		AfxMessageBox(_T("Failed to open file!"));
		return;
	}

	CStringA timeA(time);
	CStringA clientIPA(client->m_ip);
	CStringA porteA(porte);

	SaveFile1 << timeA.GetString() << "," << clientIPA.GetString() << "," << porteA.GetString() << "," << "在线" << std::endl;

	SaveFile1.close();
	//Sender(client->m_ip);
	//m_dlg->ClientInsert();
	//Sender(msg);

	CSocket::OnAccept(nErrorCode);
}

void CServerSocket::CloseAllConn()
{
	// 关闭监听套接字，先关闭 连接的套接字
	list<CConnSocket*>::iterator it = m_clientList.begin();
	for (; it != m_clientList.end(); )
	{
		(*it)->Close();
		delete (*it);
		it = m_clientList.erase(it);
	}
	this->Close();
}

void CServerSocket::Sender(CString msg)
{
	// TODO: 在此处添加实现代码.
	/*char szBuf[256] = {0};
	memcpy(szBuf, msg, msg.GetLength());
	list<CConnSocket*>::iterator it = m_clientList.begin();
	int iWrite;
	iWrite = (*it)->Send(szBuf, 256, 1);
	if (SOCKET_ERROR == iWrite) {
		AfxMessageBox(szBuf);
	}*/
	//AfxMessageBox(msg);
	
	
	/*if (m_clientList.empty()) {
		// 处理没有客户端的情况
		AfxMessageBox(_T("No clients available."));
		return;
	}
	else
	{
		//AfxMessageBox(msg);
		for (auto it = m_clientList.begin(); it != m_clientList.end(); ++it) {
			char szBuf[256] = { 0 };
			memcpy(szBuf, msg, msg.GetLength());
			int errorCode = ::WSAGetLastError(); // 获取错误代码
			int iWrite = (*it)->Send(_T("1"), 6);
			if (SOCKET_ERROR == iWrite) {
				// 发送失败时的处理
		// 处理错误，例如输出错误信息
				AfxMessageBox(_T("Failed to send message to client."));
				AfxMessageBox(errorCode);
			}
		}
	}*/
	if (m_clientList.empty()) {
		// 处理没有客户端的情况
		AfxMessageBox(_T("No clients available."));
		return;
	}
	else {
		// 遍历客户端列表
		for (auto it = m_clientList.begin(); it != m_clientList.end(); ++it) {
			char szBuf[256] = { 0 };
			// 获取消息的字符数组指针，并复制消息内容到缓冲区
			strncpy(szBuf, CT2A(msg.GetBuffer()), sizeof(szBuf) - 1);//这个是真不容易，尝试了好久啊
			// 释放 CString 缓冲区
			msg.ReleaseBuffer();

			int errorCode = ::WSAGetLastError(); // 获取错误代码
			// 发送完整消息给客户端
			int iWrite = (*it)->Send(szBuf, strlen(szBuf));
			if (SOCKET_ERROR == iWrite) {
				// 处理发送失败的情况
				AfxMessageBox(_T("Failed to send message to client."));
				AfxMessageBox(errorCode); // 输出错误代码
			}
		}
	}

	
	/*AfxMessageBox(msg);
	for (auto pClientSocket : m_clientList)
	{
		// 发送消息给每个客户端
		pClientSocket->Send(msg, msg.GetLength());
	}*/

	/*for (; it != m_clientList.end(); )
	{
	int iWrite;
	iWrite = (*it)->Send(szBuf, 256, 1);
	if (SOCKET_ERROR == iWrite) {
		AfxMessageBox(szBuf);
	}
	it = m_clientList.erase(it);
	}*/
	
}


void CServerSocket::ClientInsrt()
{
	// TODO: 在此处添加实现代码.
}


void CServerSocket::SelectSend(CString port)//发给已连接客户端，目前连接情况
{
	if (m_clientList.empty()) {
		// 处理没有客户端的情况
		AfxMessageBox(_T("No clients available."));
		return;
	}
	else {
		// 遍历客户端列表
		for (auto it = m_clientList.begin(); it != m_clientList.end(); ++it) {
			if ((*it)->m_port != port)
			{
				char szBuf[256] = { 0 };
				_itoa_s((*it)->m_port, szBuf, 10);

				// 释放 CString 缓冲区
				//port.ReleaseBuffer();

				// 发送完整消息给客户端
				int iWrite = (*it)->Send(szBuf, strlen(szBuf));

				//strncpy(szBuf, CT2A((*it)->m_ip.GetBuffer()), sizeof(szBuf) - 1);
				//(*it)->Send(szBuf, strlen(szBuf));
				//AfxMessageBox((*it)->m_port);
				//AfxMessageBox(port);

				if (SOCKET_ERROR == iWrite) {
					// 处理发送失败的情况
					AfxMessageBox(_T("Failed to send message to client."));
				}
			}
		}
	}
}
