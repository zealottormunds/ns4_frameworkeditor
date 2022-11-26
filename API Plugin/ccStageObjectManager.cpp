#include "ccStageObjectManager.h"

ccStageObjectManager * ccStageObjectManager::GetManager(ccStageManager * stageManager)
{
	typedef ccStageObjectManager *(__fastcall * funct)(ccStageManager * stageManager);
	funct fc = (funct)(moduleBase + 0x187DE0);
	return fc(stageManager);
}

__int64 __fastcall ccStageObjectManager::GetObjectListNum(ccStageObjectManager* a)
{
	typedef __int64(__fastcall * funct)(ccStageObjectManager* a);
	funct fc = (funct)(moduleBase + 0x814EAC);
	return fc(a);
}

ccStageObjectList* __fastcall ccStageObjectManager::GetObjectList(ccStageObjectManager* a, int b)
{
	typedef ccStageObjectList*(__fastcall * funct)(ccStageObjectManager* a, int b);
	funct fc = (funct)(moduleBase + 0x814E80);
	return fc(a, b);
}

__int64 __fastcall ccStageObjectManager::Delete(__int64 a, int b)
{
	typedef __int64(__fastcall * funct)(__int64 a, int b);
	funct fc = (funct)(moduleBase + 0x814CA0);
	return fc(a, b);
}

__int64 __fastcall ccStageObjectManager::DeleteAll(__int64 a)
{
	typedef __int64(__fastcall * funct)(__int64 a);
	funct fc = (funct)(moduleBase + 0x814CFC);
	return fc(a);
}

__int64 __fastcall ccStageObjectManager::Create(ccStageObjectManager * a1, unsigned int a2, __int64 a3)
{
	return reinterpret_cast<__int64(__fastcall*)(ccStageObjectManager* a1, unsigned int a2, __int64 a3)>(moduleBase + 0x814B18)(a1, a2, a3);
}

ccStageObjectManager * ccStageObjectManager::CcStageObjectManager(ccStageObjectManager * a1, unsigned int a2)
{
	return reinterpret_cast<ccStageObjectManager*(__fastcall*)(ccStageObjectManager * a1, unsigned int a2)>(moduleBase + 0x814988)(a1, a2);
}
