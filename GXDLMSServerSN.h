#pragma once
#include "GXDLMSBase.h"

class CGXDLMSServerSN :
	public CGXDLMSBase
{
public:
	CGXDLMSServerSN() : CGXDLMSBase(false, GXDLMS_INTERFACETYPE_GENERAL)
	{
	}
};
