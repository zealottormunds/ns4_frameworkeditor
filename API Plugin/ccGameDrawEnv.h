#pragma once
#include "Common.h"
#include "Vector3.h"
#include "ccCmnLightManager.h"
#include "nuccFogParam.h"
#include "ccCmnScreenManager.h"

class ccGameDrawEnv
{
public:
	__int64 vtable; // 0x00 to 0x08
	char padding0[0x18]; // 0x08 to 0x20
	ccCmnLightManager* m_cmnLightManager; // 0x20 to 0x28
	char padding1[0x318]; // 0x28 to 0x340
	nuccFogParam* m_nuccFogParam; // 0x340 to 0x348
	char padding2[0x20F8]; // 0x348 to 0x2440
	ccCmnScreenManager* m_cmnScreenManager; // 0x2440 to 0x2448

	static void ReleaseLightAll(ccGameDrawEnv* a1)
	{
		reinterpret_cast<void(__fastcall*)(ccGameDrawEnv*)>(moduleBase + 0x85D670)(a1);
	}

	static __int64 GetFogParamPtr(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C8EC);
		return fc(a1, a2);
	}

	static void SetFogParam(__int64 a1, unsigned int a2, __int64 color, float near_, float far_, float clampfar)
	{
		typedef void(__fastcall * funct)(__int64 a1, unsigned int a2, __int64 color, float near_, float far_, float clampfar);
		funct fc = (funct)(moduleBase + 0x85F14C);
		fc(a1, a2, color, near_, far_, clampfar);
	}

	static __int64 ccInitNoise(int a1)
	{
		typedef __int64(__fastcall * funct)(int a1);
		funct fc = (funct)(moduleBase + 0x536BE4);
		return fc(a1);
	}

	static __int64 ClearCelShadeParam(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C344);
		return fc(a1, a2);
	}

	static __int64 ClearFogParam(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C3B0);
		return fc(a1, a2);
	}

	static __int64 ClearShadowParam(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C430);
		return fc(a1, a2);
	}

	static __int64 ClearGlareParam(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C404);
		return fc(a1, a2);
	}

	static __int64 ClearSoftFocusParam(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C4B0);
		return fc(a1, a2);
	}

	static __int64 ClearDoFParam(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C394);
		return fc(a1, a2);
	}

	static __int64 ClearMotBlurParam(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C420);
		return fc(a1, a2);
	}

	static __int64 ResetCmnBlurParam(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C350);
		return fc(a1, a2);
	}

	static __int64 ResetColorConvParam(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C378);
		return fc(a1, a2);
	}

	static void sub_14085D0C8(ccGameDrawEnv* a1, unsigned int a2)
	{
		typedef void(__fastcall * funct)(ccGameDrawEnv* a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C4C8);
		fc(a1, a2);
	}

	static void sub_14085EB70(ccGameDrawEnv* a1, unsigned int a2)
	{
		typedef void(__fastcall * funct)(ccGameDrawEnv* a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85DF70);
		fc(a1, a2);
	}

	static __int64 sub_14085FE78(ccGameDrawEnv* a1, unsigned int a2, unsigned int a3)
	{
		typedef __int64(__fastcall * funct)(ccGameDrawEnv* a1, unsigned int a2, unsigned int a3);
		funct fc = (funct)(moduleBase + 0x85F278);
		return fc(a1, a2, a3);
	}

	static void * sub_14085D164(__int64 a1, unsigned int a2)
	{
		typedef void* (__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85C564);
		return fc(a1, a2);
	}

	static __int64 sub_14085E304(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85D704);
		return fc(a1, a2);
	}

	static __int64 sub_14085E398(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85D798);
		return fc(a1, a2);
	}

	static __int64 sub_14085E3F8(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85D7F8);
		return fc(a1, a2);
	}

	static __int64 sub_14085E458(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x85D858);
		return fc(a1, a2);
	}

	static void SetForceDircEnable(bool enable);
	static void SetForceDircParam(Vector3 * c);

	static __int64 nuccColorFilterDirectionalGetPtr(int a1)
	{
		typedef __int64(__fastcall * funct)(int a1);
		funct fc = (funct)(moduleBase + 0x42D708);
		return fc(a1);
	}

	static void nuccColorFilterDirectionalSetColor(__int64 colorFilterPtr, Vector4* color1, Vector4* color2, Vector4* color3)
	{
		typedef void(__fastcall * funct)(__int64 colorFilterPtr, Vector4* color1, Vector4* color2, Vector4* color3);
		funct fc = (funct)(moduleBase + 0xA55920);
		fc(colorFilterPtr, color1, color2, color3);
	}

	static __int64 ResetCelShadeParam(ccGameDrawEnv* a1, unsigned int a2) { return reinterpret_cast<__int64(__fastcall*)(ccGameDrawEnv* a1, unsigned int a2)>(moduleBase + 0x85D730)(a1, a2); }
	static __int64 ResetFogParam(ccGameDrawEnv* a1, unsigned int a2) { return reinterpret_cast<__int64(__fastcall*)(ccGameDrawEnv* a1, unsigned int a2)>(moduleBase + 0x85DBF8)(a1, a2); }
	static __int64 ResetShadowParam(ccGameDrawEnv* a1, unsigned int a2) { return reinterpret_cast<__int64(__fastcall*)(ccGameDrawEnv* a1, unsigned int a2)>(moduleBase + 0x85DE78)(a1, a2); }
	static __int64 ResetGlareParam(ccGameDrawEnv* a1, unsigned int a2) { return reinterpret_cast<__int64(__fastcall*)(ccGameDrawEnv* a1, unsigned int a2)>(moduleBase + 0x85DC84)(a1, a2); }
	static __int64 ResetSoftfocusParam(ccGameDrawEnv* a1, unsigned int a2) { return reinterpret_cast<__int64(__fastcall*)(ccGameDrawEnv* a1, unsigned int a2)>(moduleBase + 0x85DEF8)(a1, a2); }
	static __int64 ResetColorConvParam(ccGameDrawEnv* a1, unsigned int a2) { return reinterpret_cast<__int64(__fastcall*)(ccGameDrawEnv* a1, unsigned int a2)>(moduleBase + 0x85D740)(a1, a2); }
	static __int64 SetColorConvEnable(ccGameDrawEnv* a1, unsigned int a2) { return reinterpret_cast<__int64(__fastcall*)(ccGameDrawEnv* a1, unsigned int a2)>(moduleBase + 0x85DB80)(a1, a2); }
};