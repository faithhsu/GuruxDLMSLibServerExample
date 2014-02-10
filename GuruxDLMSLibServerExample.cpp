//
// --------------------------------------------------------------------------
//  Gurux Ltd
// 
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License 
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2. 
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#include "stdafx.h"
#include "GXDLMSServerSN.h"
#include "GXDLMSServerLN.h"
#include "GXDLMSServerSN_47.h"
#include "GXDLMSServerLN_47.h"

#if defined(_WIN32) || defined(_WIN64)//Windows includes
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

