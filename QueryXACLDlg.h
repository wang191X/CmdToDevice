#pragma once
#include "WFCLPAPI.h"

// CQueryXACLDlg 对话框

class CQueryXACLDlg : public CDialog
{
	DECLARE_DYNAMIC(CQueryXACLDlg)

public:
	CQueryXACLDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQueryXACLDlg();

// 对话框数据
	enum { IDD = IDD_QUERYXACLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int mETBId;
	int mETEId;
	afx_msg void OnBnClickedBtok();

public:
	SQXACL sqxacl;
	virtual BOOL OnInitDialog();
};
