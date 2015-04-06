// CmdToDeviceDoc.h : CCmdToDeviceDoc 类的接口
//


#pragma once

#include "WFCLPAPI.h"
#include "Wsnmpdetail.h"
#include "MainFrm.h"

class CAclView;
class CSessionView;
class CIfView;

class CCmdToDeviceDoc : public CDocument
{
protected: // 仅从序列化创建
	CCmdToDeviceDoc();
	DECLARE_DYNCREATE(CCmdToDeviceDoc)

// 属性
public:
	CWFCLPAPI wfclpapi;
	CWsnmpdetail wsnmpDetail;
    CMainFrame* pMainFrm;
	CAclView* pAclView;
	CSessionView* pSessionView;
	CIfView* pIfView;

private:
	void GetMainFrm();

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public: 
	virtual ~CCmdToDeviceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	int newSession(void);
	int queryACL(void);
	int queryXACL(void);
	int queryPL(void);
	int upLoadACL(void);
	int uploadXACL(void);
	int uploadPL(void);
	int removeXACL(int xId);
	int removeACL(int ruleId);
	int removePL(int plId);
	int queryIfInfo();
	int setAclBind(string& ifId,long setValue);
	int setXaclBind(string& ifId,long setValue);
};

