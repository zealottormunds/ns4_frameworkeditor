#pragma once
#include "Common.h"
#include <iostream>
#include "Utilities.h"

class FrameworkScene
{
public:
	virtual __int64 __fastcall delete00(__int64 mem, char a2)
	{
		return 0;
	}

	virtual __int64 __fastcall delete01(__int64 mem)
	{
		return Game::delete_operator(mem);
	}

	virtual __int64 __fastcall pop00(__int64 mem)
	{
		typedef __int64(__fastcall * funct)(__int64 mem);
		funct fc = (funct)(moduleBase + 0xA2D4C0);
		return fc(mem);
	}

	virtual __int64 __fastcall Initialize(__int64 mem)
	{
		delete01((__int64)this);

		return pop00((__int64)this);
	}

	virtual void __fastcall Execute(__int64 mem)
	{
		//return mem;
	}

	virtual __int64 __fastcall Finalize(__int64 mem)
	{
		return mem;
	}

	virtual __int64 __fastcall Activated(__int64 mem)
	{
		return mem;
	}

	virtual __int64 __fastcall Deactivated(__int64 mem)
	{
		return mem;
	}

	virtual __int64 __fastcall Idling(__int64 mem)
	{
		return mem;
	}

	char padding[288];
	int m_var00;
	int m_var01;
	__int64 m_var02;

	static FrameworkScene * Create(const char* sceneName)
	{
		FrameworkScene dummy;
		__int64 vtable = *(__int64*)(&dummy); // get custom vtable for this scene

		__int64 scenePtr = Game::operator_new(0x138, "", 0x2E9); // allocate this scene

		FrameworkScene * sceneTemplate = 0; // reinterpret pointer as template
		sceneTemplate = (FrameworkScene*)(ccScene::Constructor((ccScene*)scenePtr)); // default constructor for scene

		*((__int64*)(sceneTemplate)) = vtable; // write custom vtable to our new scene

		sceneTemplate->m_var00 = 0; // set default variables
		sceneTemplate->m_var01 = 0; // set default variables
		sceneTemplate->m_var02 = 0; // set default variables

		//*(__int64*)(((__int64)(sceneTemplate)) + 296) = 0;
		//*(__int64*)(((__int64)(sceneTemplate)) + 304) = 0;

		ccScene::SetSceneName((ccScene*)sceneTemplate, sceneName);

		return sceneTemplate;
	}
};