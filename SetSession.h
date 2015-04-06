#pragma once
#include "afxwin.h"
#include "WFCLPAPI.h"

// SetSession 对话框

class SetSession : public CDialog
{
	DECLARE_DYNAMIC(SetSession)

public:
	SetSession(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SetSession();

// 对话框数据
	enum { IDD = IDD_SETSESSION };

public:
	SSession sSession;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtcont();
	afx_msg void OnBnClickedBtcancel();
	CComboBox mCbSession;
	CComboBox mCbVersion;
	CEdit mEtPort;
	CEdit mEtAddress;
	CEdit mEtUser;
	CEdit mEtPassword;
	CString sessionType;
	virtual BOOL OnInitDialog();
};
