/*#include "stdafx.h"
#include "MyServerSocket.h"

MyServerSocket::MyServerSocket() {
}

MyServerSocket::~MyServerSocket() {
}

// 将原来的 StartServer 函数移除，因为我们将在按钮点击事件中直接创建和监听服务器套接字

void MyServerSocket::OnAccept(int nErrorCode) {
    MyServerSocket* pClientSocket = new MyServerSocket();

    if (Accept(*pClientSocket)) {
        // 处理新连接
        m_client.push_back(pClientSocket);
        TRACE("Client connected\n");
        AfxMessageBox(_T("accept"));

        // 启动异步接收数据
        pClientSocket->AsyncSelect(FD_READ | FD_CLOSE);
    }
    else {
        TRACE("Failed to accept client connection. Error code: %d\n", GetLastError());
        delete pClientSocket;
    }

    CAsyncSocket::OnAccept(nErrorCode);
}

void MyServerSocket::OnReceive(int nErrorCode) {
    char buffer[512] = { 0 };
    int bytesRead = Receive(buffer, sizeof(buffer));

    CString a(buffer);

    if (bytesRead > 0) {
        // 处理接收到的数据
        TRACE("Received data from client: %s\n", buffer);

        // 回显数据给客户端
        Send(buffer, bytesRead);
        AfxMessageBox(a);
    }
    else if (bytesRead == 0) {
        // 客户端断开连接
        TRACE("Client disconnected\n");
        Close();
        delete this;
    }
    else {
        // 接收数据出错
        TRACE("Failed to receive data from client. Error code: %d\n", GetLastError());
        Close();
        delete this;
    }

    CAsyncSocket::OnReceive(nErrorCode);
}*/
#include "stdafx.h"
#include "MyServerSocket.h"
#include <string>
#include <fstream>
#include <thread>
#include <cstdio> 

std::list<MyServerSocket*> MyServerSocket::m_clientList;  // 定义和初始化静态成员变量

using namespace std;
MyServerSocket::MyServerSocket() {
   // m_clientPort = 0;
}

MyServerSocket::~MyServerSocket() {
}

void MyServerSocket::OnAccept(int nErrorCode) {
    pClientSocket = new MyServerSocket();
    CString a;
    int port;

    if (Accept(*pClientSocket)) {
        // 获取客户端的地址信息
        SOCKADDR_IN clientAddr;
        int addrLen = sizeof(clientAddr);
        pClientSocket->GetPeerName((SOCKADDR*)&clientAddr, &addrLen);

        // 获取客户端端口号
        UINT clientPort = ntohs(clientAddr.sin_port);
        pClientSocket->m_clientPort = clientPort;
        port= clientPort;
        //TRACE("Client connected on port %d\n", clientPort);
        //m_clientPort= clientPort;
        CString message;
        message.Format(_T("用户: %u已连接,"), pClientSocket->m_clientPort);
        //AfxMessageBox(message);

        char buff1[256] = { 0 };
        sprintf(buff1, "您好，用户%u", pClientSocket->m_clientPort);
        int flag= pClientSocket->Send(buff1,20);
        if (!flag)
        {
            AfxMessageBox(_T("error"));
        }

        //AfxMessageBox(a);

        m_clientList.push_back(pClientSocket); // 将客户端指针添加到列表
        if (m_clientList.empty())
        {
            AfxMessageBox(_T("客户端列表为空"));
        }
        pClientSocket->AsyncSelect(FD_READ | FD_CLOSE);
    }
    else {
        TRACE("Failed to accept client connection. Error code: %d\n", GetLastError());
        //delete pClientSocket;
    }
    CStringA fixedFilePath1 = "D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\交流端口号.csv";
    CString porte;
    porte.Format(_T("%u"), m_clientPort);
    std::ofstream SaveFile1(fixedFilePath1, ios::app);
    
    if (!SaveFile1.is_open())
    {
        AfxMessageBox(_T("文件打开失败!"));
        return;
    }

    SYSTEMTIME t;
    GetLocalTime(&t);
    CStringA porteA(porte);
    CStringA timeA;
    timeA.Format("[%d:%d:%d]", t.wHour, t.wMinute, t.wSecond);

    SaveFile1 << timeA.GetString() << "," << "127.0.0.1"<< "," << port << "," << "在线" << std::endl;

    SaveFile1.close();
    
    CAsyncSocket::OnAccept(nErrorCode);
}

