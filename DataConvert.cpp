#include "StdAfx.h"
#include "DataConvert.h"
#include <sstream>
using namespace std;

#include <boost/format.hpp>
using namespace boost;

CDataConvert::CDataConvert(void)
{
}

CDataConvert::~CDataConvert(void)
{
}



string CDataConvert::arrayToHexStr(UCHAR* p,int len)
{
	string retStr("");
	format fmt("%02X");

	for (int i=0;i!=len;++i)
	{
		fmt%((int)p[i]);
		string tmp=fmt.str();
		retStr+=tmp+" ";
	}

	return retStr;
}

int CDataConvert::hexStrToint(CString& hexStr)
{
	stringstream ss;
	ss<<hex<<hexStr;
	int x;
	ss>>x;
	return x;
}

