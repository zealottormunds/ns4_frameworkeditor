#pragma once
#include "ccStageBaseClump.h"

class ccStageClumpContainer
{
public:
	__int64 vtable; // 0x00 to 0x08
	__int64 m_unk00; // 0x08 to 0x10
	char padding0[0x08]; // 0x10 to 0x18
	ccStageBaseClump* m_stageBaseClump; // 0x18 to 0x20
	char m_name[10]; // 0x20 to 0x30
};

