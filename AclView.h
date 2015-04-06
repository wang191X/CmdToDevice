#pragma once

// CAclView 视图

class CAclView : public CListView
{
	DECLARE_DYNCREATE(CAclView)

protected:
	CAclView();           // 动态创建所使用的受保护的构造函数
	virtual ~CAclView();

private:
	int m_nSortedCol;
	BOOL m_bAsc;
	static int CALLBACK ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	int GetSortedCol(){return m_nSortedCol;}
	BOOL GetAsc(){return m_bAsc;}

public:
	CCmdToDeviceDoc* GetDocument() const;

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
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnList32791();
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // CAclView.cpp 中的调试版本
inline CCmdToDeviceDoc* CAclView::GetDocument() const
   { return reinterpret_cast<CCmdToDeviceDoc*>(m_pDocument); }
#endif


