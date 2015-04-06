// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*****************************/
/*send one acl in normal mode*/
/*****************************/

#include "fclpapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WINSOCK2.h"

char server_name[128] = {0};
char user_name[128] = {0};
char password[128] = {0};
FCLP_TRANSMIT_MODE mode = FCLP_OVER_TCP;
FCLP_UINT8 version = FCLP_VERSION_3;
int async = 0;

void main()
{
	FCLP_HANDLE acl = FCLP_NULL;  
	FCLPAPI_STATUS ret = FCLPAPI_OK;
	FCLP_HANDLE session = FCLP_NULL;

	if(Fclp_Startup(FCLP_VERSION_3) != FCLPAPI_OK)
	{
		printf("check fclp environment ... \n");
		return;
	}

	printf("connecting to server ... \n");
	strcpy((char *)server_name, "10.10.23.155");
	strcpy((char *)user_name, "usr");
	strcpy((char *)password, "name");

	ret = Fclp_Session_Create((FCLP_UINT8 *)server_name, 
		FCLP_DEFAULT_PORT, mode,
		(FCLP_UINT8 *)user_name, 
		(FCLP_UINT8 *)password,
		 &session);

	if (ret!=FCLPAPI_OK)
	{
		printf("Session_Create result %d\n",ret);
		return;
	}

	printf("OK!\n");
					


	ret = Fclp_Acl_Create(&acl);
	if (ret!=FCLPAPI_OK)
	{
		printf("Acl_Create result %d\n",ret);
		return;
	}

	/*set five parameter */
	Fclp_Acl_SetProtocol(acl, FCLP_ACL_PROTOCOL_TCP);
	//Fclp_Acl_SetSourceAddress(acl, 0xa000000, 0xffffffff);
	//Fclp_Acl_SetDestAddress(acl, 0xb000000, 0xffffffff);
	//Fclp_Acl_SetDestPort(acl, 100, 0xffff);
	//Fclp_Acl_SetSourcePort(acl, 100, 0xffff);
	Fclp_Acl_SetSourceAddress(acl, 0x72000000, 0xff000000);
	Fclp_Acl_SetDestAddress(acl, 0x0000000, 0x0);
	Fclp_Acl_SetDestPort(acl, 00, 0x0);
	Fclp_Acl_SetSourcePort(acl, 00, 0x0);

	/*set other parameter*/
	Fclp_Acl_SetId(acl,2222);
	Fclp_Acl_SetStatic(acl, FCLP_TRUE);
	Fclp_Acl_SetRedirectEnabled(acl, FCLP_TRUE);
	Fclp_Acl_SetRedirectTarget(acl, FCLP_TRUE,1);
	

	if (async)
		//ret = Fclp_Acl_AsyncAdd(session, acl);
		ret = Fclp_Acl_AsyncRemove(session, acl);
	else
		ret = Fclp_Acl_Add(session, acl, 2000);
		//ret = Fclp_Acl_Remove(session, acl, 2000);

	if (ret != FCLPAPI_OK)
	{
		printf("result: %d\n",ret);
	}

	printf("finished.\n");
	Fclp_Acl_Destroy(acl);
	Fclp_Session_Destroy(session);
	Fclp_Cleanup();
	return;
}