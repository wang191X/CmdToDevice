// AclView.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "CmdToDeviceDoc.h"
#include "AclView.h"

#include <vector>
#include "WFCLPAPI.h"
#include "DataConvert.h"
#include <string>

// CAclView

IMPLEMENT_DYNCREATE(CAclView, CListView)

CAclView::CAclView()
{

}

CAclView::~CAclView()
{
}

BEGIN_MESSAGE_MAP(CAclView, CListView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LIST_32791, &CAclView::OnList32791)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CAclView::OnLvnColumnclick)
END_MESSAGE_MAP()


// CAclView 诊断

#ifdef _DEBUG
void CAclView::AssertValid() const
{
	CListView::AssertValid();
}

CCmdToDeviceDoc* CAclView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCmdToDeviceDoc)));
	return (CCmdToDeviceDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CAclView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAclView 消息处理程序

void CAclView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	GetDocument()->pAclView=this;
	// TODO: 在此添加专用代码和/或调用基类
	GetParentFrame()->SetWindowTextA("查询ACL结果");

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
	vTableHeader.push_back("group");
	vTableHeader.push_back("action");
	
	int itemNum=0;

	for ( vIter = vTableHeader.begin( ) ; vIter != vTableHeader.end( ) ; vIter++ )
	{
		listCtrl->InsertColumn(itemNum,*vIter,LVCFMT_LEFT,130,itemNum);
		itemNum++;
	}

	vTableHeader.clear();

	//listCtrl->InsertItem(0,"");
	//listCtrl->SetItemText(0,0,"20");
	//listCtrl->SetItemText(0,1,"30");
}

void CAclView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CCmdToDeviceDoc* pDoc=GetDocument();
	CListCtrl* listCtrl=&GetListCtrl();
	listCtrl->DeleteAllItems();
	int itemCount=listCtrl->GetItemCount();
	CString tmpStr;
	CDataConvert dc;
	typedef vector<SACL>::iterator iterAcl;

	for(iterAcl iter=pDoc->wfclpapi.vecAcl.begin();iter!=pDoc->wfclpapi.vecAcl.end();++iter,++itemCount)
	{
		SACL sacl=*iter;
		listCtrl->InsertItem(itemCount,"");

		if(sacl.id!=0)
		{
			tmpStr.Format("%d",sacl.id);
			listCtrl->SetItemText(itemCount,0,tmpStr);
		}

		/*if(sacl.group!=0)
		{
			tmpStr.Format("%d",sacl.group);
			listCtrl->SetItemText(itemCount,1,tmpStr);
		}

		if(sacl.action==1)
		{
			listCtrl->SetItemText(itemCount,2,"阻断");
		}
		else if(sacl.action==2)
		{
			listCtrl->SetItemText(itemCount,2,"通过");
		}*/

	}

	int aclCount=pDoc->wfclpapi.vecAcl.size();
	CString tmp;
	tmp.Format("%d",aclCount);
	tmp="查询ACL结果("+tmp+"条)";
	GetParentFrame()->SetWindowTextA(tmp);

	//pDoc->wfclpapi.vecAcl.clear();
}

void CAclView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	//if (0==GetListCtrl().GetSelectedCount())
	//{
		CMenu menu;
		menu.LoadMenu(IDR_POPUP);
		CMenu* pPopup=menu.GetSubMenu(0);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,pWnd);
	//}
}

void CAclView::OnList32791()
{
	// TODO: 在此添加命令处理程序代码
	if (0==GetListCtrl().GetSelectedCount())
	{
		return;
	}

	int selected=GetListCtrl().GetSelectionMark();
	CString ruleId=GetListCtrl().GetItemText(selected,0);
	int ruleId1=atoi(ruleId);
	int ret = GetDocument()->removeACL(ruleId1);

	if (ret!=-1)
	{
		GetListCtrl().DeleteItem(selected);
		MessageBox("成功");
	}
	else
	{
		MessageBox("失败");
	}
}

void CAclView::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
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

int CALLBACK CAclView::ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CAclView *sort=(CAclView*)lParamSort;
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