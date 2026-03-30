// PreTranslateMessage.cpp: 实现文件
//
#include"stdafx.h"
#include"resource.h"
#include "pch.h"
#include "PreTranslateMessage.h"
#include "afxdialogex.h"
#include"02_TCPClientDlg.h"


// PreTranslateMessage 对话框

IMPLEMENT_DYNAMIC(PreTranslateMessage, CDialogEx)

PreTranslateMessage::PreTranslateMessage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, username_value(_T(""))
	, password_value(_T(""))
{

}

PreTranslateMessage::~PreTranslateMessage()
{
}

void PreTranslateMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, username_value);
	DDX_Text(pDX, IDC_EDIT2, password_value);
}


BEGIN_MESSAGE_MAP(PreTranslateMessage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &PreTranslateMessage::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &PreTranslateMessage::OnBnClickedCheck1)
END_MESSAGE_MAP()


// PreTranslateMessage 消息处理程序


void PreTranslateMessage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	static int k = 3;
	CString name;
	CString password; // 创造两个字符串变量来接受用户输入的信息（用户名和密码等）
	GetDlgItemText(IDC_EDIT1, name); // 返回用户名
	GetDlgItemText(IDC_EDIT2, password); // 返回密码
	UpdateData(true);
	if (password_value.IsEmpty())
	{
		MessageBox(L"用户名不能为空");
	}
	if (password_value.IsEmpty())
		MessageBox(L"密码不能为空");
	if (username_value == "admin" && password_value == "123456")
	{
		// 进入主对话框界面
		//m_SuccessLogin = true;
		CMy02_TCPClientDlg a;
		a.DoModal();
		CDialogEx::OnOK(); // 关闭登陆界面
	}
	else
	{
		// 弹出窗口提示用户名或密码不正确
		MessageBox(_T("用户名或密码不正确！"), _T("提示"), MB_OK);
		// 清空用户名和密码，便于重新输入
		username_value = "";
		password_value = "";
		UpdateData(FALSE); // 更新编辑框控件的显示值
	}
}


void PreTranslateMessage::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_CHECK1) == BST_CHECKED)	//如果被选中
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT2);
		pEdit->SetPasswordChar(0);
		SetDlgItemText(IDC_EDIT2, password_value);
		UpdateData(false);
	}
	else
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT2);
		pEdit->SetPasswordChar('*');
		SetDlgItemText(IDC_EDIT2, password_value);
		UpdateData(false);
	}
	GetDlgItem(IDC_EDIT2)->SetFocus();
}


void PreTranslateMessage::PreTranslateMessag()
{
	// TODO: 在此处添加实现代码.
}
