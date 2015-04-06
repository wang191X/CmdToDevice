#pragma once
#include "wsnmp.h"
#include <string>
#include <map>
using namespace std;

class CWsnmpdetail:
	public CWsnmp
{
public:
	CWsnmpdetail(void);
	~CWsnmpdetail(void);
    
	string ifId;
	long setValue;
	map<string,string>ifDescMap;
	map<string,string>ifAclMap;

	int getIfInfo();
	int setAcl();
	int setXacl();
};
