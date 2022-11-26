#pragma once
#include "Common.h"

class ccCmnLightManager
{
public:
	static __int64 Clear(ccCmnLightManager* a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccCmnLightManager*)>(moduleBase + 0xB0BBA0)(a1);
	}

	static __int64 EntryAmbient(ccCmnLightManager* a1, __int64 p_nuccAmbient, int a3)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccCmnLightManager*, __int64, int)>(moduleBase + 0xB0BD10)(a1, p_nuccAmbient, a3);
	}

	static __int64 EntryDirect(ccCmnLightManager* a1, __int64 p_nuccLightDirect, int a3)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccCmnLightManager*, __int64, int)>(moduleBase + 0xB0BDE0)(a1, p_nuccLightDirect, a3);
	}

	static __int64 EntryPoint(ccCmnLightManager* a1, __int64 p_nuccLightPoint, int a3)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccCmnLightManager*, __int64, int)>(moduleBase + 0xB0C110)(a1, p_nuccLightPoint, a3);
	}

	static void EntryPointJump(ccCmnLightManager* a1, __int64 p_nuccLightPoint)
	{
		reinterpret_cast<void(__fastcall*)(ccCmnLightManager*, __int64)>(moduleBase + 0x85C69C)(a1, p_nuccLightPoint);
	}

	struct DirectList
	{
		char content[16];
	};

	static __int64 GetDirects(ccCmnLightManager* a1, DirectList* listPtr, int a3, int a4)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccCmnLightManager*, DirectList*, int, int)>(moduleBase + 0xB0C0B0)(a1, listPtr, a3, a4);
	}

	static void ReleaseAmbient(ccCmnLightManager* a1, __int64 p_nuccAmbient)
	{
		reinterpret_cast<void(__fastcall*)(ccCmnLightManager*, __int64)>(moduleBase + 0xB0BEB0)(a1, p_nuccAmbient);
	}

	static void ReleaseDirect(ccCmnLightManager* a1, __int64 p_nuccLightDirect)
	{
		reinterpret_cast<void(__fastcall*)(ccCmnLightManager*, __int64)>(moduleBase + 0xB0BF70)(a1, p_nuccLightDirect);
	}

	static void ReleasePoint(ccCmnLightManager* a1, __int64 p_nuccLightPoint)
	{
		reinterpret_cast<void(__fastcall*)(ccCmnLightManager*, __int64)>(moduleBase + 0xB0C220)(a1, p_nuccLightPoint);
	}
};