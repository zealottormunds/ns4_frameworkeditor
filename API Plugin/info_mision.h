#pragma once
#include "Common.h"

class info_mision
{
public:
	static info_mision* AllocateAndCreate();

	static info_mision* Create(info_mision * a1)
	{
		return reinterpret_cast<info_mision*(__fastcall*)(info_mision*)>(moduleBase + 0x474E28)(a1);
	}

	static info_mision* Initialize(info_mision * a1)
	{
		return reinterpret_cast<info_mision*(__fastcall*)(info_mision*)>(moduleBase + 0x474ED4)(a1);
	}
	
	static info_mision* SetOpen(info_mision * a1, const char* msg, int a2, int a3, int a4)
	{
		return reinterpret_cast<info_mision*(__fastcall*)(info_mision *, const char*, int, int, int)>(moduleBase + 0x47504C)(a1, msg, a2, a3, a4);
	}

	static info_mision* SetClose(info_mision * a1)
	{
		return reinterpret_cast<info_mision*(__fastcall*)(info_mision*)>(moduleBase + 0x475008)(a1);
	}
};

