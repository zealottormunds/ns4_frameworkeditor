#pragma once
#include "Common.h"
#include "nuccCoord.h"

class NuccClump
{
public:
	/*__int64 vtable; // 0x00 to 0x08
	char padding0[0x10]; // 0x08 to 0x18
	__int64 m_ptr00; // 0x18 to 0x20
	Vector3* m_position; // 0x20 to 0x28
	__int64 m_ptr02; // 0x28 to 0x30
	__int64 m_ptr03; // 0x30 to 0x38
	float m_float00; // 0x38 to 0x3C
	char padding1[0x30]; // 0x3C to 0x6C
	Vector3* m_scale; // 0x6C to 0x74
	char padding2[0x88]; // 0x74 to 0xFC
	Vector3 m_vector00; // 0xFC to 0x108
	Vector3 m_vector01; // 0x108 to 0x114
	char padding3[0x04]; // 0x114 to 0x118
	__int64 m_unkptr00; // 0x118 to 0x120
	int m_unkint00; // 0x120 to 0x124
	short m_flag00; // 0x124 to 0x126
	short m_flag01; // 0x126 to 0x128
	int m_isUpdated; // 0x128 to 0x12C*/

	static __int64 nuccClump(__int64 a1, __int64 anmChunk, __int64 a3, int a4, double a5)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, __int64 anmChunk, __int64 a3, int a4, double a5);
		funct fc = (funct)(moduleBase + 0xA1B4C0);
		return fc(a1, anmChunk, a3, a4, a5);
	}

	static __int64 Draw(NuccClump * nc)
	{
		typedef __int64(__fastcall * funct)(NuccClump* nc);
		funct fc = (funct)(moduleBase + 0xA1DB80);
		return fc(nc);
	}

	static __int64 Update(NuccClump * nc)
	{
		typedef __int64(__fastcall * funct)(NuccClump* nc);
		funct fc = (funct)(moduleBase + 0xA20180);
		return fc(nc);
	}
};