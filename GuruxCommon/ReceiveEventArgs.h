#pragma once

class CReceiveEventArgs
{
	vector<unsigned char> m_Data;
    basic_string<char> m_SenderInfo;
public:   
    /** 
     Constructor
    */
    CReceiveEventArgs()
    {

    }

    /** 
     Constructor
    */
    CReceiveEventArgs(vector<unsigned char> data, basic_string<char> senderInfo)
    {
        m_Data = data;
        m_SenderInfo = senderInfo;
    }

	/** 
     Constructor
    */
    CReceiveEventArgs(unsigned char* pData, int len, basic_string<char> senderInfo)
    {
		//Append new data to the end of buffer.
		m_Data.insert(m_Data.end(), reinterpret_cast<const unsigned char*>(pData), 
			reinterpret_cast<const unsigned char*>(pData) + len);        
        m_SenderInfo = senderInfo;
    }

    /** 
     Pointer to the (safe array) byte buffer containing the data, 
     which is received from the device.
    */
    vector<unsigned char>& getData()
    {
        return m_Data;
    }
    void setData(vector<unsigned char> value)
    {
        m_Data = value;
    }
    /** 
     Media depend sender information.
    */
    basic_string<char>& getSenderInfo()
    {
        return m_SenderInfo;
    }
};
