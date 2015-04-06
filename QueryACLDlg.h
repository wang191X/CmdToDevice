#pragma once
#include "afxwin.h"
#include "WFCLPAPI.h"

// QueryACLDlg 对话框

class CQueryACLDlg : public CDialog
{
	DECLARE_DYNAMIC(CQueryACLDlg)

public:
	CQueryACLDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQueryACLDlg();

// 对话框数据
	enum { IDD = IDD_QUERYACLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	SQACL sqacl;

public:
	afx_msg void OnBnClickedBtok();
	int mETBId;
	int mETEId;
};
