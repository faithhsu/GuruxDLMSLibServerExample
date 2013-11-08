#pragma once

enum GX_NW_TYPE
{	GX_NW_UDP	= 0,
	GX_NW_TCPIP	= 1,
};

enum GX_MEDIA_STATE_CHANGE
{	
    /** 
     Media is closed.<br/>            
    */
	GX_MEDIA_STATE_CHANGE_CLOSED = 1,
    /** 
     Media is open.<br/>            
    */
	GX_MEDIA_STATE_CHANGE_OPEN = 2,
    /** 
     Media is opening.<br/>
    */
	GX_MEDIA_STATE_CHANGE_OPENING = 3,
    /** 
     Media is closing.<br/>            
    */
	GX_MEDIA_STATE_CHANGE_CLOSING = 4,
};

/** 
 * Trace Type enumerates where trace is sent.
*/
enum GX_TRACE_TYPES
{
    /** 
     Data is sent.
    */
    GX_TRACE_TYPES_SENT,
    /** 
     Data is received.
    */
    GX_TRACE_TYPES_RECEIVED,
    /** 
     Error has occurred.
    */
    GX_TRACE_TYPES_ERROR,
    /** 
     Warning.
    */
    GX_TRACE_TYPES_WARNING,
    /** 
     Info. Example Media states are notified as info.
    */
    GX_TRACE_TYPES_INFO
};

enum GX_TRACE_LEVEL
{
    // Summary:
    //     Output no tracing and debugging messages.
    GX_TRACE_LEVEL_OFF,
    //
    // Summary:
    //     Output error-handling messages.
    GX_TRACE_LEVEL_ERROR,
    //
    // Summary:
    //     Output warnings and error-handling messages.
    GX_TRACE_LEVEL_WARNING,
    //
    // Summary:
    //     Output informational messages, warnings, and error-handling messages.
    GX_TRACE_LEVEL_INFO,
    //
    // Summary:
    //     Output all debugging and tracing messages.
    GX_TRACE_LEVEL_VERBOSE
};