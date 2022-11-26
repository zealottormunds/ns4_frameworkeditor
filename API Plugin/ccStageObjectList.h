#pragma once
#include "Common.h"
#include "ccStageClump.h"
#include "ccStageAnm.h"
#include <vector>

class ccStageObjectList
{
public:
	__int64 vtable; // 0x00 to 0x08
	__int64 m_ptr00; // 0x08 to 0x10
	int m_int00; // 0x10 to 0x14
	int m_int01; // 0x14 to 0x18
	std::vector<__int64> * m_collisionList; // 0x18 to 0x20
	char padding0[0x28]; // 0x20 to 0x48
	std::vector<ccStageBaseClump*> * m_clumpList; // 0x48 to 0x50

	static ccStageClump * __fastcall AddClump(ccStageObjectList* a, const char* b, const char* c);
	static __int64 __fastcall AddCollision(ccStageObjectList* a1, ccStageClump* a2);
	static ccStageAnm * __fastcall AddAnm(ccStageObjectList* a1, const char* path, const char* mesh_anm);
	static __int64 __fastcall Clear(ccStageObjectList* a1);
	static void __fastcall DeleteAllCollision(ccStageObjectList * a1);
	static __int64 DeleteClump(ccStageObjectList* a1, ccStageClump* a2);
	static __int64 DeleteAnm(ccStageObjectList* a1, ccStageAnm * a2);
};