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

#include "../GXDLMSVariant.h"
#include "../GXDLMSClient.h"
#include "GXDLMSClock.h"
#include "../GXDLMSConverter.h"

void CGXDLMSClock::Init()
{
	m_Deviation = m_ClockBase = CLOCKBASE_NONE;		
	m_Enabled = false;		
	m_TimeZone = 0;
	m_Status = GXDLMS_CLOCK_STATUS_OK;
}

/**  
 Constructor.
*/
CGXDLMSClock::CGXDLMSClock() : CGXDLMSObject(OBJECT_TYPE_CLOCK, "0.0.1.0.0.255")
{
	Init();
}

/**  
Constructor.
@param ln Logical Name of the object.
*/
CGXDLMSClock::CGXDLMSClock(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_CLOCK, ln)
{
	Init();
}

/**  
 Constructor.
 @param ln Logical Name of the object.
 @param sn Short Name of the object.
*/
CGXDLMSClock::CGXDLMSClock(basic_string<char> ln, int sn) : CGXDLMSObject(OBJECT_TYPE_CLOCK, ln)
{
	Init();
	SetShortName(sn);
}
	
/** 
 Time of COSEM Clock object.
*/	
CGXDateTime CGXDLMSClock::GetTime()
{
    return m_Time;
}
void CGXDLMSClock::SetTime(CGXDateTime& value)
{
    m_Time = value;
}

/** 
 TimeZone of COSEM Clock object.
*/
short CGXDLMSClock::GetTimeZone()
{
    return m_TimeZone;
}
void CGXDLMSClock::SetTimeZone(short value)
{
    m_TimeZone = value;
}

/** 
 Status of COSEM Clock object.
*/
GXDLMS_CLOCK_STATUS CGXDLMSClock::GetStatus()
{
    return m_Status;
}
void CGXDLMSClock::SetStatus(GXDLMS_CLOCK_STATUS value)
{
    m_Status = value;
}

CGXDateTime CGXDLMSClock::GetBegin()
{
    return m_Begin;
}

void CGXDLMSClock::SetBegin(CGXDateTime& value)
{
    m_Begin = value;
}

CGXDateTime CGXDLMSClock::GetEnd()
{
    return m_End;
}
void CGXDLMSClock::SetEnd(CGXDateTime& value)
{
    m_End = value;
}

char CGXDLMSClock::GetDeviation()
{
    return m_Deviation;
}
void CGXDLMSClock::SetDeviation(char value)
{
    m_Deviation = value;
}

bool CGXDLMSClock::GetEnabled()
{
    return m_Enabled;
}
void CGXDLMSClock::SetEnabled(bool value)
{
    m_Enabled = value;
}

/** 
 Clock base of COSEM Clock object.
*/
CLOCKBASE CGXDLMSClock::GetClockBase()
{
    return m_ClockBase;
}
void CGXDLMSClock::SetClockBase(CLOCKBASE value)
{
    m_ClockBase = value;
}

// Returns amount of attributes.
int CGXDLMSClock::GetAttributeCount()
{
	return 9;
}

// Returns amount of methods.
int CGXDLMSClock::GetMethodCount()
{
	return 0;
}

void CGXDLMSClock::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(m_Time.ToString());
	values.push_back(CGXDLMSVariant(m_TimeZone).ToString());
	values.push_back(CGXDLMSConverter::ToString(m_Status));
	values.push_back(m_Begin.ToString());
	values.push_back(m_End.ToString());
	values.push_back(CGXDLMSVariant(m_Deviation).ToString());
	values.push_back(CGXDLMSVariant(m_Enabled).ToString());
	values.push_back(CGXDLMSConverter::ToString(m_ClockBase));
}

void CGXDLMSClock::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//Time
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
    //TimeZone
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //Status
    if (CanRead(4))
    {
        attributes.push_back(4);
    }
    //Begin
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
    //End
    if (!IsRead(6))
    {
        attributes.push_back(6);
    }
    //Deviation
    if (!IsRead(7))
    {
        attributes.push_back(7);
    }
    //Enabled
    if (!IsRead(8))
    {
        attributes.push_back(8);
    }
    //ClockBase
    if (!IsRead(9))
    {
        attributes.push_back(9);
    }
}

int CGXDLMSClock::GetUIDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 2)
    {
		type = DLMS_DATA_TYPE_DATETIME;			
    }
	else
	{
		return CGXDLMSObject::GetUIDataType(index, type);
	}
	return ERROR_CODES_OK;
}

int CGXDLMSClock::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;			
    }
    else if (index == 2)
    {
		type = DLMS_DATA_TYPE_DATETIME;			
    }
    else if (index == 3)
    {            
		type = DLMS_DATA_TYPE_INT16;			
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_UINT8;			
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_DATETIME;			
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_DATETIME;			
    }
    else if (index == 7)
    {
        type = DLMS_DATA_TYPE_INT8;			
    }
    else if (index == 8)
    {
        type = DLMS_DATA_TYPE_BOOLEAN;			
    }
    else if (index == 9)
    {
        type = DLMS_DATA_TYPE_ENUM;			
    }
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

/*
 * Returns value of given attribute.
 */    
int CGXDLMSClock::GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value)
{
    if (index == 1)
    {
        GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
    }
    if (index == 2)
    {
		value = GetTime();
		return 0;
    }
    if (index == 3)
    {            
        value = GetTimeZone();
		return 0;
    }
    if (index == 4)
    {
        value = (unsigned char) GetStatus();
		return 0;
    }
    if (index == 5)
    {
		value = GetBegin();
		return 0;
    }
    if (index == 6)
    {
		value = GetEnd();
		return 0;
    }
    if (index == 7)
    {
        value = GetDeviation();
		return 0;
    }
    if (index == 8)
    {
        value = GetEnabled();
		return 0;
    }
    if (index == 9)
    {
        value = GetClockBase();
		return 0;
    }
    return ERROR_CODES_INVALID_PARAMETER;
}

/*
 * Set value of given attribute.
 */
int CGXDLMSClock::SetValue(int index, CGXDLMSVariant& value)
{
    if (index == 1)
    {
        if (value.vt != DLMS_DATA_TYPE_OCTET_STRING || value.GetSize() != 6)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		memcpy(m_LN, &value.byteArr[0], 6);
		return ERROR_CODES_OK;
    }
    else if (index == 2)
    {
		if (value.vt == DLMS_DATA_TYPE_OCTET_STRING)
		{
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
			SetTime(tmp.dateTime);
		}
		else
		{
			SetTime(value.dateTime);
		}
    }
    else if (index == 3)
    {
        SetTimeZone(value.ToInteger());
    }
    else if (index == 4)
    {
        SetStatus((GXDLMS_CLOCK_STATUS) value.ToInteger());
    }
    else if (index == 5)
    {
		if (value.vt == DLMS_DATA_TYPE_OCTET_STRING)
		{
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
			SetBegin(tmp.dateTime);
		}
		else
		{
			SetBegin(value.dateTime);
		}
    }
    else if (index == 6)
    {
		if (value.vt == DLMS_DATA_TYPE_OCTET_STRING)
		{
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
			SetEnd(tmp.dateTime);
		}
		else
		{
			SetEnd(value.dateTime);
		}
    }
    else if (index == 7)
    {
        SetDeviation(value.ToInteger());
    }
    else if (index == 8)
    {
        SetEnabled(value.boolVal);
    }
    else if (index == 9)
    {
        SetClockBase((CLOCKBASE)value.ToInteger());
    }
    else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}
