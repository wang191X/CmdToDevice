// QueryXACLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "QueryXACLDlg.h"


// CQueryXACLDlg 对话框

IMPLEMENT_DYNAMIC(CQueryXACLDlg, CDialog)

CQueryXACLDlg::CQueryXACLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryXACLDlg::IDD, pParent)
	, mETBId(0)
	, mETEId(0)
{

}

CQueryXACLDlg::~CQueryXACLDlg()
{
}

void CQueryXACLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ETBId, mETBId);
	DDV_MinMaxInt(pDX, mETBId, 1, 255);
	DDX_Text(pDX, IDC_ETEId, mETEId);
	DDV_MinMaxInt(pDX, mETEId, 1, 255);
}


BEGIN_MESSAGE_MAP(CQueryXACLDlg, CDialog)
	ON_BN_CLICKED(IDC_BTOK, &CQueryXACLDlg::OnBnClickedBtok)
END_MESSAGE_MAP()


// CQueryXACLDlg 消息处理程序

void CQueryXACLDlg::OnBnClickedBtok()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	if(mETBId>mETEId)
	{
		CString err="起始id应不大于终止id";
		AfxMessageBox(err);
	}

	sqxacl.groupBegin=mETBId;
	sqxacl.groupEnd=mETEId;
	OnOK();
}

BOOL CQueryXACLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
