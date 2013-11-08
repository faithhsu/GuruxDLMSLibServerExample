#pragma once

class CMediaStateEventArgs
{
	GX_MEDIA_STATE_CHANGE m_State;
    bool m_Accept;
public:

    /** 
     Constructor
    */
    CMediaStateEventArgs()
    {
        SetAccept(true);
    }

    /** 
     Constructor
    */
    CMediaStateEventArgs(GX_MEDIA_STATE_CHANGE state)
    {        
		SetAccept(true);
        SetState(state);
    }

    /** 
     Status information from media state.
    */
    
    GX_MEDIA_STATE_CHANGE GetState()
    {
        return m_State;
    }
    void SetState(GX_MEDIA_STATE_CHANGE value)
    {
        m_State = value;
    }

    /** 
     True is returned if media state change succeeded.
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
