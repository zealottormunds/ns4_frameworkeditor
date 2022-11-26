#pragma once
#include "Common.h"
#include "nuccAnm.h"

class ccAdvBaseAnm
{
public:
	__int64 vtable; // 0x00 to 0x08
	NuccAnm* m_nuccAnm; // 0x08 to 0x10
	__int64 m_qword_10; // 0x10 to 0x18
	__int64 m_qword_18; // 0x18 to 0x20
	__int64 m_qword_20; // 0x20 to 0x28
	char padding0[0x18]; // 0x28 to 0x40
	Vector3 m_position; // 0x40 to 0x4C
	float m_rotation[16]; // 0x4C to 0x8C
	Vector3 m_scale; // 0x8C to 0x98
	int m_display; // 0x98 to 0x9C
	float m_anmSpeed; // 0x9C to 0xA0
	int m_flag_A0; // 0xA0 to 0xA4
	int m_isUpdated; // 0xA4 to 0xA8
	int m_flag_A8; // 0xA8 to 0xAC

	static __int64 SetAnm(ccAdvBaseAnm* base, const char* path, const char* anm)
	{
		typedef __int64(__fastcall * funct)(ccAdvBaseAnm* base, const char* path, const char* anm);
		funct fc = (funct)(moduleBase + 0x47DC84);
		return fc(base, path, anm);
	}
};