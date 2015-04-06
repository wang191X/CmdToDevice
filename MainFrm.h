// MainFrm.h : CMainFrame 类的接口
//


#pragma once

#include "SetSession.h"
#include "QueryACLDlg.h"
#include "QueryXACLDlg.h"
#include "QueryPLDlg.h"
#include "NewACLDlg.h"
#include "NewXACLDlg.h"
#include "NewPLDlg.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 属性
public:
	SetSession sessionDlg;
	/*CQueryACLDlg queryACLDlg;
	CQueryXACLDlg queryXACLDlg;
    CQueryPLDlg queryPLDlg;
	CNewACLDlg newACLDlg;
    CNewPLDlg newPLDlg;
    CNewXACLDlg newXACLDlg;*/

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	int SwitchView(CDocTemplate* pTemplate, CRuntimeClass* pViewClass);
	afx_msg void OnNewsession();
	afx_msg void OnQueryacl();
	afx_msg void OnQueryxacl();
	afx_msg void OnQuerypl();
	afx_msg void OnUploadacl();
	afx_msg void OnUploadxacl();
	afx_msg void OnUploadpl();
	afx_msg void OnRulebind();
	afx_msg void OnBeginservice();
};


