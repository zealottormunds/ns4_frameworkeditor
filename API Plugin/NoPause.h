#pragma once
#include "Utilities.h"

class NoPause
{
public:
	static void Init()
	{
		// Prevent the game from stopping the music
		DWORD dwOld = 0;
		VirtualProtect((void*)(moduleBase + 0xAB7C9D), 4, PAGE_EXECUTE_READWRITE, &dwOld);

		int* returnValue = (int*)(moduleBase + 0xAB7C9D);
		*returnValue = 0;

		VirtualProtect((void*)(moduleBase + 0xAB7C9D), 4, dwOld, &dwOld);
	}

	static void Update()
	{
		int* pauseGame = (int*)(moduleBase + 0x16BCEE8);
		*pauseGame = 1;
	}
};