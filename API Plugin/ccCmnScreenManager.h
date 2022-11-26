#pragma once
#include "ccCmnCameraDirector.h"
#include "Common.h"

class ccCmnScreenManager
{
public:
	static ccCmnScreenManager* GetInstance()
	{
		// 14161C780
		return (ccCmnScreenManager*)*((__int64*)(moduleBase + 0x14161C780 - 0x140000C00));
	}

	static ccCmnCameraDirector* __fastcall GetCameraDirector(ccCmnScreenManager* cmnscreenmanager, int id)
	{
		typedef __int64(__fastcall * funct)(ccCmnScreenManager* a1, int id);
		funct fc = (funct)(moduleBase + 0xAB3C30);
		return (ccCmnCameraDirector*)fc(cmnscreenmanager, id);
	}
};