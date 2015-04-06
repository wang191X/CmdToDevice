// XACLView.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "CmdToDeviceDoc.h"
#include "XACLView.h"
#include <bitset>
#include <vector>

// CXACLView

IMPLEMENT_DYNCREATE(CXACLView, CListView)

CXACLView::CXACLView()
{

}

CXACLView::~CXACLView()
{
}

BEGIN_MESSAGE_MAP(CXACLView, CListView)
	ON_COMMAND(ID_XACL_delete, &CXACLView::OnXacldelete)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CXACLView::OnLvnColumnclick)
END_MESSAGE_MAP()


// CXACLView 诊断

#ifdef _DEBUG
void CXACLView::AssertValid() const
{
	CListView::AssertValid();
}

CCmdToDeviceDoc* CXACLView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCmdToDeviceDoc)));
	return (CCmdToDeviceDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CXACLView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CXACLView 消息处理程序

void CXACLView::OnInitialUpdate()
{
	GetParentFrame()->SetWindowTextA("查询XACL结果");

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
	vTableHeader.push_back("mpls");
	vTableHeader.push_back("size");
	vTableHeader.push_back("uaprsf");
	vTableHeader.push_back("payloadid");
	vTableHeader.push_back("redirection");
	
	int itemNum=0;

	for ( vIter = vTableHeader.begin( ) ; vIter != vTableHeader.end( ) ; vIter++ )
	{
		listCtrl->InsertColumn(itemNum,*vIter,LVCFMT_LEFT,100,itemNum);
		itemNum++;
	}

	vTableHeader.clear();

	CListView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}

void CXACLView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CCmdToDeviceDoc* pDoc=GetDocument();
	CListCtrl* listCtrl=&GetListCtrl();
	listCtrl->DeleteAllItems();
	int itemCount=listCtrl->GetItemCount();
	CString tmpStr;
	typedef vector<SXACL>::iterator iterXacl;

	for(iterXacl iter=pDoc->wfclpapi.vecXacl.begin();iter!=pDoc->wfclpapi.vecXacl.end();++iter,++itemCount)
	{
		SXACL sxacl=*iter;
		listCtrl->InsertItem(itemCount,"");

		if(sxacl.id!=0)
		{
			tmpStr.Format("%d",sxacl.id);
			listCtrl->SetItemText(itemCount,0,tmpStr);
		}

		if(sxacl.group!=0)
		{
			tmpStr.Format("%d",sxacl.group);
			listCtrl->SetItemText(itemCount,1,tmpStr);
		}

		if(sxacl.action==1)
		{
			listCtrl->SetItemText(itemCount,2,"阻断");
		}
		else if(sxacl.action==2)
		{
			listCtrl->SetItemText(itemCount,2,"通过");
		}

		tmpStr.Format("%d",sxacl.mpls);
		listCtrl->SetItemText(itemCount,3,tmpStr);

		tmpStr.Format("%d",sxacl.frameLen);
		listCtrl->SetItemText(itemCount,4,tmpStr);

		if(sxacl.tcp!=0)
		{
			bitset<6>bs(sxacl.tcp);
			tmpStr="";

			if (bs[5]==1)
			{
				tmpStr+="urg;";
			}
			if (bs[4]==1)
			{
				tmpStr+="ack;";
			}
			if (bs[3]==1)
			{
				tmpStr+="psh;";
			}
			if (bs[2]==1)
			{
				tmpStr+="rst;";
			}
			if (bs[1]==1)
			{
				tmpStr+="syn;";
			}
			if (bs[0]==1)
			{
				tmpStr+="fin";
			}

			listCtrl->SetItemText(itemCount,5,tmpStr);
		}

		if(sxacl.PLId!=0)
		{
			tmpStr.Format("%d",sxacl.PLId);
			listCtrl->SetItemText(itemCount,6,tmpStr);
		}

		if (sxacl.outPlace==1)
		{
			tmpStr.Format("%d_%d",sxacl.card,sxacl.outPort);
			listCtrl->SetItemText(itemCount,7,tmpStr);
		}
		else if (sxacl.outPlace==2)
		{
			tmpStr.Format("FlowComb%d",sxacl.flowId);
			listCtrl->SetItemText(itemCount,7,tmpStr);
		}

	}

	int aclCount=pDoc->wfclpapi.vecXacl.size();
	CString tmp;
	tmp.Format("%d",aclCount);
	tmp="查询XACL结果("+tmp+"条)";
	GetParentFrame()->SetWindowTextA(tmp);

	//pDoc->wfclpapi.vecXacl.clear();
}

void CXACLView::OnXacldelete()
{
	// TODO: 在此添加命令处理程序代码
	if (0==GetListCtrl().GetSelectedCount())
	{
		return;
	}

	int selected=GetListCtrl().GetSelectionMark();
	CString xId=GetListCtrl().GetItemText(selected,0);
	int xId1=atoi(xId);
	int ret = GetDocument()->removeXACL(xId1);

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

void CXACLView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	CMenu menu;
	menu.LoadMenu(IDR_POPUP);
	CMenu* pPopup=menu.GetSubMenu(3);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,pWnd);
}


void CXACLView::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
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


int CALLBACK CXACLView::ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CXACLView *sort=(CXACLView*)lParamSort;
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