/*void MyServerSocket::OnReceive(int nErrorCode) {
    char buffer[1024] = { 0 };
    int bytesRead = Receive(buffer, sizeof(buffer));

    CString a(buffer);

    if (bytesRead > 0) {
        if (m_clientList.empty())
        {
            AfxMessageBox(_T("empty"));
        }
        UINT recevicePort = _ttoi(a);

        if (SelectPort != NULL)
        {
            int flag1 = SelectPort->Send(buffer, bytesRead);
            if (flag1)
            {
                AfxMessageBox(_T("select"));
            }
        }

        for (auto it = m_clientList.begin(); it != m_clientList.end(); ++it) {
            //AfxMessageBox(_T("Send"));
            //CString message;
            //message.Format(_T("(*it)->m_clientPort: %u, recevicePort: %u"), (*it)->m_clientPort, recevicePort);
            

            if ((*it)->m_clientPort == recevicePort) {
                //b.Format(_T("%d"), (*it)->m_clientPort);
                //AfxMessageBox(message);
                /*flag = (*it)->Send(b, bytesRead);
                if (flag)
                {
                    AfxMessageBox(_T("it发送成功"));
                }
                AfxMessageBox(_T("配对成功"));
                SelectPort = *it;
                break;
            }
        }
        
    }
    else {
        TRACE("Failed to receive data from client on port %d. Error code: %d\n", m_clientPort, GetLastError());
        Close();
    }
    }
  

    CAsyncSocket::OnReceive(nErrorCode);
}*/
void MyServerSocket::OnReceive(int nErrorCode) {
    // 在多线程环境下处理接收到的数据
    std::thread receiveThread(&MyServerSocket::HandleReceivedData, this, nErrorCode);
    receiveThread.detach();
    CAsyncSocket::OnReceive(nErrorCode);

}

void MyServerSocket::HandleReceivedData(int nErrorCode) {
    char buffer[1024] = { 0 };
    int bytesRead = Receive(buffer, sizeof(buffer));
    char buffers[1024] = { 0 };
    char buffers2[1024] = { 0 };
    
    CString a(buffer);
    char buff[20] = { 0 }; // 声明一个足够大的字符数组来存储转换后的字符串

    // 使用 sprintf 将 UINT 转换为字符串
    sprintf(buff, "%u", this->m_clientPort);

    // 将字符串输出到控制台
    if (bytesRead > 0) {
        if (m_clientList.empty()) {
            AfxMessageBox(_T("empty"));
        }

        UINT recevicePort = _ttoi(a);

        if (SelectPort != NULL) {
            
            
            int flag1 = SelectPort->Send(buffer, bytesRead);
            if (flag1) {
               //AfxMessageBox(_T("发送成功"));
            }
        }
        for (auto it = m_clientList.begin(); it != m_clientList.end(); ++it) {
            if ((*it)->m_clientPort == recevicePort) {
                
                //AfxMessageBox(_T("配对成功"));
                SelectPort = *it;
                strcat(buff, "与您连接");
                sprintf(buffers2, "与%u配对成功", SelectPort->m_clientPort);
                this->Send(buffers2, 30);
                SelectPort->Send(buff, 20);
                break;
            }
        }

    }
    else {
        TRACE("Failed to receive data from client on port %d. Error code: %d\n", m_clientPort, GetLastError());
        Close();
    }
}
void MyServerSocket::OnClose(int nErrorCode)
{
   /*CStringA fixedFilePath1 = "D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\交流端口号.csv";
    CString porte;
    porte.Format(_T("%d"), this->m_clientPort);
    std::ofstream SaveFile1(fixedFilePath1, ios::app);
    if (!SaveFile1.is_open())
    {
        AfxMessageBox(_T("Failed to open file!"));
        return;
    }

    SYSTEMTIME t;
    GetLocalTime(&t);
    CStringA porteA(porte);
    CStringA timeA;
    timeA.Format("[%d:%d:%d]", t.wHour, t.wMinute, t.wSecond);

    SaveFile1 << timeA.GetString() << "," << "127.0.0.1" << "," << porteA.GetString() << "," << "断开连接" << std::endl;

    SaveFile1.close();

    MyServerSocket::OnClose(nErrorCode);*/ 
}

void MyServerSocket::SelectSend(char* Port)
{
    // TODO: 在此处添加实现代码.
    int flag;
    CString b;
    Send(Port, strlen(Port));
    if (m_clientList.empty())
    {
        AfxMessageBox(_T("empty66"));
    }
    for (auto it = m_clientList.begin(); it != m_clientList.end(); ++it) {
        AfxMessageBox(_T("Send"));
        if ((*it)->m_clientPort == *Port) {
            //flag = (*it)->Send(, strlen());
            if (!flag)
            {
                AfxMessageBox(_T("Send"));
            }
            break;
        }
    }
}
