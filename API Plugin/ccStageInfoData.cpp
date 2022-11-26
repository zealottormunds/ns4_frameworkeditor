#include "ccStageInfoData.h"

__int64 __fastcall ccStageInfoData::CreateHook(__int64 a1, __int64 a2, __int64 a3, int a4, int a5, int a6, int a7, int a8)
{
	const char * stageId = (const char*)(ccStageInfoData::GetId(a2));
	std::string stageIdStr = std::string(stageId);
	std::cout << "StageID: " << stageIdStr << std::endl;

	UndoCreateHook();
	__int64 ret = Create(a1, a2, a3, a4, a5, a6, a7, a8);
	DoCreateHook();

	return ret;
}

void ccStageInfoData::DoCreateHook()
{
	HookFunct Hook = (HookFunct)hookFunct;
	Hook((void*)(moduleBase + 0x812A14), ccStageInfoData::CreateHook, 15);
}
