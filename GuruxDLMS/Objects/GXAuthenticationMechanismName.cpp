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

#include "GXAuthenticationMechanismName.h"
#include <sstream> 
#include "../GXDLMSVariant.h"

CGXAuthenticationMechanismName::CGXAuthenticationMechanismName()
{
    m_MechanismId = GXDLMS_AUTHENTICATION_NONE;
	m_JointIsoCtt = m_Country = m_CountryName = 0;
	m_IdentifiedOrganization = m_DlmsUA = m_AuthenticationMechanismName = 0;
}

int CGXAuthenticationMechanismName::GetJointIsoCtt()
{
    return m_JointIsoCtt;
}
void CGXAuthenticationMechanismName::SetJointIsoCtt(int value)
{
    m_JointIsoCtt = value;
}

int CGXAuthenticationMechanismName::GetCountry()
{
    return m_Country;
}
void CGXAuthenticationMechanismName::SetCountry(int value)
{
    m_Country = value;
}

int CGXAuthenticationMechanismName::GetCountryName()
{
    return m_CountryName;
}
void CGXAuthenticationMechanismName::SetCountryName(int value)
{
    m_CountryName = value;
}
int CGXAuthenticationMechanismName::GetIdentifiedOrganization()
{
    return m_IdentifiedOrganization;
}
void CGXAuthenticationMechanismName::SetIdentifiedOrganization(int value)
{
    m_IdentifiedOrganization = value;
}

int CGXAuthenticationMechanismName::GetDlmsUA()
{
    return m_DlmsUA;
}
void CGXAuthenticationMechanismName::SetDlmsUA(int value)
{
    m_DlmsUA = value;
}
int CGXAuthenticationMechanismName::GetAuthenticationMechanismName()
{
    return m_AuthenticationMechanismName;
}
void CGXAuthenticationMechanismName::SetAuthenticationMechanismName(int value)
{
    m_AuthenticationMechanismName = value;
}

GXDLMS_AUTHENTICATION CGXAuthenticationMechanismName::GetMechanismId()
{
    return m_MechanismId;
}
void CGXAuthenticationMechanismName::SetMechanismId(GXDLMS_AUTHENTICATION value)
{
    m_MechanismId = value;
}


string CGXAuthenticationMechanismName::ToString()
{
	std::stringstream sb;
	sb << CGXDLMSVariant(m_JointIsoCtt).ToString().c_str();
	sb << " ";
	sb << CGXDLMSVariant(m_Country).ToString().c_str();
	sb << " ";
	sb << CGXDLMSVariant(m_CountryName).ToString().c_str();
	sb << " ";
	sb << CGXDLMSVariant(m_IdentifiedOrganization).ToString().c_str();
	sb << " ";
	sb << CGXDLMSVariant(m_DlmsUA).ToString().c_str();
	sb << " ";
	sb << CGXDLMSVariant(m_AuthenticationMechanismName).ToString().c_str();
	sb << " ";
	sb << CGXDLMSVariant(m_MechanismId).ToString().c_str();
	return sb.str();
}