#pragma once

#include "Enums.h"
#include "ReceiveParameters.h"

struct IGXMediaListener;

/** 
Common interface for all Media components.<br/>
Using this interface GXCommunication library enables communication with
different medias.
*/
struct IGXMedia
{
public:
    /*
     * Start to listen media events.
     */
    virtual void AddListener(IGXMediaListener* pListener) = 0;

    /*
     * Stop to listen media events.
     */
    virtual void RemoveListener(IGXMediaListener* pListener) = 0;

    /** 
     Trace level of the IGXMedia for System.Diagnostic.Trace.Writes.

     {@link OnTrace}        
    */
    virtual GX_TRACE_LEVEL GetTrace() = 0;
    virtual void SetTrace(GX_TRACE_LEVEL value) = 0;


    /** 
     Opens the media.
    */
	virtual int Open() = 0;

    /** 
     Checks if the connection is established.

     @return True, if the connection is established.		
    */
    virtual bool IsOpen() = 0;

    /** 
     Closes the active connection.

     @see Open Open
    */
    virtual int Close() = 0;

    /** 
     Sends data. <br/>
     No reply from the receiver, whether or not the operation was successful, is expected.

     @param data Data to send to the device.
     @param receiver Media depend information of the receiver (optional).
     @see Receive Receive
    */
    virtual int Send(vector<unsigned char>& data, basic_string<char> receiver) = 0;

    /** 
     Sends data. <br/>
     No reply from the receiver, whether or not the operation was successful, is expected.

     @param data Data to send to the device.
     @param receiver Media depend information of the receiver (optional).
     @see Receive Receive
    */
	virtual int Send(unsigned char* pData, int len, basic_string<char> receiver) = 0;

    /** 
     Checks if the connection is in synchronous mode.

     @return True, if the connection is in synchronous mode.		
    */
    virtual bool GetSynchronous() = 0;

    /** 
     Sets connection synchronous mode.
    */
    virtual void SetSynchronous(bool value) = 0;

    /** 
     Waits for more reply data After SendSync if whole packet is not received yet.

     @param args Receive data arguments.
    */
    virtual int Receive(CReceiveParameters& args) = 0;

    /** 
     Sent byte count.

     @see BytesReceived BytesReceived
     @see ResetByteCounters ResetByteCounters            
    */
    virtual unsigned long GetBytesSent() = 0;

    /** 
     Received byte count.

     @see BytesSent BytesSent
     @see ResetByteCounters ResetByteCounters            
    */
    virtual unsigned long GetBytesReceived() = 0;

    /** 
     Resets BytesReceived and BytesSent counters.

     @see BytesSent BytesSent
     @see BytesReceived BytesReceived            
    */
    virtual void ResetByteCounters() = 0;
};
