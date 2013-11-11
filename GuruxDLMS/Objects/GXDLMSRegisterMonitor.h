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

#pragma once
#include "GXDLMSMonitoredValue.h"
#include "GXDLMSActionSet.h"

class CGXDLMSRegisterMonitor : public CGXObject
{
	vector<CGXDLMSActionSet> m_Actions;
    CGXDLMSMonitoredValue m_MonitoredValue;
    vector<CGXDLMSVariant> m_Thresholds;
    
public:
	/**  
     Constructor.
    */
	CGXDLMSRegisterMonitor() : CGXObject(OBJECT_TYPE_REGISTER_MONITOR)
    {        
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXDLMSRegisterMonitor(basic_string<char> ln) : CGXObject(OBJECT_TYPE_REGISTER_MONITOR, ln)
    {        
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
	CGXDLMSRegisterMonitor(int sn) : CGXObject(OBJECT_TYPE_REGISTER_MONITOR, sn)
    {        
    }

    vector<CGXDLMSVariant> GetThresholds()
    {
        return m_Thresholds;
    }
    void SetThresholds(vector<CGXDLMSVariant>& value)
    {
        m_Thresholds = value;
    }

    CGXDLMSMonitoredValue& GetMonitoredValue()
    {
        return m_MonitoredValue;
    }
    void SetMonitoredValue(CGXDLMSMonitoredValue& value)
    {
        m_MonitoredValue = value;
    }

    vector<CGXDLMSActionSet>& GetActions()
    {
        return m_Actions;
    }
    void SetActions(vector<CGXDLMSActionSet>& value)
    {
        m_Actions = value;
    }
    

	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 4;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 0;
	}
    
    /*
     * Returns value of given attribute.
     */    
    int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value, DLMS_DATA_TYPE& type)
	{    
        if (index == 1)
        {
            GXHelpers::AddRange(value.byteArr, m_LN, 6);
			type = value.vt = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
        }
        if (index == 2)
        {
			type = DLMS_DATA_TYPE_ARRAY;
			vector<unsigned char> data;
			data.push_back(DLMS_DATA_TYPE_ARRAY);
			//Add count
			CGXOBISTemplate::SetObjectCount(m_Thresholds.size(), data);
			for(vector<CGXDLMSVariant>::iterator it = m_Thresholds.begin(); it != m_Thresholds.end(); ++it)
			{
				DLMS_DATA_TYPE type = (*it).vt;
				CGXOBISTemplate::SetData(data, type, *it);
			}			
			value = data;
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            vector<unsigned char> stream;
			stream.push_back(DLMS_DATA_TYPE_STRUCTURE);
            stream.push_back(3);
			int ret;
			if ((ret = CGXOBISTemplate::SetData(stream, DLMS_DATA_TYPE_UINT16, m_MonitoredValue.GetObjectType())) != ERROR_CODES_OK ||  //ClassID            
				(ret = CGXOBISTemplate::SetData(stream, DLMS_DATA_TYPE_OCTET_STRING, m_MonitoredValue.GetLogicalName())) != ERROR_CODES_OK || //LN
				(ret = CGXOBISTemplate::SetData(stream, DLMS_DATA_TYPE_INT8, m_MonitoredValue.GetAttributeIndex())) != ERROR_CODES_OK)
			{
				return ret;
			}
            value = stream;
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {
			type = DLMS_DATA_TYPE_ARRAY;
			vector<unsigned char> data;
			data.push_back(DLMS_DATA_TYPE_ARRAY);
			int ret;
			//Add count			
			CGXOBISTemplate::SetObjectCount(m_Actions.size(), data);
			for(vector<CGXDLMSActionSet>::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it)
			{
				data.push_back(DLMS_DATA_TYPE_STRUCTURE);
				data.push_back(2);				
				data.push_back(DLMS_DATA_TYPE_STRUCTURE);
				data.push_back(2);				
				if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, it->GetActionDown().GetLogicalName())) != ERROR_CODES_OK ||
					(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, it->GetActionDown().GetScriptSelector())) != ERROR_CODES_OK)
				{
					return ret;
				}						
				data.push_back(DLMS_DATA_TYPE_STRUCTURE);
				data.push_back(2);				
				if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, it->GetActionUp().GetLogicalName())) != ERROR_CODES_OK ||
					(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, it->GetActionUp().GetScriptSelector())) != ERROR_CODES_OK)
				{
					return ret;
				}						
			}			
			value = data;
			return ERROR_CODES_OK;
        }  
        return ERROR_CODES_INVALID_PARAMETER;
    }
    
    /*
     * Set value of given attribute.
     */
    int SetValue(int index, CGXDLMSVariant& value)
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
        if (index == 2)
        {                
			SetThresholds(value.Arr);
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
			GetMonitoredValue().SetObjectType((OBJECT_TYPE) value.Arr[0].lVal);
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.Arr[1].byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp);
			GetMonitoredValue().SetLogicalName(tmp.strVal);
			GetMonitoredValue().SetAttributeIndex(value.Arr[2].lVal);
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {
			for (vector<CGXDLMSVariant>::iterator action_set = value.Arr.begin(); action_set != value.Arr.end(); ++action_set)
            {
                CGXDLMSActionSet set;
				CGXDLMSVariant target = (*action_set).Arr[0];
				CGXDLMSVariant tmp;
				CGXDLMSClient::ChangeType(target.Arr[0].byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp);
				set.GetActionUp().SetLogicalName(tmp.strVal);
				set.GetActionUp().SetScriptSelector(target.Arr[1].lVal);
                target = (*action_set).Arr[1];
				CGXDLMSClient::ChangeType(target.Arr[0].byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp);
				set.GetActionDown().SetLogicalName(tmp.strVal);
                set.GetActionDown().SetScriptSelector(target.Arr[1].lVal);
                m_Actions.push_back(set);
            }
			return ERROR_CODES_OK;
        }
        return ERROR_CODES_INVALID_PARAMETER;
    }
};