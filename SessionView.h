#pragma once


// CSessionView 视图

class CSessionView : public CListView
{
	DECLARE_DYNCREATE(CSessionView)

protected:
	CSessionView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSessionView();

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

public:

private:

//public:
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // SessionView.cpp 中的调试版本
inline CCmdToDeviceDoc* CSessionView::GetDocument() const
   { return reinterpret_cast<CCmdToDeviceDoc*>(m_pDocument); }
#endif


