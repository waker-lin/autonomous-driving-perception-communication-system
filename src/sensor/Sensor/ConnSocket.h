#pragma once

class CMy02_TCPClientDlg;
// CConnSocket ÃüÁîÄ¿±ê

class CConnSocket : public CSocket
{
public:
	CConnSocket(CMy02_TCPClientDlg* dlg = NULL);
	virtual ~CConnSocket();
	BOOL Connect(LPCTSTR lpszHostAddress, UINT nHostPort);

	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
private:
	CMy02_TCPClientDlg* m_dlg;
	CString m_ip;
	UINT m_port;
	CMy02_TCPClientDlg * m_warn;
public:
	virtual void OnReceive(int nErrorCode);
};


