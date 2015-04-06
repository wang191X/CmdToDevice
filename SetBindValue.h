#pragma once


// CSetBindValue 对话框

class CSetBindValue : public CDialog
{
	DECLARE_DYNAMIC(CSetBindValue)

public:
	CSetBindValue(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetBindValue();

// 对话框数据
	enum { IDD = IDD_SETBINDVALUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int mEtBindValue;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
