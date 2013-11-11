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
#include "GXNet.h"

CGXNet::CGXNet(void)
{	
	basic_string<char> name;
	Init(GX_NW_TCPIP, name, 0);
}

CGXNet::CGXNet(enum GX_NW_TYPE protocol, int port)
{		
	basic_string<char> name;
	Init(protocol, name, port);
	m_IsServer = true;
}

CGXNet::CGXNet(enum GX_NW_TYPE protocol, basic_string<char> hostName, int port)
{
	Init(protocol, hostName, port);
}

void CGXNet::Init(enum GX_NW_TYPE protocol, basic_string<char>& hostName, int port)
{
	m_IsServer = false;	
	m_ReceiveBuffPos = 0;
	m_Synchronous = false;
	m_Trace = GX_TRACE_LEVEL_OFF;
	m_ServerSocket = m_Socket = -1;
	m_BytesSent = m_BytesReceived = 0;
	SetProtocol(protocol);  
	SetHostName(hostName);
	SetPort(port);
}

CGXNet::~CGXNet(void)
{
}

void CGXNet::NotifyPropertyChanged(basic_string<char>& info)
{
	CPropertyChangedEventArgs arg(info);
	for (vector<IGXMediaListener*>::iterator it = m_MediaListeners.begin(); 
		it != m_MediaListeners.end(); ++it)
    {
        (*it)->OnPropertyChanged(this, arg);
    }  
}

void CGXNet::NotifyClientConnected(CConnectionEventArgs& e)
{
	for (vector<IGXNetListener*>::iterator it = m_NetListeners.begin(); 
			it != m_NetListeners.end(); ++it)
    {
        (*it)->OnClientConnected(this, e);
    }
    if (m_Trace >= (int) GX_TRACE_TYPES_INFO)
    {
		CTraceEventArgs arg(GX_TRACE_TYPES_INFO, "Client connected.");
		for (vector<IGXMediaListener*>::iterator it = m_MediaListeners.begin(); 
			it != m_MediaListeners.end(); ++it)
        {
            (*it)->OnTrace(this, arg);
        }            
    }
}

void CGXNet::NotifyClientDisconnected(CConnectionEventArgs& e)
{
	for (vector<IGXNetListener*>::iterator it = m_NetListeners.begin(); 
			it != m_NetListeners.end(); ++it)
    {
        (*it)->OnClientDisconnected(this, e);
    }
    if (m_Trace >= (int) GX_TRACE_TYPES_INFO)
    {
		CTraceEventArgs arg(GX_TRACE_TYPES_INFO, "Client disconnected.");	
		for (vector<IGXMediaListener*>::iterator it = m_MediaListeners.begin(); 
			it != m_MediaListeners.end(); ++it)
        {
            (*it)->OnTrace(this, arg);
        }            
    }
}

void CGXNet::NotifyError(basic_string<char>& ex)
{
	for (vector<IGXMediaListener*>::iterator it = m_MediaListeners.begin(); 
		it != m_MediaListeners.end(); ++it)
    {
		(*it)->OnError(this, ex);
		if (m_Trace >= (int) GX_TRACE_TYPES_ERROR)
        {
			CTraceEventArgs e(GX_TRACE_TYPES_ERROR, ex);
            (*it)->OnTrace(this, e);
        }
    }
}

void CGXNet::NotifyReceived(CReceiveEventArgs& e)
{	
	for (vector<IGXMediaListener*>::iterator it = m_MediaListeners.begin(); 
		it != m_MediaListeners.end(); ++it)
    {
        (*it)->OnReceived(this, e);
    }
}

void CGXNet::NotifyTrace(CTraceEventArgs& e)
{
	for (vector<IGXMediaListener*>::iterator it = m_MediaListeners.begin(); 
		it != m_MediaListeners.end(); ++it)
    {
        (*it)->OnTrace(this, e);
    }
}

void CGXNet::NotifyMediaStateChange(GX_MEDIA_STATE_CHANGE state)
{
	CMediaStateEventArgs ms(state);
	basic_string<char> str;
	switch(state)
	{
		case GX_MEDIA_STATE_CHANGE_CLOSED:
			str = "Closed";
		break;
		case GX_MEDIA_STATE_CHANGE_OPEN:
			str = "Open";
		break;
		case GX_MEDIA_STATE_CHANGE_OPENING:
			str = "Opening";
		break;
		case GX_MEDIA_STATE_CHANGE_CLOSING:
			str = "Closing";
		break;
	}
	CTraceEventArgs te(GX_TRACE_TYPES_INFO, str);
	for (vector<IGXMediaListener*>::iterator it = m_MediaListeners.begin(); 
	it != m_MediaListeners.end(); ++it)
    {
        if (m_Trace >= (int) GX_TRACE_TYPES_ERROR)
        {
            (*it)->OnTrace(this, te);
        }
        (*it)->OnMediaStateChange(this, ms);
    }
}


