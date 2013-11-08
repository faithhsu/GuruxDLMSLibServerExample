#pragma once

#include "GuruxCommon/GXMedia.h"
#include "GuruxCommon/ReceiveParameters.h"
#include "GuruxCommon/GXMediaListener.h"
#include "ConnectionEventArgs.h"
#include "GuruxCommon/ReceiveEventArgs.h"
#include "GXNetListener.h"

/** 
 The GXNet component determines methods that make the communication possible using Internet. 

*/
class CGXNet : public IGXMedia
{	
	//TODO; HANDLE m_Received;
	bool m_Synchronous;
	GX_TRACE_LEVEL m_Trace;
	int m_Port;
	basic_string<char> m_HostName;
    unsigned long m_BytesReceived, m_BytesSent;
	enum GX_NW_TYPE m_Protocol;
	bool m_IsServer;    
	vector<IGXNetListener*> m_NetListeners;
	vector<IGXMediaListener*> m_MediaListeners;
	void Init(enum GX_NW_TYPE protocol, basic_string<char>& hostName, int port);
	basic_string<char> GetProtocolAsString()
	{
		if (m_Protocol == GX_NW_TCPIP)
		{
			return "TCP/IP";
		}
		return "UDP";
	}

	int ShowError(const char* msg)
	{
#ifdef WIN32
		return WSAGetLastError();
#else
		perror(msg);
		return errno;
#endif
	}

public:	
	unsigned char m_Receivebuff[1024];
	int m_ReceiveBuffPos;
	int m_Socket;
	int m_ServerSocket;
public:
	/** 
     Constructor.
    */
	CGXNet(void);

	/** 
     Server Constructor.
    */
    CGXNet(GX_NW_TYPE protocol, int port);

	/** 
     Client Constructor.
    */
	CGXNet(GX_NW_TYPE protocol, string hostName, int port);

	~CGXNet(void);

	/** 
     Checks if the connection is in synchronous mode.

     @return True, if the connection is in synchronous mode.		
    */
    bool GetSynchronous()
	{
		return m_Synchronous;
	}

    /** 
     Sets connection synchronous mode.
    */
    void SetSynchronous(bool value)
	{
		m_Synchronous = value;
	}

	/** 
     Opens the media.
    */
	int Open();
	
	/** 
     Closes the active connection.

     @see Open Open
    */
	int Close();

	/** 
     Retrieves or sets the name or IP address of the host.

     <value>
     The name of the host.
     </value>
     @see Open Open
     @see Port Port
     @see Protocol Protocol
    */
	basic_string<char> GetHostName();
	void SetHostName(basic_string<char> value);
	
	/** 
     Retrieves or sets the host or server port number.

     <value>
     Host or server port number.
     </value>
     @see Open Open
     @see HostName HostName  	
     @see Protocol Protocol
    */
	int GetPort()
	{
		return m_Port;
	}
	void SetPort(int value)
	{
		m_Port = value;
	}	

	/** 
     Retrieves or sets the protocol.

     Defaut protocol is UDP.

     <value>
     Protocol
     </value>
    */
	GX_NW_TYPE getProtocol()
	{
		return m_Protocol;
	}

	void SetProtocol(GX_NW_TYPE value)
	{
		m_Protocol = value;
	}

	 /** 
    Determines if the component is in server, or in client, mode.

    <value>
    True, if component is a server. False, if component is a client.
    </value>
    @see Open Open 	
	*/
	bool IsServer()
	{
		return m_IsServer;
	}
	void IsServer(bool value)
	{
		m_IsServer = value;
	}

    /** 
     Received byte count.

     @see BytesSent BytesSent
     @see ResetByteCounters ResetByteCounters            
    */
    unsigned long GetBytesReceived()
	{
		return m_BytesReceived;
	}

	 /** 
     Sent byte count.

     @see BytesReceived BytesReceived
     @see ResetByteCounters ResetByteCounters            
    */
    unsigned long GetBytesSent()
	{
		return m_BytesSent;
	}
	
	 /** 
     Trace level of the IGXMedia for System.Diagnostic.Trace.Writes.

     {@link OnTrace}        
    */
	GX_TRACE_LEVEL GetTrace()
	{
		return m_Trace;
	}
	void SetTrace(GX_TRACE_LEVEL value)
	{
		m_Trace = value;
	}

	 /** 
     Checks if the connection is established.

     @return True, if the connection is established.		
    */
	bool IsOpen()
	{
		if (m_IsServer)
		{
			return m_ServerSocket != -1;
		}
		return m_Socket != -1;
	}
    
	/** 
     Waits for more reply data After SendSync if whole packet is not received yet.

     @param args Receive data arguments.
    */
	int Receive(CReceiveParameters& args);
    
	    /** 
     Resets BytesReceived and BytesSent counters.

     @see BytesSent BytesSent
     @see BytesReceived BytesReceived
    */
	void ResetByteCounters();


	/** 
     Sends data asynchronously. <br/>
     No reply from the receiver, whether or not the operation was successful, is expected.

     @param data Data to send to the device.
     @param receiver IP address of the receiver (optional).
     Reply data is received through OnReceived event.<br/>     		
     @see OnReceived OnReceived
     @see Open Open
     @see Close Close 
    */
    int Send(vector<unsigned char>& data, basic_string<char> receiver);
	int Send(unsigned char* pData, int len, basic_string<char> receiver);

	/*
     * Start to listen media events.
     */
    void AddListener(IGXMediaListener* pListener)
	{
		m_MediaListeners.push_back(pListener);		
		IGXNetListener* p = dynamic_cast<IGXNetListener*>(pListener);
		if (p != NULL)
		{
			m_NetListeners.push_back(p);
		}
	}

    /*
     * Stop to listen media events.
     */
    void RemoveListener(IGXMediaListener* pListener)
	{
		for(vector<IGXMediaListener*>::iterator it = m_MediaListeners.begin(); 
			it != m_MediaListeners.end(); ++it)
		{
			if (pListener == (*it))
			{
				m_MediaListeners.erase(it);
				break;
			}
		}
		IGXNetListener* p = dynamic_cast<IGXNetListener*>(pListener);
		if (p != NULL)
		{
			for(vector<IGXNetListener*>::iterator it = m_NetListeners.begin(); 
				it != m_NetListeners.end(); ++it)
			{
				if (p == (*it))
				{
					m_NetListeners.erase(it);
					break;
				}
			}			
		}
	}

	//Notify that client is connected.
	void NotifyClientConnected(CConnectionEventArgs& e);
	
	//Notify that client is disconnected.
	void NotifyClientDisconnected(CConnectionEventArgs& e);
	
	//Notify that property is changed.
	void NotifyPropertyChanged(basic_string<char>& info);
	
	//Notify error.
	void NotifyError(basic_string<char>& ex);
	
	//Notify that new data is received..
	void NotifyReceived(CReceiveEventArgs& e);
	
	//Notify trace.
	void NotifyTrace(CTraceEventArgs& e);
	
	//Notify that media state is changed.
	void NotifyMediaStateChange(GX_MEDIA_STATE_CHANGE state);
};
