/*#pragma once
#include <afxsock.h>
#include"stdafx.h"
#include<list>
#include"MyServerSocket.h"

class MyServerSocket : public CAsyncSocket
{
public:
    MyServerSocket();
    virtual ~MyServerSocket();
    std::list<MyServerSocket*> m_client;
    USHORT m_port;

    void StartServer(UINT port);

protected:
    virtual void OnAccept(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
};*/
#pragma once

#include <afxsock.h>
#include<list>

class MyServerSocket : public CAsyncSocket {
public:
    MyServerSocket();
    virtual ~MyServerSocket();

    void OnAccept(int nErrorCode) override;
    void OnReceive(int nErrorCode) override;
    void MyServerSocket::OnClose(int nErrorCode)override;
    MyServerSocket* pClientSocket;


    UINT m_clientPort; // 客户端端口号
public:
    void SelectSend(char* Port);
    static std::list<MyServerSocket*> m_clientList; // 存储客户端指针的列表
    MyServerSocket* SelectPort=NULL;
    void HandleReceivedData(int nErrorCode);

};