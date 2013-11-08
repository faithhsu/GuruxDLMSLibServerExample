#pragma once

#include "Enums.h"
#include <stdio.h>
#include <stdlib.h>
#include "../GuruxDLMS/GXHelpers.h"

/** 
 * Argument class for IGXMedia connection and disconnection events.
*/
class CTraceEventArgs
{
    struct tm m_Timestamp;    
    GX_TRACE_TYPES m_Type;
    vector<unsigned char> m_Data;
	bool m_Ascii;
public: 
    /** 
     Timestamp.
    */
    struct tm GetTimestamp()
    {
        return m_Timestamp;
    }

    /** 
     Is data send or received and type of trace.
    */
    GX_TRACE_TYPES GetType()
    {
        return m_Type;
    }

	/** 
     Received/send data.
    */    
    vector<unsigned char>& GetData()
    {
        return m_Data;
    }
    
    /** 
     Convert data to string.

     @param ascii Is content get as ascii or hex string.
     @return Content of data as string.
    */
    basic_string<char> DataToString(bool ascii)
    {
		if (m_Data.size() == 0)
        {
			return "";
        }
		basic_string<char> str;
        if (ascii)
        {
			const unsigned char* pData = &m_Data[0];
			str.insert(str.end(), reinterpret_cast<const unsigned char*>(pData), 
						reinterpret_cast<const unsigned char*>(pData) + m_Data.size());
			return str;
        }
		return GXHelpers::bytesToHex(&m_Data[0], m_Data.size());    
    }

	basic_string<char> TypeToString()
    {
		basic_string<char> str;
		switch(m_Type)
		{
			case GX_TRACE_TYPES_SENT:
				str = "<-";
			break;
			case GX_TRACE_TYPES_RECEIVED:
				str = "->";
			break;
			case GX_TRACE_TYPES_ERROR:
				str = "Error";
			break;
			case GX_TRACE_TYPES_WARNING:
				str = "Warning";
			break;
			case GX_TRACE_TYPES_INFO:
				str = "Info";
			break;
			default:
				str = "Unknown";
		}
		return str;
	}

    /** 
     Show trace event content as string.

     @return 
    */
    basic_string<char> ToString()
    {
		char tmp[5];
		basic_string<char> str;
#if _MSC_VER > 1000		
		_ltoa_s(m_Timestamp.tm_hour, tmp, 5, 10);
#else
		sprintf(tmp, "%d", m_Timestamp.tm_hour);
#endif		
		str.append(tmp);
		str.append(":");
#if _MSC_VER > 1000		
		_ltoa_s(m_Timestamp.tm_min, tmp, 5, 10);
#else
		sprintf(tmp, "%d", m_Timestamp.tm_min);
#endif		
		str.append(tmp);
		str.append(":");
#if _MSC_VER > 1000		
		_ltoa_s(m_Timestamp.tm_sec, tmp, 5, 10);
#else
		sprintf(tmp, "%d", m_Timestamp.tm_sec);
#endif		
		str.append(tmp);
		str.append("\t");
		str.append(TypeToString());		
		str.append("\t");
		str.append(DataToString(m_Ascii));
        return str;                		
    }

	/** 
     Constructor
    */
    CTraceEventArgs(GX_TRACE_TYPES type, basic_string<char> data)
    {
		m_Ascii = true;
		time_t tm1 = time(NULL);
#if _MSC_VER > 1000		
		localtime_s(&m_Timestamp, &tm1);
#else
		m_Timestamp = *localtime(&tm1);
#endif        
        m_Type = type;
		const char* pData = &data[0];
		m_Data.insert(m_Data.end(), reinterpret_cast<const unsigned char*>(pData), 
				reinterpret_cast<const unsigned char*>(pData) + data.size());
    }

    /** 
     Constructor
    */
    CTraceEventArgs(GX_TRACE_TYPES type, vector<unsigned char> data)
    {
		m_Ascii = false;
		time_t tm1 = time(NULL);
#if _MSC_VER > 1000		
		localtime_s(&m_Timestamp, &tm1);
#else
		m_Timestamp = *localtime(&tm1);
#endif
        m_Type = type;
        m_Data = data;
    }

    /** 
     Constructor
    */
    CTraceEventArgs(GX_TRACE_TYPES type, unsigned char* pData, int index, int length)
    {
		m_Ascii = false;
		time_t tm1 = time(NULL);
#if _MSC_VER > 1000		
		localtime_s(&m_Timestamp, &tm1);
#else
		m_Timestamp = *localtime(&tm1);
#endif
		m_Type = type;
		m_Data.insert(m_Data.end(), reinterpret_cast<const unsigned char*>(pData + index), 
						reinterpret_cast<const unsigned char*>(pData) + length);
    }
};
