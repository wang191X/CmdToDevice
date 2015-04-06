#pragma once
#include "WFCLPAPI.h"
#include <vector>
#include "afxcmn.h"

// CRulesService 对话框

class CRulesService : public CDialog
{
	DECLARE_DYNAMIC(CRulesService)

public:
	CRulesService(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRulesService();

// 对话框数据
	enum { IDD = IDD_RULESSERVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();

private:
	//void toSerialize(std::vector<SACL>& sacls_,std::string& outbound_data_);
	//void fromSerialize(std::vector<char>& recvBuff,std::vector<SACL>& sacls_);
public:
	virtual BOOL OnInitDialog();
	CListCtrl mList1;
	afx_msg void OnBnClickedStart2();
	afx_msg void OnBnClickedClrlog();
};
