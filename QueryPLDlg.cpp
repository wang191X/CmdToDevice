// QueryPLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "QueryPLDlg.h"


// CQueryPLDlg 对话框

IMPLEMENT_DYNAMIC(CQueryPLDlg, CDialog)

CQueryPLDlg::CQueryPLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryPLDlg::IDD, pParent)
	, mETBId(0)
	, mETEId(0)
{

}

CQueryPLDlg::~CQueryPLDlg()
{
}

void CQueryPLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ETBId, mETBId);
	DDX_Text(pDX, IDC_ETEId, mETEId);
}


BEGIN_MESSAGE_MAP(CQueryPLDlg, CDialog)
	ON_BN_CLICKED(IDC_BTOK, &CQueryPLDlg::OnBnClickedBtok)
	ON_BN_CLICKED(IDC_BTCancel, &CQueryPLDlg::OnBnClickedBtcancel)
END_MESSAGE_MAP()


// CQueryPLDlg 消息处理程序

void CQueryPLDlg::OnBnClickedBtok()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	
	OnOK();
}

void CQueryPLDlg::OnBnClickedBtcancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
