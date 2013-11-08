See An [Gurux](http://www.gurux.org/ "Gurux") for an overview.

Join the Gurux Community or follow [@Gurux](http://twitter.com/guruxorg "@Gurux") for project updates.

Gurux.DLMS library for Java is a high-performance Java component that helps you to read DLMS/COSEM compatible electricity, gas or water meters. You can also use Gurux DLMS component to create own DLMS meter or broxy.

We have try to make component so easy to use that you do not need understand protocol at all.

For more info check out [Gurux.DLMS](http://www.gurux.fi/index.php?q=Gurux.DLMS "Gurux.DLMS").

We are updating documentation on Gurux web page. 

You should read [DLMS/COSEM FAQ](http://www.gurux.org/index.php?q=DLMSCOSEMFAQ) first to get started. Read Instructions for making your own [meter reading application](http://www.gurux.org/index.php?q=DLMSIntro) or build own 
DLMS/COSEM [meter/simulator/proxy](http://www.gurux.org/index.php?q=OwnDLMSMeter).

If you have problems you can ask your questions in Gurux [Forum](http://www.gurux.org/forum).

You do not nesessary need to use Gurux media component like Gurux.Net. 
You can use any connection library you want to. Gurux.DLMS classes only parse the data.


Simple example
=========================== 
First you must create server class and derive it from GXDLMSServerBase to add support for DLMS/COSEM protocol.
Then you must create server media to listen incoming DLMS messages.


```C++

class GXDLMSExampleServer : CGXDLMSServerBase, 
					IGXMediaListener, IGXNetListener

```

First you must tell what objects meter offers.
You can also set default or static values here.
Create media component here and start listen incoming data.

```C++
/// <summary>
/// Generic initialize for all servers.
/// </summary>
/// <param name="server"></param>
int CGXDLMSBase::Init(int port)
{
	m_Media.SetProtocol(GX_NW_TCPIP);
	m_Media.SetPort(port);
	m_Media.SetTrace(GX_TRACE_LEVEL_VERBOSE);
	m_Media.IsServer(true);
    m_Media.AddListener(this);
	int ret;
    if ((ret = m_Media.Open()) != 0)
	{
		printf("Media open failed %d", ret);
		return ret;
	}	
	///////////////////////////////////////////////////////////////////////
    //Add Logical Device Name. 123456 is meter serial number.
	///////////////////////////////////////////////////////////////////////
	// COSEM Logical Device Name is defined as an octet-string of 16 octets.
	// The first three octets uniquely identify the manufacturer of the device and it corresponds
	// to the manufacturer's identification in IEC 62056-21.
	// The following 13 octets are assigned by the manufacturer.
	//The manufacturer is responsible for guaranteeing the uniqueness of these octets.
	CGXDLMSVariant id2(serialNo.c_str());
	id2.ChangeType(DLMS_DATA_TYPE_UINT32);
	std::string tmp("GRX");
	for(int a = serialNo.length(); a < 13; ++a)
	{
		tmp.append("0");
	}
	tmp.append(serialNo);
	CGXDLMSVariant id(tmp.c_str());
	id.ChangeType(DLMS_DATA_TYPE_OCTET_STRING);
	CGXDataObject* d = new CGXDataObject("0.0.42.0.0.255", id);
	//d->GetAttributes().push_back(CGXDLMSAttribute(2, DLMS_DATA_TYPE_OCTET_STRING));
	GetItems().push_back(d);
	// Electricity ID 1
	d = new CGXDataObject("1.1.0.0.0.255", tmp.c_str());
	d->GetAttributes().push_back(CGXDLMSAttribute(2, DLMS_DATA_TYPE_STRING));
	GetItems().push_back(d);
	// Electricity ID 2
	d = new CGXDataObject("1.1.0.0.1.255", id2);
	d->GetAttributes().push_back(CGXDLMSAttribute(2, DLMS_DATA_TYPE_UINT32));
	GetItems().push_back(d);	    
	return ERROR_CODES_OK;
}
```

Read method is called when client wants to read some data from the meter.
If you want that framework returns current value just set Handled = false. 
Otherwice you can just set value that you want to return. 
In this example we will return current time for the clock.
Otherwise we will return attribute value of the object.

```C++

int CGXDLMSBase::OnRead(CGXObject* pItem, int index, CGXDLMSVariant& value, DLMS_DATA_TYPE& type)
{
	//Let framework handle Logical Name read.
	if (index == 1)
	{
		return ERROR_CODES_FALSE;
	}	
	//Framework will handle Association objects automatically.
	if (pItem->GetObjectType() == OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME ||
		pItem->GetObjectType() == OBJECT_TYPE_ASSOCIATION_SHORT_NAME ||
		//Framework will handle profile generic automatically.
		pItem->GetObjectType() == OBJECT_TYPE_PROFILE_GENERIC)                
    {
        return ERROR_CODES_FALSE;
    }
    //Implement read handling.
    return ERROR_CODES_FALSE;
}

```

Write method is called when client wants to write some data to the meter.
You can handle write by yourself or let the framework handle it.

```C++

int CGXDLMSBase::OnWrite(CGXObject* pItem, int index, CGXDLMSVariant& value)
{
	return ERROR_CODES_FALSE;
}

```

Action method is called when client performs action like reset.
You can handle actions by yourself or let the framework handle it.

```C++

int CGXDLMSBase::OnAction(CGXObject* pItem, int index, CGXDLMSVariant& data)
{
	return ERROR_CODES_FALSE;
}

```

Main functionality is happening here. When client sends DLMS byte packet to the server
media component receives it and sends it to the onReceived method.
You should only send received data to the handleRequest. This method parses the data and 
handles all nesessary actions. In result method returns data that is send to the client.

Note! If clientID and server ID (Server and Client Address) do not match, we do not return anything.
This is for the security. Client can't try to find meters just polling differents IP addresses.

```

/** 
 Media component sends received data through this method.

 @param sender The source of the event.
 @param e Event arguments.
*/
void OnReceived(IGXMedia* pSender, CReceiveEventArgs& e)
{
	unsigned char* pReply = NULL;
	int size = 0;
	HandleRequest(e.getData(), pReply, size);
    //Reply is null if we do not want to send any data to the client.
    //This is done if client try to make connection with wrong server or client address.
    if (size != 0)
    {
        m_Media.Send(pReply, size, e.getSenderInfo());
    }
}     

```

On error is called if media causes error.

```C++

void OnError(IGXMedia* pSender, basic_string<char>& ex)
{
	printf("Error has occurred : %s\r\n", ex.c_str());
}

```

When client is making connection onClientConnected method is called. 
You can example write log here.

```C++

void OnClientConnected(IGXMedia* pSender, CConnectionEventArgs& e)
{
	printf("Client Connected : %s\r\n", e.GetInfo().c_str());
}

```

When client is closing connection onClientDisconnected method is called. 
It is important that yo call reset method here to reset all connection settings.


```C++

/**
 Called when the client has been disconnected from the GXNet server.
 @param pSender The source of the event.    
 @param e Event arguments.
*/
void OnClientDisconnected(IGXMedia* pSender, CConnectionEventArgs& e)
{
	printf("Client Disonnected : %s\r\n", e.GetInfo().c_str());
}```