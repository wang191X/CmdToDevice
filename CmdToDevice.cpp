﻿// CmdToDevice.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "CmdToDeviceDoc.h"
#include "CmdToDeviceView.h"
#include "SessionView.h"
#include "AclView.h"
#include "XACLView.h"
#include "PLView.h"
#include "IfView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCmdToDeviceApp

BEGIN_MESSAGE_MAP(CCmdToDeviceApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CCmdToDeviceApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CCmdToDeviceApp 构造

CCmdToDeviceApp::CCmdToDeviceApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CCmdToDeviceApp 对象

CCmdToDeviceApp theApp;

// CCmdToDeviceApp 初始化

BOOL CCmdToDeviceApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)
	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	//CMultiDocTemplate* pDocTemplate;
	//pDocTemplate = new CMultiDocTemplate(IDR_CmdToDeviceTYPE,
	//	RUNTIME_CLASS(CCmdToDeviceDoc),
	//	RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
	//	RUNTIME_CLASS(CCmdToDeviceView));
	//if (!pDocTemplate)
	//	return FALSE;
	//AddDocTemplate(pDocTemplate);

	mTemplateSession = new CMultiDocTemplate(IDR_CmdToDeviceTYPE,
		RUNTIME_CLASS(CCmdToDeviceDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CSessionView));
	if (!mTemplateSession)
		return FALSE;
	AddDocTemplate(mTemplateSession);

	//pTemplateACL = new CMultiDocTemplate(IDR_CmdToDeviceTYPE,
	//	RUNTIME_CLASS(CCmdToDeviceDoc),
	//	RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
	//	RUNTIME_CLASS(CAclView));
	//if (!pTemplateACL)
	//	return FALSE;

	//pTemplateXACL = new CMultiDocTemplate(IDR_CmdToDeviceTYPE,
	//	RUNTIME_CLASS(CCmdToDeviceDoc),
	//	RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
	//	RUNTIME_CLASS(CXACLView));
	//if (!pTemplateXACL)
	//	return FALSE;

	//	pTemplatePL = new CMultiDocTemplate(IDR_CmdToDeviceTYPE,
	//	RUNTIME_CLASS(CCmdToDeviceDoc),
	//	RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
	//	RUNTIME_CLASS(CPLView));
	//if (!pTemplatePL)
	//	return FALSE;

	pTemplateIf = new CMultiDocTemplate(IDR_CmdToDeviceTYPE,
		RUNTIME_CLASS(CCmdToDeviceDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CIfView));
	if (!pTemplateIf)
		return FALSE;

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 MDI 应用程序中，这应在设置 m_pMainWnd 之后立即发生


	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CCmdToDeviceApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CCmdToDeviceApp 消息处理程序


int CCmdToDeviceApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete pTemplateACL;
	delete pTemplateXACL;
	delete pTemplatePL;

	return CWinApp::ExitInstance();
}
