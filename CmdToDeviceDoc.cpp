// CmdToDeviceDoc.cpp : CCmdToDeviceDoc 类的实现
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "CmdToDeviceDoc.h"
#include "SessionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCmdToDeviceDoc

IMPLEMENT_DYNCREATE(CCmdToDeviceDoc, CDocument)

BEGIN_MESSAGE_MAP(CCmdToDeviceDoc, CDocument)
END_MESSAGE_MAP()


// CCmdToDeviceDoc 构造/析构

CCmdToDeviceDoc::CCmdToDeviceDoc()
{
	// TODO: 在此添加一次性构造代码
    GetMainFrm();
}

CCmdToDeviceDoc::~CCmdToDeviceDoc()
{
}

BOOL CCmdToDeviceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

void CCmdToDeviceDoc::GetMainFrm()
{
	pMainFrm=(CMainFrame*)AfxGetMainWnd();
}


// CCmdToDeviceDoc 序列化

void CCmdToDeviceDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CCmdToDeviceDoc 诊断

#ifdef _DEBUG
void CCmdToDeviceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCmdToDeviceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCmdToDeviceDoc 命令

int CCmdToDeviceDoc::newSession(void)
{

	int ret=wfclpapi.connect(pMainFrm->sessionDlg.sSession);

	if(ret==-1)
	{
		AfxMessageBox("创建连接失败");
		return -1;
	}
	

	UpdateAllViews(NULL);
	return 0;
}

int CCmdToDeviceDoc::queryACL(void)
{
	/*wfclpapi.vecAcl.clear();
	int ret=wfclpapi.queryACL(pMainFrm->queryACLDlg.sqacl);

	if(ret==-1)
	{
		return -1;
	}
		
	UpdateAllViews(NULL);*/
	return 0;
}

int CCmdToDeviceDoc::queryXACL(void)
{
	/*wfclpapi.vecXacl.clear();
	int ret=wfclpapi.queryXACL(pMainFrm->queryXACLDlg.sqxacl);

	if(ret==-1)
		return -1;

	UpdateAllViews(NULL);*/
	return 0;
}

int CCmdToDeviceDoc::queryPL(void)
{
	/*wfclpapi.vecPL.clear();
	wfclpapi.sqpl.beginId=pMainFrm->queryPLDlg.mETBId;
	wfclpapi.sqpl.endId=pMainFrm->queryPLDlg.mETEId;
	int ret=wfclpapi.queryPL();

	if(ret==-1)
		return -1;

	UpdateAllViews(NULL);*/

	return 0;
}

int CCmdToDeviceDoc::upLoadACL(void)
{
	//wfclpapi.vecAcl.clear();
	//wfclpapi.sacl=pMainFrm->newACLDlg.sacl;
	////int ret=wfclpapi.uploadACL(pMainFrm->newACLDlg.sacl);
	//int ret=wfclpapi.uploadACL();

	//if(ret==-1)
	//{
	//	AfxMessageBox("不成功");
	//	return -1;
	//}
	//else
	//{
	//	AfxMessageBox("成功");
	//}
	//	
	//UpdateAllViews(NULL);

	return 0;
}

int CCmdToDeviceDoc::uploadXACL(void)
{
	//wfclpapi.vecXacl.clear();
	//wfclpapi.sxacl=pMainFrm->newXACLDlg.sxacl;
	////int ret=wfclpapi.uploadACL(pMainFrm->newACLDlg.sacl);
	//int ret=wfclpapi.uploadXACL();

	//if(ret==-1)
	//{
	//	AfxMessageBox("不成功");
	//	return -1;
	//}
	//else
	//{
	//	AfxMessageBox("成功");
	//}

	//UpdateAllViews(NULL);
	return 0;
}

int CCmdToDeviceDoc::uploadPL(void)
{
	/*wfclpapi.vecPL.clear();
	wfclpapi.spl=pMainFrm->newPLDlg.spl;
	int ret=wfclpapi.uploadPL();

	if(ret==-1)
	{
		AfxMessageBox("不成功");
		return -1;
	}
	else
	{
		AfxMessageBox("成功");
	}

	UpdateAllViews(NULL);*/
	return 0;
}

int CCmdToDeviceDoc::removeXACL(int xId)
{
	wfclpapi.vecXacl.clear();
	int ret=wfclpapi.removeXACL(xId);

	if(ret==-1)
		return -1;
	
	UpdateAllViews(NULL);
	return 0;
}

int CCmdToDeviceDoc::removeACL(int ruleId)
{
		wfclpapi.vecAcl.clear();
	int ret=wfclpapi.removeACL(ruleId);
	
	if(ret==-1)
		return -1;
	
	UpdateAllViews(NULL);
	return 0;
}

int CCmdToDeviceDoc::removePL(int plId)
{
		wfclpapi.vecPL.clear();
	int ret=wfclpapi.removePL(plId);

	if(ret==-1)
		return -1;

	UpdateAllViews(NULL);
	return 0;
}

int CCmdToDeviceDoc::queryIfInfo()
{
	wsnmpDetail.ifAclMap.clear();
	wsnmpDetail.ifDescMap.clear();
	int ret=wsnmpDetail.getIfInfo();

	if(ret==-1)
		return -1;

	UpdateAllViews(NULL);

	return 0;
}

int CCmdToDeviceDoc::setAclBind(string& ifId,long setValue)
{
	wsnmpDetail.ifId=ifId;
	wsnmpDetail.setValue=setValue;
	wsnmpDetail.setAcl();

	return 0;
}

int CCmdToDeviceDoc::setXaclBind(string& ifId,long setValue)
{
	wsnmpDetail.ifId=ifId;
	wsnmpDetail.setValue=setValue;
	wsnmpDetail.setXacl();

	return 0;
}