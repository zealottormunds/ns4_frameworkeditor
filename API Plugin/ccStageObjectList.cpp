#include "ccStageObjectList.h"
#include "ccStageClump.h"

ccStageClump* __fastcall ccStageObjectList::AddClump(ccStageObjectList* a, const char* b, const char* c)
{
	// 0x811F48
	typedef ccStageClump*(__fastcall * funct)(ccStageObjectList* a, const char* b, const char* c);
	funct fc = (funct)(moduleBase + 0x811F48);
	return fc(a, b, c);
}

__int64 __fastcall ccStageObjectList::AddCollision(ccStageObjectList* a1, ccStageClump* a2)
{
	// 0x81208C
	typedef __int64(__fastcall * funct)(ccStageObjectList* a1, ccStageClump* a2);
	funct fc = (funct)(moduleBase + 0x81208C);
	return fc(a1, a2);
}

ccStageAnm * __fastcall ccStageObjectList::AddAnm(ccStageObjectList * a1, const char * path, const char * mesh_anm)
{
	typedef ccStageAnm*(__fastcall * funct)(ccStageObjectList* a1, const char* path, const char* mesh_anm);
	funct fc = (funct)(moduleBase + 0x811E04);
	return fc(a1, path, mesh_anm);
}

__int64 __fastcall ccStageObjectList::Clear(ccStageObjectList * a1)
{
	typedef __int64(__fastcall * funct)(ccStageObjectList* a1);
	funct fc = (funct)(moduleBase + 0x811CE0);
	return fc(a1);
}

void __fastcall ccStageObjectList::DeleteAllCollision(ccStageObjectList * a1)
{
	typedef void(__fastcall * funct)(ccStageObjectList * a1);
	funct fc = (funct)(moduleBase + 0x54A9A4);
	fc(a1);
}

__int64 ccStageObjectList::DeleteClump(ccStageObjectList * a1, ccStageClump * a2)
{
	typedef __int64(__fastcall * funct)(ccStageObjectList * a1, ccStageClump * a2);
	funct fc = (funct)(moduleBase + 0x813A68);
	return fc(a1, a2);
}

__int64 ccStageObjectList::DeleteAnm(ccStageObjectList * a1, ccStageAnm * a2)
{
	typedef __int64(__fastcall * funct)(ccStageObjectList * a1, ccStageAnm * a2);
	funct fc = (funct)(moduleBase + 0x8139C8);
	return fc(a1, a2);
}
