#pragma once

class CPropertyChangedEventArgs
{
	basic_string<char> m_PropertyName;
public:
    /*
     * Constructor.
     */
    CPropertyChangedEventArgs(basic_string<char> propertyName)
    {
        m_PropertyName = propertyName;
    }

    /*
     * Gets the name of the property that changed.
     */
    basic_string<char> GetPropertyName()
    {
        return m_PropertyName;
    }
};
