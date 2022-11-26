#pragma once
#include "Common.h"

class ccBossBattleLoader
{
public:
	static void __fastcall Load(__int64 a1, const char* loadName, const char* loadPath, unsigned int flag00)
	{
		reinterpret_cast<void(__fastcall*)(__int64 a1, const char* loadName, const char* loadPath, unsigned int flag00)>(moduleBase + 0x420680)(a1, loadName, loadPath, flag00);
	}

	static void __fastcall LoadFileTable(__int64 a1, const char* loadName, __int64 loadList)
	{
		reinterpret_cast<void(__fastcall*)(__int64 a1, const char* loadName, __int64 loadList)>(moduleBase + 0x420708)(a1, loadName, loadList);
	}

	static void __fastcall LoadFlashTable(__int64 a1, const char* loadName, __int64 loadList)
	{
		reinterpret_cast<void(__fastcall*)(__int64 a1, const char* loadName, __int64 loadList)>(moduleBase + 0x420770)(a1, loadName, loadList);
	}
};

