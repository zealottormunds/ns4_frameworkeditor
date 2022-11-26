#pragma once
#include "Common.h"

class ccStateMachine
{
public:
	static __int64 Update(ccStateMachine* a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccStateMachine*)>(moduleBase + 0x3296D8)(a1);
	}
};

class ccStateMachineFunctions
{
public:
	const char* m_stateName; // 0x00 to 0x08
	__int64 m_enter; // 0x08 to 0x10
	__int64 m_execute; // 0x10 to 0x18
	__int64 m_exit; // 0x18 to 0x20
	__int64 m_padding; // 0x20 to 0x28
};