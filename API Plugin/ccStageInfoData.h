#pragma once
#include "Common.h"
#include "Utilities.h"

class ccStageInfoData
{
public:
	static __int64 __fastcall GetId(__int64 a1)
	{
		typedef __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0x810034);
		return fc(a1);
	}

	static __int64 __fastcall Create(__int64 a1, __int64 a2, __int64 a3, int a4, int a5, int a6, int a7, int a8)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, __int64 a2, __int64 a3, int a4, int a5, int a6, int a7, int a8);
		funct fc = (funct)(moduleBase + 0x812A14);
		return fc(a1, a2, a3, a4, a5, a6, a7, a8);
	}

	static void UndoCreateHook()
	{
		// 48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18
		char unhook[] = { 0x48, 0x8B, 0xC4, 0x48, 0x89, 0x58, 0x08, 0x48, 0x89, 0x70, 0x10, 0x48, 0x89, 0x78, 0x18 };

		DWORD o = Utilities::ChangeProtect(moduleBase + 0x812A14, 15, PAGE_EXECUTE_READWRITE);
		memcpy((void*)(moduleBase + 0x812A14), unhook, 15);
		Utilities::ChangeProtect(moduleBase + 0x812A14, 15, o);
	}

	static __int64 GetLoadFileNum(ccStageInfoData* a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccStageInfoData * a1)>(moduleBase + 0x810064)(a1);
	}

	static const char* GetLoadFileName(ccStageInfoData* a1, int a2)
	{
		return reinterpret_cast<const char*(__fastcall*)(ccStageInfoData* a1, int a2)>(moduleBase + 0x810044)(a1, a2);
	}

	static __int64 __fastcall CreateHook(__int64 a1, __int64 a2, __int64 a3, int a4, int a5, int a6, int a7, int a8);
	static void DoCreateHook();
};