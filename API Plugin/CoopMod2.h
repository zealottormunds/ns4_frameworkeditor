#pragma once
#include "Utilities.h"
#include <iostream>
#include "ccPlayerMain.h"

class CoopMod2
{
public:
	static bool EnableCoopMod;

	static bool waitToEnable;
	static bool isReady;
	static ccPlayerMain *  p1_prev;
	static ccPlayerMain * p1;
	static ccPlayerMain *  p2_prev;
	static ccPlayerMain *  p2;
	static __int64 ai;

	CoopMod2()
	{
		p1_prev = 0;
		p1 = 0;
		p2_prev = 0;
		p2 = 0;
		ai = 0;
	}

	static void Loop()
	{
		p1 = BattleUtils::ccGame_GetPlayerLeader(0);
		p2 = BattleUtils::ccGame_GetPlayerLeader(1);

		if (!p1 || !p2)
		{
			isReady = false;
			ai = 0;
		}

		// When a battle starts
		if (!p1_prev && p1 && waitToEnable == false)
		{
			waitToEnable = true;
		}

		if (p2 != nullptr && waitToEnable)
		{
			__int64 ai_pos = (__int64)(p2) + 0xB40;
			ai = *(__int64*)(ai_pos);

			if (ai != 0)
			{
				std::cout << "Battle Started. P2: " << std::hex << p2 << ", AI: " << std::hex << ai << std::endl;
				waitToEnable = false;
				isReady = true;
			}
			else
			{
				std::cout << "AI is 0" << std::endl;
			}
		}

		if (isReady && p1 != 0 && p2 != 0)
		{
			*(__int64*)(p1 + 0xB40) = ai;
			*(__int64*)(p2 + 0xB40) = 0;

			*(int*)(p1 + 0x840) = -1;
			*(int*)(p2 + 0x840) = 0;
		}

		p1_prev = p1;
		p2_prev = p2;
	}
};