// login.cpp: 实现文件
//
#include"stdafx.h"
#include"resource.h"
#include "pch.h"
#include "login.h"
#include "afxdialogex.h"
#include "02_TCPClientDlg.h"


// login 对话框

IMPLEMENT_DYNAMIC(login, CDialogEx)

login::login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, password_value(_T(""))
	, username_value(_T(""))
{

}

login::~login()
{
}

void login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_usingname);
	DDX_Control(pDX, IDC_EDIT2, m_edit_password);
	DDX_Text(pDX, IDC_EDIT2, password_value);
	DDX_Text(pDX, IDC_EDIT1, username_value);
	DDX_Control(pDX, IDC_BUTTON1, m_ok);
}


BEGIN_MESSAGE_MAP(login, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &login::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &login::OnBnClickedCheck1)
END_MESSAGE_MAP()


// login 消息处理程序


void login::OnBnClickedButton1()
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
		AfxGetMainWnd()->SendMessage(WM_CLOSE);//OnCancel(); // 关闭登陆界面
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


void login::OnBnClickedCheck1()
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


BOOL login::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	draw();
	UpdateData(true);
	CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT2);
	pEdit->SetPasswordChar('*');
	SetDlgItemText(IDC_EDIT2, password_value);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void login::draw()
{
	// TODO: 在此处添加实现代码.
	CImage image;
	image.Load(TEXT("D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\s.png"));  //加载图片
	// 将整控件调整为与图像同一尺寸  
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC);//获得句柄，就是控件的id
	pStatic->SetWindowPos(NULL,
		100,
		100,
		image.GetWidth(),
		image.GetHeight(),
		SWP_NOMOVE);
	pStatic->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	pStatic->SetBitmap((HBITMAP)image.Detach());
}