void ListenerThread(void* pVoid)
{
	CGXNet* pNet = (CGXNet*) pVoid;
	sockaddr_in add = {0};
	int ret;
#ifdef WIN32
	int len;
	int AddrLen = sizeof(add);
#else
	socklen_t len;
	socklen_t AddrLen = sizeof(add);
#endif
    struct sockaddr_in client; 
    memset(&client,0,sizeof(client));	
	//Get buffer data
	basic_string<char> senderInfo;
	if (pNet->IsServer())
	{
		while(pNet->IsOpen())
		{
			len = sizeof(client);
			senderInfo.clear();
			pNet->m_Socket = accept(pNet->m_ServerSocket,(struct sockaddr*)&client, &len); 
			if (pNet->m_Socket != -1)
			{
				if ((ret = getpeername(pNet->m_Socket, (sockaddr*) &add, &AddrLen)) == 1)
				{
					//Notify error.
					break;
				}
				senderInfo = inet_ntoa(add.sin_addr);
				senderInfo.append(":");
				char tmp[10];
#if _MSC_VER > 1000				
				_ltoa_s(add.sin_port, tmp, 10, 10);
#else
				sprintf(tmp, "%d", add.sin_port);
#endif
				senderInfo.append(tmp);
				while(pNet->IsOpen())
				{
					//If client is left wait for next client.
					if(pNet->m_Socket != -1)
					{
						if ((ret = recv(pNet->m_Socket, (char*) 
								pNet->m_Receivebuff + pNet->m_ReceiveBuffPos, 
								sizeof(pNet->m_Receivebuff) - pNet->m_ReceiveBuffPos, 0)) == -1)
						{
							//Notify error.
							break;
						}
						//If client is closed the connection.
						if (ret == 0)
						{
							break;
						}
						if (pNet->GetSynchronous())
						{
							pNet->m_ReceiveBuffPos += ret;
						}
						else
						{
							pNet->m_ReceiveBuffPos = 0;
							CReceiveEventArgs e(pNet->m_Receivebuff, ret, senderInfo);
							pNet->NotifyReceived(e);
						}
					}
				}
			}
		}		
	}
	else
	{
		while(pNet->IsOpen())
		{
			if ((ret = recv(pNet->m_Socket, (char*) 
				pNet->m_Receivebuff + pNet->m_ReceiveBuffPos, 
				sizeof(pNet->m_Receivebuff) - pNet->m_ReceiveBuffPos, 0)) == -1)
			{
				//Notify error.
				return;
			}
			if (pNet->GetSynchronous())
			{
				pNet->m_ReceiveBuffPos += ret;
			}
			else
			{
				pNet->m_ReceiveBuffPos = 0;
				CReceiveEventArgs e(pNet->m_Receivebuff, ret, ""); //TODO:
				pNet->NotifyReceived(e);
			}
		}
	}
}

void * UnixListenerThread(void * pVoid)
{
	ListenerThread(pVoid);
	return NULL;
}


int CGXNet::Open()
{
#ifdef WIN32
	WSADATA wsaData; 	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// Tell the user that we could not find a usable WinSock DLL.
		return 1;
	}
#endif
	int ret;
	if((ret = Close()) != 0)
	{
		return ret;
	}
	NotifyMediaStateChange(GX_MEDIA_STATE_CHANGE_OPENING);
	if (m_IsServer) //If server.
	{
		m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_ServerSocket == -1) //If failed.
		{
			return ShowError("socket creation.");
		}
		if (m_Trace >= (int) GX_TRACE_LEVEL_INFO)
        {
			char tmp[10];
			basic_string<char> str;
			str.append("Server settings: Protocol: ");
			str.append(GetProtocolAsString());
			str.append(" Port: ");
#if _MSC_VER > 1000
			_ltoa_s(GetPort(), tmp, 10, 10);			
#else
			sprintf(tmp, "%d", GetPort());
#endif
			str.append(tmp);
			CTraceEventArgs t(GX_TRACE_TYPES_INFO, str);
            NotifyTrace(t);
        }
		int fFlag = 1;
		if (setsockopt(m_ServerSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&fFlag, sizeof(fFlag)) == -1)
		{
			return ShowError("setsockopt ");
		}
		sockaddr_in add = {0};
		add.sin_port = htons(m_Port);
		add.sin_addr.s_addr = htonl(INADDR_ANY);
