#pragma once
#include "ConnectionEventArgs.h"
#include "GuruxCommon/GXMedia.h"

struct IGXNetListener
{
public:
    /** 
     Called when the client is establishing a connection with a GXNet Server.

     @param sender The source of the event.    
     @param e Event arguments.
    */
    virtual void OnClientConnected(IGXMedia* pSender, CConnectionEventArgs& e) = 0;

    /** 
     Called when the client has been disconnected from the GXNet server.

     @param sender The source of the event.    
     @param e Event arguments.
    */
    virtual void OnClientDisconnected(IGXMedia* pSender, CConnectionEventArgs& e) = 0;
};
