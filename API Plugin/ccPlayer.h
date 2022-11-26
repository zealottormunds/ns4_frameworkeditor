#pragma once
#include "Common.h"
#include <iostream>

class ccPlayer
{
public:
	static void __fastcall SetActionImmediate(ccPlayer* p, int action)
	{
		/*typedef void(__fastcall * funct)(ccPlayer * p, int action);
		funct fc = (funct)(moduleBase + 0x7ADC9C);
		fc(p, action);*/

		//std::cout << "Setting action" << std::endl;
		return reinterpret_cast<void(__fastcall*)(ccPlayer* p, int action)>(moduleBase + 0x7ADC9C)(p, action);
	}
};