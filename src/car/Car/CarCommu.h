#pragma once

#include"02_TCPClientDlg.h"
#include<list>
// CarCommu 对话框


class CarCommu : public CDialogEx,public CSocket
{
	DECLARE_DYNAMIC(CarCommu)

public:
	CarCommu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CarCommu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HANDLE handle_Thread;
	CConnSocket m_connSocket1;
	UINT m_port1;
	CIPAddressCtrl m_ip;
	CListCtrl m_listCtrl;
	list<CConnSocket*> m_clientList;
	virtual BOOL OnInitDialog();
	CString m_port;
	CString m_rcv;
	CString m_send;
	CMy02_TCPClientDlg * c_dlg=new CMy02_TCPClientDlg;
	afx_msg void OnBnClickedButton3();
	void listInit(char* port);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	CConnSocket& quote(CConnSocket& Con);

	CSocket clientSocket;
	afx_msg void OnBnClickedButton5();
	void ThreadStart();
	CEdit m_CsendBuf;
	void OnReceive(int nErrorCode);
	CEdit m_sender;
	CEdit m_rcver;
	afx_msg void OnBnClickedCancel();
	SOCKET hSocket;
	CSocket* pNewSocket;
	void CarCommu::TransferSocketToAnotherThread(CSocket pSocket);
	afx_msg LRESULT CarCommu::OnSocketEvent(WPARAM wParam, LPARAM lParam);

};
