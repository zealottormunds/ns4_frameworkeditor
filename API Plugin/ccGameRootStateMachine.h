#pragma once
#include "Common.h"

class ccGameRootStateMachine
{
public:
	static ccGameRootStateMachine * GetInstance()
	{
		ccGameRootStateMachine * a = (ccGameRootStateMachine*)(moduleBase + 0x14161C890 - 0x140000C00);
		return a;
	}

	static __int64 __fastcall CreateBtlParam(ccGameRootStateMachine* root)
	{
		typedef __int64(__fastcall * funct)(ccGameRootStateMachine * root);
		funct fc = (funct)(moduleBase + 0x530C0C);
		return fc(root);
	}

	static void __fastcall EnterLoadCmn(ccGameRootStateMachine* root)
	{
		typedef void(__fastcall * funct)(ccGameRootStateMachine * root);
		funct fc = (funct)(moduleBase + 0x855200);
		return fc(root);
	}
};