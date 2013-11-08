// GuruxDLMSLibServerExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GXDLMSServerSN.h"
#include "GXDLMSServerLN.h"
#include "GXDLMSServerSN_47.h"
#include "GXDLMSServerLN_47.h"

#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main( int argc, char* argv[] )
#endif
{	
	//Create Network media component and start listen events.
	//4059 is Official DLMS port.
    ///////////////////////////////////////////////////////////////////////
    //Create Gurux DLMS server component for Short Name and start listen events.
    CGXDLMSServerSN SNServer;
    if (SNServer.Init(4060) != 0)
    {
    	return -1;
    }
    printf("Short Name DLMS Server in port 4060.\r\n");
    ///////////////////////////////////////////////////////////////////////
    //Create Gurux DLMS server component for Short Name and start listen events.
    CGXDLMSServerLN LNServer;
    if (LNServer.Init(4061) != 0)
    {
        return -1;
    }
    printf("Logical Name DLMS Server in port 4061.\r\n");
    ///////////////////////////////////////////////////////////////////////
    //Create Gurux DLMS server component for Short Name and start listen events.
    CGXDLMSServerSN_47 SN_47Server;
    if (SN_47Server.Init(4062) != 0)
    {
    	return -1;
    }
    printf("Short Name DLMS Server with IEC 62056-47 in port 4062.\r\n");
    ///////////////////////////////////////////////////////////////////////
    //Create Gurux DLMS server component for Short Name and start listen events.
    CGXDLMSServerLN_47 LN_47Server;
    if (LN_47Server.Init(4063) != 0)
    {
    	return -1;
    }
    printf("Logical Name DLMS Server with IEC 62056-47 in port 4063.\r\n");
#if _MSC_VER > 1000
    while (_getche() != '\r');
#else
    while (getchar() != 10);
#endif
	return 0;
}

