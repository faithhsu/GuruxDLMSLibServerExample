#pragma once
#include "GXDLMSBase.h"

class CGXDLMSServerLN :
	public CGXDLMSBase
{
public:
	//Constructor.
	CGXDLMSServerLN(void) : CGXDLMSBase(true, GXDLMS_INTERFACETYPE_GENERAL)
	{
	}
};
