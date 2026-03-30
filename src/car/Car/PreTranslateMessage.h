#pragma once


// PreTranslateMessage 对话框

class PreTranslateMessage : public CDialogEx
{
	DECLARE_DYNAMIC(PreTranslateMessage)

public:
	PreTranslateMessage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PreTranslateMessage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString username_value;
	CString password_value;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	void PreTranslateMessag();
};
