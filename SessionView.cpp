// SessionView.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "CmdToDeviceDoc.h"
#include "SessionView.h"

#include <vector>

// CSessionView

IMPLEMENT_DYNCREATE(CSessionView, CListView)

CSessionView::CSessionView()
{
	
}

CSessionView::~CSessionView()
{
}

BEGIN_MESSAGE_MAP(CSessionView, CListView)
END_MESSAGE_MAP()


// CSessionView 诊断

#ifdef _DEBUG
void CSessionView::AssertValid() const
{
	CListView::AssertValid();
}

CCmdToDeviceDoc* CSessionView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCmdToDeviceDoc)));
	return (CCmdToDeviceDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CSessionView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSessionView 消息处理程序

void CSessionView::OnInitialUpdate()
{
	// TODO: 在此添加专用代码和/或调用基类
	GetDocument()->pSessionView=this;
	GetParentFrame()->SetWindowTextA("会话");

	CListCtrl* listCtrl=&GetListCtrl();
	listCtrl->ModifyStyle(NULL,LVS_REPORT);
	listCtrl->SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	using namespace std;
    vector <CString>::iterator vIter;
	vector<CString> vTableHeader;
	vTableHeader.push_back("会话名称");
	vTableHeader.push_back("传输方式");
	vTableHeader.push_back("地址");
	vTableHeader.push_back("端口");
	vTableHeader.push_back("FCLP版本");
	vTableHeader.push_back("用户名");
	int itemNum=0;

	for ( vIter = vTableHeader.begin( ) ; vIter != vTableHeader.end( ) ; vIter++ )
	{
		listCtrl->InsertColumn(itemNum,*vIter,LVCFMT_LEFT,100,itemNum);
		itemNum++;
	}

	vTableHeader.clear();

	CListView::OnInitialUpdate();
}

void CSessionView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CCmdToDeviceDoc* pDoc=GetDocument();

	if(pDoc->wfclpapi.rSession.isSuccess)
	{
		CListCtrl* listCtrl=&GetListCtrl();
		int itemCount=listCtrl->GetItemCount();
		listCtrl->InsertItem(itemCount,"");
		
		CString id;
		id.Format("会话%d",itemCount+1);
		listCtrl->SetItemText(itemCount,0,id);
		
		listCtrl->SetItemText(itemCount,1,pDoc->wfclpapi.rSession.sSession.sessionType);
		listCtrl->SetItemText(itemCount,2,pDoc->wfclpapi.rSession.sSession.ip);
		
		int port=pDoc->wfclpapi.rSession.sSession.port;
		CString strPort;
		strPort.Format("%d",port);
		listCtrl->SetItemText(itemCount,3,strPort);
		
		listCtrl->SetItemText(itemCount,4,pDoc->wfclpapi.rSession.sSession.versionType);
		listCtrl->SetItemText(itemCount,5,pDoc->wfclpapi.rSession.sSession.user);

		pDoc->wfclpapi.rSession.isSuccess=false;
	}
}