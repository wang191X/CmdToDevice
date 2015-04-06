// SetBindValue.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "SetBindValue.h"


// CSetBindValue 对话框

IMPLEMENT_DYNAMIC(CSetBindValue, CDialog)

CSetBindValue::CSetBindValue(CWnd* pParent /*=NULL*/)
	: CDialog(CSetBindValue::IDD, pParent)
	, mEtBindValue(0)
{

}

CSetBindValue::~CSetBindValue()
{
}

void CSetBindValue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EtBindValue, mEtBindValue);
	DDV_MinMaxInt(pDX, mEtBindValue, 0, 64);
}


BEGIN_MESSAGE_MAP(CSetBindValue, CDialog)
	ON_BN_CLICKED(IDOK, &CSetBindValue::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSetBindValue::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSetBindValue 消息处理程序

void CSetBindValue::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	OnOK();
}

void CSetBindValue::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
