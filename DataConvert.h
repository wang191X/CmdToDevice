#pragma once

#include <string>
using namespace std;

class CDataConvert
{
public:
	CDataConvert(void);
	~CDataConvert(void);
	string arrayToHexStr(UCHAR* p,int len);
	int hexStrToint(CString& hexStr);

};
