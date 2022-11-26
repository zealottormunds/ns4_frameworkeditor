#pragma once
#include "ccPlayerContainer.h"
#include "Utilities.h"

class ccDuelTeam
{
public:
	static ccDuelTeam * GetTeam(unsigned int PLAYER_SIDE)
	{
		__int64 ptr = BattleUtils::GetPlayerContainer(PLAYER_SIDE);
		return (ccDuelTeam*)(ptr);
	}

	ccPlayerContainer * m_leader;
	ccPlayerContainer * m_supportA;
	ccPlayerContainer * m_supportB;
};