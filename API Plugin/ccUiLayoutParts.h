#pragma once
#include "Common.h"

class ccUiLayoutParts
{
public:
	static ccUiLayoutParts * __fastcall CreateSpriteInit(const char* path, const char* namehash, unsigned int a3)
	{
		typedef ccUiLayoutParts *(__fastcall * funct)(const char* path, const char* namehash, unsigned int a3);
		funct fc = (funct)(moduleBase + 0x5EF7B4);
		return fc(path, namehash, a3);
	}

	static void __fastcall CreateObject(__int64 a1)
	{
		reinterpret_cast<void(__fastcall*)(__int64 a1)>(moduleBase + 0xB02C30)(a1);
	}

	static __int64 __fastcall CreateText(__int64 a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(moduleBase + 0xB034B0)(a1); // a1 + 8 = ccUiFont
	}
};