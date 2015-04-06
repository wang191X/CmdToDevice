// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "MainFrm.h"
#include "CmdToDeviceDoc.h"
#include "SessionView.h"
#include "AclView.h"
#include "XACLView.h"
#include "PLView.h"
#include "IfView.h"
#include "RulesService.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_NewSession, &CMainFrame::OnNewsession)
	ON_COMMAND(ID_QueryACL, &CMainFrame::OnQueryacl)
	ON_COMMAND(ID_QueryXACL, &CMainFrame::OnQueryxacl)
	ON_COMMAND(ID_QueryPL, &CMainFrame::OnQuerypl)
	ON_COMMAND(ID_UpLoadACL, &CMainFrame::OnUploadacl)
	ON_COMMAND(ID_UploadXACL, &CMainFrame::OnUploadxacl)
	ON_COMMAND(ID_UploadPL, &CMainFrame::OnUploadpl)
	ON_COMMAND(ID_RuleBind, &CMainFrame::OnRulebind)
	ON_COMMAND(ID_BeginService, &CMainFrame::OnBeginservice)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序

int CMainFrame::SwitchView(CDocTemplate* pTemplate, CRuntimeClass* pViewClass)
{
	CMDIChildWnd* pActiveChild=MDIGetActive();
	CDocument* pDocument=pActiveChild->GetActiveDocument();

	if(pActiveChild==NULL||pDocument==NULL)
	{
		return -1;
	}

	CView* pView;
	POSITION pos= pDocument->GetFirstViewPosition();
    
	while(pos!=NULL)
	{
		pView=pDocument->GetNextView(pos);

		if(pView->IsKindOf(pViewClass))
		{
			pView->GetParentFrame()->ActivateFrame();
			return -1;
		}
		pView->UpdateWindow();
	}
	
	CFrameWnd* pFrame=pTemplate->CreateNewFrame(pDocument,pActiveChild);

	if(pFrame==NULL)
	{
		return -1;
	}

	pTemplate->InitialUpdateFrame(pFrame,pDocument);
	return 0;
}


void CMainFrame::OnNewsession()
{
	// TODO: 在此添加命令处理程序代码
	if(IDOK==sessionDlg.DoModal())
	{
		CDocTemplate* pTemplate=((CCmdToDeviceApp*)AfxGetApp())->mTemplateSession;
		((CMainFrame*)AfxGetMainWnd())->SwitchView(pTemplate,RUNTIME_CLASS(CSessionView));
		CMDIChildWnd* pActiveChild=MDIGetActive();
		CDocument* pDocument=pActiveChild->GetActiveDocument();
		((CCmdToDeviceDoc*)pDocument)->newSession();
	}
}

void CMainFrame::OnQueryacl()
{
	// TODO: 在此添加命令处理程序代码
	/*if(IDOK==queryACLDlg.DoModal())
	{
		CDocTemplate* pTemplate=((CCmdToDeviceApp*)AfxGetApp())->pTemplateACL;
		((CMainFrame*)AfxGetMainWnd())->SwitchView(pTemplate,RUNTIME_CLASS(CAclView));
		CMDIChildWnd* pActiveChild=MDIGetActive();
		CDocument* pDocument=pActiveChild->GetActiveDocument();
		((CCmdToDeviceDoc*)pDocument)->queryACL();
	}*/
}

void CMainFrame::OnQueryxacl()
{
	// TODO: 在此添加命令处理程序代码
   /* if(IDOK==queryXACLDlg.DoModal())
	{
		CDocTemplate* pTemplate=((CCmdToDeviceApp*)AfxGetApp())->pTemplateXACL;
		((CMainFrame*)AfxGetMainWnd())->SwitchView(pTemplate,RUNTIME_CLASS(CXACLView));
		CMDIChildWnd* pActiveChild=MDIGetActive();
		CDocument* pDocument=pActiveChild->GetActiveDocument();
		((CCmdToDeviceDoc*)pDocument)->queryXACL();
	}*/
}

void CMainFrame::OnQuerypl()
{
	// TODO: 在此添加命令处理程序代码
	/*if(IDOK==queryPLDlg.DoModal())
	{
		CDocTemplate* pTemplate=((CCmdToDeviceApp*)AfxGetApp())->pTemplatePL;
		((CMainFrame*)AfxGetMainWnd())->SwitchView(pTemplate,RUNTIME_CLASS(CPLView));
		CMDIChildWnd* pActiveChild=MDIGetActive();
		CDocument* pDocument=pActiveChild->GetActiveDocument();
		((CCmdToDeviceDoc*)pDocument)->queryPL();
	}*/
}

void CMainFrame::OnUploadacl()
{
	// TODO: 在此添加命令处理程序代码
	/*if(IDOK==newACLDlg.DoModal())
	{
		CDocTemplate* pTemplate=((CCmdToDeviceApp*)AfxGetApp())->pTemplateACL;
		((CMainFrame*)AfxGetMainWnd())->SwitchView(pTemplate,RUNTIME_CLASS(CAclView));
		CMDIChildWnd* pActiveChild=MDIGetActive();
		CDocument* pDocument=pActiveChild->GetActiveDocument();
		((CCmdToDeviceDoc*)pDocument)->upLoadACL();
	}*/
}

void CMainFrame::OnUploadxacl()
{
	// TODO: 在此添加命令处理程序代码
	/*if(IDOK==newXACLDlg.DoModal())
	{
		CDocTemplate* pTemplate=((CCmdToDeviceApp*)AfxGetApp())->pTemplateXACL;
		((CMainFrame*)AfxGetMainWnd())->SwitchView(pTemplate,RUNTIME_CLASS(CXACLView));
		CMDIChildWnd* pActiveChild=MDIGetActive();
		CDocument* pDocument=pActiveChild->GetActiveDocument();
		((CCmdToDeviceDoc*)pDocument)->uploadXACL();
	}*/
}

void CMainFrame::OnUploadpl()
{
	// TODO: 在此添加命令处理程序代码
	/*if(IDOK==newPLDlg.DoModal())
	{
		CDocTemplate* pTemplate=((CCmdToDeviceApp*)AfxGetApp())->pTemplatePL;
		((CMainFrame*)AfxGetMainWnd())->SwitchView(pTemplate,RUNTIME_CLASS(CPLView));
		CMDIChildWnd* pActiveChild=MDIGetActive();
		CDocument* pDocument=pActiveChild->GetActiveDocument();
		((CCmdToDeviceDoc*)pDocument)->UpdateAllViews(NULL);
		((CCmdToDeviceDoc*)pDocument)->uploadPL();
	}*/
}

void CMainFrame::OnRulebind()
{
	// TODO: 在此添加命令处理程序代码
	CDocTemplate* pTemplate=((CCmdToDeviceApp*)AfxGetApp())->pTemplateIf;
	((CMainFrame*)AfxGetMainWnd())->SwitchView(pTemplate,RUNTIME_CLASS(CIfView));
	CMDIChildWnd* pActiveChild=MDIGetActive();
	CDocument* pDocument=pActiveChild->GetActiveDocument();
	((CCmdToDeviceDoc*)pDocument)->queryIfInfo();
}

void CMainFrame::OnBeginservice()
{
	// TODO: 在此添加命令处理程序代码
	CRulesService rsDlg;
	rsDlg.DoModal();
}
