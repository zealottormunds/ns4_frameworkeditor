#pragma once
#include "nuccClump.h"

class ccStageBaseClump
{
public:
	__int64 vtable; // 0x00 to 0x08
	__int64 m_unk00; // 0x08 to 0x10
	char padding0[0x08]; // 0x10 to 0x18
	NuccClump* m_nuccClump; // 0x18 to 0x20
	Vector3 m_position; // 0x20 to 0x2C
	float m_rotation4x4[16]; // 0x2C to 0x6C
	Vector3 m_scale; // 0x6C to 0x78
	int m_draw; // 0x78 to 0x7C
	int m_flag00; // 0x7C to 0x80
	int m_isUpdated; // 0x80 to 0x84
};

