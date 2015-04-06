// SetSession.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "SetSession.h"


// SetSession 对话框

IMPLEMENT_DYNAMIC(SetSession, CDialog)

SetSession::SetSession(CWnd* pParent /*=NULL*/)
	: CDialog(SetSession::IDD, pParent)
{
	
}

SetSession::~SetSession()
{
}

void SetSession::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CbSession, mCbSession);
	DDX_Control(pDX, IDC_CbVersion, mCbVersion);
	DDX_Control(pDX, IDC_EtPort, mEtPort);
	DDX_Control(pDX, IDC_EtAddress, mEtAddress);
	DDX_Control(pDX, IDC_EtUser, mEtUser);
	DDX_Control(pDX, IDC_EtPassword, mEtPassword);

    mEtAddress.SetWindowTextA("10.10.23.155");
	mEtUser.SetWindowTextA("ztg");
	mEtPassword.SetWindowTextA("ztg");
	mEtPort.SetWindowTextA("1000");
	mCbVersion.SetCurSel(2);
	mCbSession.SetCurSel(0);
}

BEGIN_MESSAGE_MAP(SetSession, CDialog)
	ON_BN_CLICKED(IDC_BtCont, &SetSession::OnBnClickedBtcont)
	ON_BN_CLICKED(IDC_BTCancel, &SetSession::OnBnClickedBtcancel)
END_MESSAGE_MAP()


// SetSession 消息处理程序

void SetSession::OnBnClickedBtcont()
{
	// TODO: 在此添加控件通知处理程序代码
    CString address;
	CString user;
	CString password;
	CString port;
	CString strVersion;
	CString strSession;
	int nVersion;
	int nSession;
	
	mEtAddress.GetWindowTextA(address);
	mEtUser.GetWindowTextA(user);
	mEtPassword.GetWindowTextA(password);
	mEtPort.GetWindowTextA(port);
	nVersion=mCbVersion.GetCurSel();
	nSession=mCbSession.GetCurSel();
	mCbVersion.GetLBText(nVersion,strVersion);
	mCbSession.GetLBText(nSession,strSession);

	strcpy(sSession.ip,address);
	strcpy(sSession.user,user);
	strcpy(sSession.password,password);
	strcpy(sSession.versionType,strVersion);
	strcpy(sSession.sessionType,strSession);
	sSession.port=atoi(port);
	
	OnOK();
}

void SetSession::OnBnClickedBtcancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

BOOL SetSession::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
