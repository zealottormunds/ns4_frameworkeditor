#pragma once
#include "Common.h"

class ccUiFlash
{
public:
	static __int64 __fastcall Create(const char* a1)
	{
		typedef __int64(__fastcall * funct)(const char* a1);
		funct fc = (funct)(moduleBase + 0x606B40);
		return fc(a1);
	}

	static __int64 __fastcall ccUiFlashEulaCheck(__int64 mem)
	{
		typedef __int64(__fastcall * funct)(__int64 mem);
		funct fc = (funct)(moduleBase + 0x65BFC0);
		return fc(mem);
	}

	static __int64 __fastcall LoadFileMaybe(ccUiFlash * a1, const char* a2, int a3)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccUiFlash * a1, const char* a2, int a3)>(moduleBase + 0x9A3240)(a1, a2, a3);
	}

	static void __fastcall InvokeFunction(ccUiFlash * a1, const char* key, const char* symbol, const char* function, __int64 a2, __int64 a3, int a4)
	{
		return reinterpret_cast<void(__fastcall*)(ccUiFlash * a1, const char* key, const char* symbol, const char* function, __int64 a2, __int64 a3, int a4)>(moduleBase + 0x606FA0)(a1, key, symbol, function, a2, a3, a4);
	}

	static void __fastcall SetVariable(ccUiFlash * a1, const char* key, const char* symbol, const char* variable, __int64 a2)
	{
		reinterpret_cast<void(__fastcall*)(ccUiFlash * a1, const char* key, const char* symbol, const char* function, __int64 a2)>(moduleBase + 0x607178)(a1, key, symbol, variable, a2);
	}

	static void __fastcall GetVariable(ccUiFlash * a1, const char* key, const char* symbol, const char* variable, __int64 a2)
	{
		reinterpret_cast<void(__fastcall*)(ccUiFlash * a1, const char* key, const char* symbol, const char* function, __int64 a2)>(moduleBase + 0x606E7C)(a1, key, symbol, variable, a2);
	}
};