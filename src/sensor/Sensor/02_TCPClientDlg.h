
// 02_TCPClientDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ConnSocket.h"
#include "DataSave.h"
#include "CMSCOMM2.h"
#include "CMSCOMM1.h"

// CMy02_TCPClientDlg 对话框
class CMy02_TCPClientDlg : public CDialogEx
{
	friend class CSensor;

// 构造
public:
	CMy02_TCPClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY02_TCPCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()
public:
//	CIPAddressCtrl m_serverIp;
private:
	UINT m_port;
	CIPAddressCtrl m_ip;
	CButton m_connBtn;
	CButton m_disConnBtn;
	CString m_sendBuf;
	CButton m_sendBtn;
	CButton m_clearBtn;
	CListCtrl m_listCtrl;
	CConnSocket m_connSocket;
	bool m_connSuc;
	CSensor* m_Sensor;
	CMy02_TCPClientDlg* pCom;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	// 往消息列表中添加一条消息
	void AddMsg(CString msg);
	
	void MyEnableBtn();
	//afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	//afx_msg void OnEnChangeEdit3();
	//afx_msg void OnCbnSelchangeCombo2();
	CComboBox chuankouhao;
	//afx_msg void OnCbnSelchangeCombo1();
	CComboBox botelv;
	CComboBox SensorType;
	afx_msg void OnBnClickedButton5();
	CMSCOMM2 communications1;
	int PortSelect(int m_McsPortNum);
	DataSave* SensorSelect(int SensorNum);
	void OnOncommMscomm1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	CButton xuanze;
	CMSCOMM1 communications2;
	afx_msg void OnBnClickedCheck1();
	void OnTimer(UINT_PTR nIDEvent);
	void PortInit(CMSCOMM2& communication);
	void PortInit(CMSCOMM1& communication);
	afx_msg void OnBnClickedButton6();
	CButton SerialStart;
	CButton SerialStop;
};
