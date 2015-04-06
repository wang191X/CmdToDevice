// QueryACLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "QueryACLDlg.h"


// QueryACLDlg 对话框

IMPLEMENT_DYNAMIC(CQueryACLDlg, CDialog)

CQueryACLDlg::CQueryACLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryACLDlg::IDD, pParent)
	, mETBId(0),mETEId(0)
{

}

CQueryACLDlg::~CQueryACLDlg()
{
}

void CQueryACLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ETBId, mETBId);
	DDV_MinMaxInt(pDX, mETBId, 1, 255);
	DDX_Text(pDX, IDC_ETEId, mETEId);
	DDV_MinMaxInt(pDX, mETEId, 1, 255);
}


BEGIN_MESSAGE_MAP(CQueryACLDlg, CDialog)
	ON_BN_CLICKED(IDC_BTOK, &CQueryACLDlg::OnBnClickedBtok)
END_MESSAGE_MAP()


// QueryACLDlg 消息处理程序

void CQueryACLDlg::OnBnClickedBtok()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

    if(mETBId>mETEId)
	{
		CString err="起始id应不大于终止id";
		AfxMessageBox(err);
	}

	sqacl.groupBegin=mETBId;
	sqacl.groupEnd=mETEId;

	OnOK();
}
