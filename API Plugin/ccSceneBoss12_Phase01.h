#pragma once
#include "ccSceneBoss12StateMachine.h"
#include "ccUiFlash.h"
#include "info_mision.h"

class ccSceneBoss12_Phase01
{
public:
	// Original stuff
	struct params
	{
		ccUiFlash* m_flash;
		info_mision * m_mision;
		bool m_booleans[50];
		int m_timers[50];
	};

	__int64 vtable; // 0x00 to 0x08
	char padding0[0x120]; // 0x08 to 0x128
	ccSceneBoss12StateMachine* m_stateMachine; // 0x128 to 0x130
	__int64 m_unkptr00; // 0x130 to 0x138
	__int64 m_unkptr01; // 0x138 to 0x140
	__int64 m_unkptr02; // 0x140 to 0x148
	params* m_customParam; // 0x148 to 0x150

	static void ReplaceVirtuals();
	static __int64 __fastcall Initialize(ccSceneBoss12_Phase01* a1);
	static void __fastcall Execute(ccSceneBoss12_Phase01* a1);
	static __int64 __fastcall Finalize(ccSceneBoss12_Phase01* a1);
};

