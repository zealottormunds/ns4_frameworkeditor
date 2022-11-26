#pragma once
#include "ccStateMachine.h"
#include "Common.h"

class ccSceneBoss12StateMachine
{
public:
	__int64 vtable; // 0x00 to 0x08
	char padding0[0x40]; // 0x08 to 0x48
	ccStateMachineFunctions* m_stateFunctions; // 0x48 to 0x50
	char padding1[0x04]; // 0x50 to 0x54
	int m_dword00_54; // 0x54 to 0x58
	char padding2[0x08]; // 0x58 to 0x60
	int m_dword01_60; // 0x60 to 0x64
	char padding3[0x04]; // 0x64 to 0x68
	__int64 m_qword00_68; // 0x68 to 0x70
	__int64 m_qword01_70; // 0x70 to 0x78
	__int64 m_qword02_78; // 0x78 to 0x80
	__int64 m_qword03_80; // 0x80 to 0x88
	__int64 m_qword04_88; // 0x88 to 0x90
	__int64 m_qword05_90; // 0x90 to 0x98
	__int64 m_qword06_98; // 0x98 to 0xA0
	__int64 m_qword07_a0; // 0xA0 to 0xA8
	int m_dword02_A8; // 0xA8 to 0xAC

	static ccSceneBoss12StateMachine * Create(ccSceneBoss12StateMachine* a1)
	{
		return reinterpret_cast<ccSceneBoss12StateMachine*(__fastcall*)(ccSceneBoss12StateMachine*)>(moduleBase + 0x3E367C)(a1);
	}
};

