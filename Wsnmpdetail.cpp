#include "StdAfx.h"
#include "Wsnmpdetail.h"



CWsnmpdetail::CWsnmpdetail(void)
{
}

CWsnmpdetail::~CWsnmpdetail(void)
{
}

int CWsnmpdetail::getIfInfo()
{
	ip="10.10.23.155";
	oidStr="1.3.6.1.2.1.31.1.1.1.1";  //端口描述
	snmpWalk();
	ifDescMap=resultMap;
	resultMap.clear();
	oidStr="1.3.6.1.4.1.3902.1017.3.7.1.4";  //端口acl绑定情况
	snmpWalk();
	ifAclMap=resultMap;
	resultMap.clear();

    if (ifDescMap.size()==0&&ifAclMap.size()==0)
    {
		return -1;
    }

	return 0;
}

int CWsnmpdetail::setAcl()
{
	ip="10.10.23.155";
	oidStr="1.3.6.1.4.1.3902.1017.3.7.1.4."+ifId;  //端口acl绑定情况
	aclValue=setValue;
	snmpSet();

	return 0;
}

int CWsnmpdetail::setXacl()
{
	ip="10.10.23.155";
	oidStr="1.3.6.1.4.1.3902.1017.3.7.1.5."+ifId;  //端口xacl绑定情况
	aclValue=setValue;
	snmpSet();

	return 0;
}
