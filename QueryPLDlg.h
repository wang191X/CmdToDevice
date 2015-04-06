#pragma once


// CQueryPLDlg 对话框

class CQueryPLDlg : public CDialog
{
	DECLARE_DYNAMIC(CQueryPLDlg)

public:
	CQueryPLDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQueryPLDlg();

// 对话框数据
	enum { IDD = IDD_QUERYPLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int mETBId;
	int mETEId;
	afx_msg void OnBnClickedBtok();
	afx_msg void OnBnClickedBtcancel();
};