#ifdef WIN32
		add.sin_family = AF_INET;
#else
		add.sin_family = AF_INET;
#endif
		if((ret = ::bind(m_ServerSocket, (sockaddr*) &add, sizeof(add))) == -1)
		{
			return ShowError("bind ");
		}
		if((ret = listen(m_ServerSocket, 1)) == -1)
		{
			return ShowError("socket listen.");
		}
	}
	else //If client.
	{
		//create socket.
		m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
		if (m_Socket == -1) //If failed.
		{
			return ShowError("socket creation.");
		}
		if (m_Trace >= (int) GX_TRACE_LEVEL_INFO)
        {
			char tmp[10];
			basic_string<char> str;
			str.append("Client settings: Protocol: ");
			str.append(GetProtocolAsString());
			str.append(" Host: ");
			str.append(GetHostName());
			str.append(" Port: ");
#if _MSC_VER > 1000
			_ltoa_s(GetPort(), tmp, 10, 10);			
#else
			sprintf(tmp, "%d", GetPort());
#endif
			str.append(tmp);
			CTraceEventArgs t(GX_TRACE_TYPES_INFO, str);
            NotifyTrace(t);
        }
		sockaddr_in add;
		add.sin_port = htons(m_Port);
#ifdef WIN32
		add.sin_family = AF_INET;
#else
		add.sin_family = AF_INET;
#endif
		add.sin_addr.s_addr = inet_addr(m_HostName.c_str());
		//If address is give as name
		if(add.sin_addr.s_addr == INADDR_NONE)
		{
			hostent *Hostent = gethostbyname(m_HostName.c_str());
			if (Hostent == NULL)
			{
				ret = ShowError("gethostbyname ");
				Close();
				return ret;
			};
			add.sin_addr = *(in_addr*)(void*)Hostent->h_addr_list[0];
		};

		//Connect to the meter.
		ret = connect(m_Socket, (sockaddr*)&add, sizeof(sockaddr_in));
		if (ret == -1)
		{
			return ShowError("connect ");
		};
	}
#ifdef WIN32
	HANDLE m_hConnect = (HANDLE) _beginthread(ListenerThread, 0, (LPVOID) this);
#else
	pthread_t iThreadId;
	ret = pthread_create(&iThreadId, NULL, UnixListenerThread, (void *) this);
#endif
	NotifyMediaStateChange(GX_MEDIA_STATE_CHANGE_OPEN);
	return ret;
}

int CGXNet::Close()
{	
	if (m_ServerSocket != -1 || m_Socket != -1)
	{
		NotifyMediaStateChange(GX_MEDIA_STATE_CHANGE_CLOSING);
		if (m_ServerSocket != -1)
		{
			closesocket(m_ServerSocket);
			m_ServerSocket = -1;
		}
		if (m_Socket != -1)
		{
			closesocket(m_Socket );
			m_Socket = -1;
		}	
		//Sulje thread
		NotifyMediaStateChange(GX_MEDIA_STATE_CHANGE_CLOSED);
	}
	return 0;
}


basic_string<char> CGXNet::GetHostName()
{
	return m_HostName;
}

void CGXNet::SetHostName(basic_string<char> value)
{
	m_HostName = value;
}

int CGXNet::Receive(CReceiveParameters& args)
{
	if (GetSynchronous())
	{
		return 0;
	}
	else
	{
		int ret;
		if ((ret = recv(m_Socket, (char*) m_Receivebuff, sizeof(m_Receivebuff), 0)) == -1)
		{
			return -1;
		}
		//Append new data to the end of buffer.
		vector<unsigned char>& reply = args.getReply();
		reply.insert(reply.end(), reinterpret_cast<const unsigned char*>(m_Receivebuff), 
			reinterpret_cast<const unsigned char*>(m_Receivebuff) + ret);
		return ret;
	}
}

void CGXNet::ResetByteCounters()
{
	m_BytesReceived = m_BytesSent = 0;
}

int CGXNet::Send(vector<unsigned char>& data, basic_string<char> receiver)
{
	return Send(&data[0], data.size(), receiver);
}

int CGXNet::Send(unsigned char* pData, int len, basic_string<char> receiver)
{
	if (send(m_Socket, (const char*) pData, len, 0) == -1)
	{
		//If error has occured
		return -1;
	}
	return 0;
}

