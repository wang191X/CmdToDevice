#pragma once

#include "snmp_pp/snmp_pp.h"
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <map>
using namespace std;

class CWsnmp
{
public:
	CWsnmp(void);
	virtual ~CWsnmp(void);
protected:
	string oidStr;
	string ip;
	long aclValue;
	map<string,string>resultMap;

	virtual int snmpWalk();
	virtual int snmpSet();
	int determine_vb(SmiUINT32 val, Vb &vb);
};
