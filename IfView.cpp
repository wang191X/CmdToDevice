// IfView.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "CmdToDeviceDoc.h"

#include "IfView.h"

#include <map>
#include <string>
using namespace std;

#include <boost/lexical_cast.hpp>
using namespace boost;

// CIfView

IMPLEMENT_DYNCREATE(CIfView, CListView)

CIfView::CIfView()
{

}

CIfView::~CIfView()
{
}

BEGIN_MESSAGE_MAP(CIfView, CListView)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CIfView::OnLvnColumnclick)
	ON_COMMAND(ID_RULEBIND_ACL32794, &CIfView::OnRulebindAcl32794)
	ON_COMMAND(ID_RULEBIND_XACL32795, &CIfView::OnRulebindXacl32795)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CIfView 诊断

#ifdef _DEBUG
void CIfView::AssertValid() const
{
	CListView::AssertValid();
}

CCmdToDeviceDoc* CIfView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCmdToDeviceDoc)));
	return (CCmdToDeviceDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CIfView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIfView 消息处理程序

void CIfView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	GetDocument()->pIfView=this;
	GetParentFrame()->SetWindowTextA("接口");

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
	vTableHeader.push_back("id");
	vTableHeader.push_back("ifid");
	vTableHeader.push_back("desc");
	vTableHeader.push_back("acl");
	
	int itemNum=0;

	for ( vIter = vTableHeader.begin( ) ; vIter != vTableHeader.end( ) ; vIter++ )
	{
		listCtrl->InsertColumn(itemNum,*vIter,LVCFMT_LEFT,130,itemNum);
		itemNum++;
	}

	vTableHeader.clear();
}

void CIfView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CCmdToDeviceDoc* pDoc=GetDocument();
	CListCtrl* listCtrl=&GetListCtrl();
	listCtrl->DeleteAllItems();
	int itemCount=listCtrl->GetItemCount();
	CString tmpstr;
	int id=0;
	string ifid,desc,acl;
	typedef map<string,string>::iterator iterMap;
	iterMap iter1,iter2;

	for (iter1=pDoc->wsnmpDetail.ifDescMap.begin();
		iter1!=pDoc->wsnmpDetail.ifDescMap.end();
		++iter1
		)
	{
         ifid=iter1->first;
		 iter2=pDoc->wsnmpDetail.ifAclMap.find(ifid);

		 if (iter2==pDoc->wsnmpDetail.ifAclMap.end())
		 {
			 continue;
		 }

		 desc=iter1->second;
		 acl=iter2->second;
		 ++id;

		 listCtrl->InsertItem(itemCount,"");
		 
		 tmpstr.Format("%d",id);
		 listCtrl->SetItemText(itemCount,0,tmpstr);
         listCtrl->SetItemText(itemCount,1,ifid.c_str());
		 listCtrl->SetItemText(itemCount,2,desc.c_str());
		 listCtrl->SetItemText(itemCount,3,acl.c_str());
	}

//	pDoc->wsnmpDetail.ifAclMap.clear();
//	pDoc->wsnmpDetail.ifDescMap.clear();
}


void CIfView::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nCouter,i;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	CListCtrl* m_FileList=&GetListCtrl();
	if(pNMListView->iSubItem == m_nSortedCol)
	{
		m_bAsc=!m_bAsc;
	}
	else
	{
		m_bAsc=this->GetStyle()&LVS_SORTASCENDING;;
		m_nSortedCol=pNMListView->iSubItem;
	}
	nCouter=m_FileList->GetItemCount();
	for (i=0;i<nCouter;i++)
	{
		CString strText = m_FileList->GetItemText(i,m_nSortedCol);
		m_FileList->SetItemData(i,i);
	}
	m_FileList->SortItems(ListCompare,(DWORD)this);

	*pResult = 0;
}

int CALLBACK CIfView::ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CIfView *sort=(CIfView*)lParamSort;
	CString string1 = sort->GetListCtrl().GetItemText(lParam1,sort->GetSortedCol());
	CString string2= sort->GetListCtrl().GetItemText(lParam2,sort->GetSortedCol());

	if(sort->GetAsc()==TRUE)
	{
		if (string1.GetLength()==string2.GetLength())
		{
			return string1.CompareNoCase(string2);
		}
		else if (string1.GetLength()>string2.GetLength())
		{
			return 1;
		}
		else if (string1.GetLength()<string2.GetLength())
		{
			return -1;
		}
	}
	else
	{
		if (string1.GetLength()==string2.GetLength())
		{
			return string1.CompareNoCase(string2)*(-1);
		}
		else if (string1.GetLength()>string2.GetLength())
		{
			return -1;
		}
		else if (string1.GetLength()<string2.GetLength())
		{
			return 1;
		}
	}

	return 0;
}

void CIfView::OnRulebindAcl32794()
{
	// TODO: 在此添加命令处理程序代码

	if (0==GetListCtrl().GetSelectedCount())
	{
		return;
	}

	int selected=GetListCtrl().GetSelectionMark();
	CString ifId=GetListCtrl().GetItemText(selected,1);
	int ifId1=atoi(ifId);
	string ifIdStr=lexical_cast<string>(ifId1);

	if(IDOK==setBVDlg.DoModal())
	{
		CCmdToDeviceDoc* pDoc=GetDocument();
		pDoc->setAclBind(ifIdStr,(long)setBVDlg.mEtBindValue);
	}
}

void CIfView::OnRulebindXacl32795()
{
	// TODO: 在此添加命令处理程序代码
	if (0==GetListCtrl().GetSelectedCount())
	{
		return;
	}

	int selected=GetListCtrl().GetSelectionMark();
	CString ifId=GetListCtrl().GetItemText(selected,1);
	int ifId1=atoi(ifId);
	string ifIdStr=lexical_cast<string>(ifId1);

	if(IDOK==setBVDlg.DoModal())
	{
		CCmdToDeviceDoc* pDoc=GetDocument();
		pDoc->setXaclBind(ifIdStr,(long)setBVDlg.mEtBindValue);
	}
}

void CIfView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	CMenu menu;
	menu.LoadMenu(IDR_POPUP);
	CMenu* pPopup=menu.GetSubMenu(1);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,pWnd);
}
