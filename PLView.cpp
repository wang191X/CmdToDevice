// PLView.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdToDevice.h"
#include "CmdToDeviceDoc.h"
#include "PLView.h"
#include "DataConvert.h"

#include <vector>

// CPLView

IMPLEMENT_DYNCREATE(CPLView, CListView)

CPLView::CPLView()
{

}

CPLView::~CPLView()
{
}

BEGIN_MESSAGE_MAP(CPLView, CListView)
	ON_COMMAND(ID_PAYLOAD_delete, &CPLView::OnPayloaddelete)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CPLView::OnLvnColumnclick)
END_MESSAGE_MAP()


// CPLView 诊断

#ifdef _DEBUG
void CPLView::AssertValid() const
{
	CListView::AssertValid();
}

CCmdToDeviceDoc* CPLView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCmdToDeviceDoc)));
	return (CCmdToDeviceDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CPLView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPLView 消息处理程序
void CPLView::OnInitialUpdate()
{
	GetParentFrame()->SetWindowTextA("查询PayLoad结果");

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
	vTableHeader.push_back("block");
	vTableHeader.push_back("value");
	vTableHeader.push_back("mask");
	int itemNum=0;

	for ( vIter = vTableHeader.begin( ) ; vIter != vTableHeader.end( ) ; vIter++ )
	{
		listCtrl->InsertColumn(itemNum,*vIter,LVCFMT_LEFT,100,itemNum);
		itemNum++;
	}

	listCtrl->SetColumnWidth(2,1200);
		listCtrl->SetColumnWidth(3,1200);
	
	vTableHeader.clear();

	CListView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}


void CPLView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CCmdToDeviceDoc* pDoc=GetDocument();
	CListCtrl* listCtrl=&GetListCtrl();
	listCtrl->DeleteAllItems();
	int itemCount=listCtrl->GetItemCount();
	CDataConvert dc;
	CString tmpStr;
	typedef vector<SPL>::iterator iterPL;

	for(iterPL iter=pDoc->wfclpapi.vecPL.begin();iter!=pDoc->wfclpapi.vecPL.end();++iter,++itemCount)
	{
		SPL spl=*iter;
		listCtrl->InsertItem(itemCount,"");

		if(spl.id!=0)
		{
			tmpStr.Format("%d",spl.id);
			listCtrl->SetItemText(itemCount,0,tmpStr);
		}

		tmpStr.Format("%d",spl.block);
		listCtrl->SetItemText(itemCount,1,tmpStr);

		string keyValue=dc.arrayToHexStr(spl.keyValue,sizeof(spl.keyValue));
		listCtrl->SetItemText(itemCount,2,keyValue.c_str());

		string keyMask=dc.arrayToHexStr(spl.keyMask,sizeof(spl.keyMask));
		listCtrl->SetItemText(itemCount,3,keyMask.c_str());
	}

	int aclCount=pDoc->wfclpapi.vecPL.size();
	CString tmp;
	tmp.Format("%d",aclCount);
	tmp="查询PL结果("+tmp+"条)";
	GetParentFrame()->SetWindowTextA(tmp);

	//pDoc->wfclpapi.vecPL.clear();
}

void CPLView::OnPayloaddelete()
{
	// TODO: 在此添加命令处理程序代码
	if (0==GetListCtrl().GetSelectedCount())
	{
		return;
	}

	int selected=GetListCtrl().GetSelectionMark();
	CString plId=GetListCtrl().GetItemText(selected,0);
	int plId1=atoi(plId);
	int ret = GetDocument()->removePL(plId1);

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

void CPLView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	CMenu menu;
	menu.LoadMenu(IDR_POPUP);
	CMenu* pPopup=menu.GetSubMenu(2);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,pWnd);
}

void CPLView::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
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


int CALLBACK CPLView::ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CPLView *sort=(CPLView*)lParamSort;
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