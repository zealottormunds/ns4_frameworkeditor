#pragma once
#include "ccGameDrawEnv.h"

class ccGame
{
public:
	char padding0[0x10]; // 0x00 to 0x10
	ccGameDrawEnv m_gameDrawEnvInstance; // 0x10 to 0x18

	static ccGame * GetInstance()
	{
		return (ccGame*)(moduleBase + 0x14161A330 - 0x140000C00);
	}
};