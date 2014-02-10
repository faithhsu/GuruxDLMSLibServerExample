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
#pragma once

#include "targetver.h"

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

#if defined(_WIN32) || defined(_WIN64)//Windows includes
    #include <tchar.h>
    #include <conio.h>
	#include <Winsock.h> //Add support for sockets	
	#include <time.h>
	#include <process.h>//Add support for threads
#else //Linux includes.
	#define closesocket close
	#include <pthread.h>
	#include <termios.h>
	#include <sys/types.h>
	#include <sys/socket.h> //Add support for sockets
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <string.h>
	#include <sys/time.h>
	#include <errno.h>
#endif


// TODO: reference additional headers your program requires here
