#pragma once
#include "Common.h"
#include "ccStageObjectList.h"

class ccStageManager
{
public:
	__int64 m_unkptr00;
	__int64 m_unkptr01;
	__int64 m_unkptr02;

	static ccStageManager * GetInstance()
	{
		__int64 a = *(__int64*)(moduleBase + 0x141617840 - 0x140000C00);

		return (ccStageManager*)(a);
	}

	static void CreateInstance()
	{
		reinterpret_cast<void(__fastcall*)()>(moduleBase + 0x810B9C)();
	}

	static void SetStageObject(ccStageManager * stageManager, int a2, __int64 stageObjectManager)
	{
		reinterpret_cast<void(__fastcall*)(ccStageManager * stageManager, int a2, __int64 stageObjectManager)>(moduleBase + 0x810C18)(stageManager, a2, stageObjectManager);
	}
};