#pragma once
#include "Common.h"

class ccStageInfoManager
{
public:
	static __int64 __fastcall Create(ccStageInfoManager* a)
	{
		typedef __int64(__fastcall * funct)(ccStageInfoManager * a);
		funct fc = (funct)(moduleBase + 0x810584);
		return fc(a);
	}

	static __int64 __fastcall GetStageInfoData(ccStageInfoManager * a1, unsigned int a2)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccStageInfoManager * a1, unsigned int a2)>(moduleBase + 0x8106BC)(a1, a2);
	}
};