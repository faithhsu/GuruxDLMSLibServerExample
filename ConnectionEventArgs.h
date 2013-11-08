#pragma once

/** 
    Argument class for IGXMedia connection and disconnection events.
*/
class CConnectionEventArgs
{
    basic_string<char> m_Info;
    bool m_Accept;
public:

    /** 
     Constructor
    */
    CConnectionEventArgs()
    {
        SetAccept(true);
    }

    /** 
     Constructor
    */
    CConnectionEventArgs(basic_string<char> info)
    {
        SetAccept(true);
        SetInfo(info);
    }

    /** 
     Media depend information.
    */
    basic_string<char>& GetInfo()
    {
        return m_Info;
    }
    void SetInfo(basic_string<char> value)
    {
        m_Info = value;
    }

    /** 
     False, if the client is not accepted to connect.
    */
    bool GetAccept()
    {
        return m_Accept;
    }
    void SetAccept(bool value)
    {
        m_Accept = value;
    }
};