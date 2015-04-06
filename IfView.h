#pragma once

#include "SetBindValue.h"

// CIfView 视图

class CIfView : public CListView
{
	DECLARE_DYNCREATE(CIfView)

protected:
	CIfView();           // 动态创建所使用的受保护的构造函数
	virtual ~CIfView();

private:
	int m_nSortedCol;
	BOOL m_bAsc;
	static int CALLBACK ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	int GetSortedCol(){return m_nSortedCol;}
	BOOL GetAsc(){return m_bAsc;}

public:
	CCmdToDeviceDoc* GetDocument() const;

public:
    CSetBindValue setBVDlg;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRulebindAcl32794();
	afx_msg void OnRulebindXacl32795();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

#ifndef _DEBUG  // CIfView.cpp 中的调试版本
inline CCmdToDeviceDoc* CIfView::GetDocument() const
{ return reinterpret_cast<CCmdToDeviceDoc*>(m_pDocument); }
#endif

