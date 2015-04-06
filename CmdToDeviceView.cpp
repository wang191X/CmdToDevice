// CmdToDeviceView.cpp : CCmdToDeviceView 类的实现
//

#include "stdafx.h"
#include "CmdToDevice.h"

#include "CmdToDeviceDoc.h"
#include "CmdToDeviceView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCmdToDeviceView

IMPLEMENT_DYNCREATE(CCmdToDeviceView, CView)

BEGIN_MESSAGE_MAP(CCmdToDeviceView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCmdToDeviceView 构造/析构

CCmdToDeviceView::CCmdToDeviceView()
{
	// TODO: 在此处添加构造代码

}

CCmdToDeviceView::~CCmdToDeviceView()
{
}

BOOL CCmdToDeviceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCmdToDeviceView 绘制

void CCmdToDeviceView::OnDraw(CDC* /*pDC*/)
{
	CCmdToDeviceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CCmdToDeviceView 打印

BOOL CCmdToDeviceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCmdToDeviceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCmdToDeviceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCmdToDeviceView 诊断

#ifdef _DEBUG
void CCmdToDeviceView::AssertValid() const
{
	CView::AssertValid();
}

void CCmdToDeviceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCmdToDeviceDoc* CCmdToDeviceView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCmdToDeviceDoc)));
	return (CCmdToDeviceDoc*)m_pDocument;
}
#endif //_DEBUG


// CCmdToDeviceView 消息处理程序
