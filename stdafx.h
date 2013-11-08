// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

#ifdef WIN32 //Windows includes
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
