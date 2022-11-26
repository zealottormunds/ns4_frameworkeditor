#pragma once
#include "Common.h"
#include "ccStageObjectList.h"
#include "ccStageManager.h"

class ccStageObjectManager
{
public:
	static ccStageObjectManager* GetManager(ccStageManager* stageManager);
	static __int64 __fastcall GetObjectListNum(ccStageObjectManager* a);
	static ccStageObjectList* __fastcall GetObjectList(ccStageObjectManager* a, int b);
	static __int64 __fastcall Delete(__int64 a, int b);
	static __int64 __fastcall DeleteAll(__int64 a);
	static __int64 __fastcall Create(ccStageObjectManager* a1, unsigned int a2, __int64 a3);
	static ccStageObjectManager* CcStageObjectManager(ccStageObjectManager * a1, unsigned int a2);

	static __int64 __fastcall Ctrl(ccStageObjectManager* a1) { return reinterpret_cast<__int64(__fastcall*)(ccStageObjectManager* a1)>(moduleBase + 0x814C3C)(a1); }
	static __int64 __fastcall Draw(ccStageObjectManager* a1) { return reinterpret_cast<__int64(__fastcall*)(ccStageObjectManager* a1)>(moduleBase + 0x814D84)(a1); }
};
