#pragma once

#include "GXMedia.h"
#include "MediaStateEventArgs.h"
#include "TraceEventArgs.h"
#include "PropertyChangedEventArgs.h"
#include "TraceEventArgs.h"

class CReceiveEventArgs;

struct IGXMediaListener
{
public:
    /** 
        Represents the method that will handle the error event of a Gurux component.
        @param sender The source of the event.
        @param ex An Exception object that contains the event data.
    */
	virtual void OnError(IGXMedia* pSender, basic_string<char>& ex) = 0;

    /** 
     Media component sends received data through this method.

     @param sender The source of the event.
     @param e Event arguments.
    */
    virtual void OnReceived(IGXMedia* pSender, CReceiveEventArgs& e) = 0;    

    /** 
     Media component sends notification, when its state changes.

     @param sender The source of the event.    
     @param e Event arguments.
    */
    virtual void OnMediaStateChange(IGXMedia* pSender, CMediaStateEventArgs& e) = 0;

    /** 
     Called when the Media is sending or receiving data.

     @param sender
     @param e
     @see IGXMedia.Trace Traceseealso>
    */
    virtual void OnTrace(IGXMedia* pSender, CTraceEventArgs& e) = 0;    
    
    // Summary:
    //     Represents the method that will handle the System.ComponentModel.INotifyPropertyChanged.PropertyChanged
    //     event raised when a property is changed on a component.
    //
    // Parameters:
    //   sender:
    //     The source of the event.
    //
    //   e:
    //     A System.ComponentModel.PropertyChangedEventArgs that contains the event
    //     data.
    virtual void OnPropertyChanged(IGXMedia* pSender, CPropertyChangedEventArgs& e) = 0;
};
