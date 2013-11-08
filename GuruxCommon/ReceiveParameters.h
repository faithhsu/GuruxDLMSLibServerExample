#pragma once

class CReceiveParameters
{
	int m_WaitTime;
    bool m_AllData;   
    vector<unsigned char> m_Reply;
    bool m_Peek;       
    int m_Count;
    
public:
    /** 
     Constructor.
    */
    CReceiveParameters()
    {        
        setWaitTime(-1);
    }
  
    /** 
     The number of reply data bytes to be read.

     Count can be between 0 and n bytes.

    */
    int getCount()
    {
        return m_Count;
    }
    void setCount(int value)
    {
        m_Count = value;
    }

    /** 
     Maximum time, in milliseconds, to wait for reply data. 
     WaitTime -1 (Default value) indicates infinite wait time.
    */
    int getWaitTime()
    {
        return m_WaitTime;
    }
    void setWaitTime(int value)
    {
        m_WaitTime = value;
    }

    /** 
     Received reply data.
    */
    vector<unsigned char>& getReply()
    {
        return m_Reply;
    }
    void setReply(vector<unsigned char>& value)
    {
        m_Reply = value;
    }
};
