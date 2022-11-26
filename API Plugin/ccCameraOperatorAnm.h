#pragma once
#include "Common.h"
#include "nuccAnm.h"

class ccCameraOperatorAnm
{
public:
	static void Attach(ccCameraOperatorAnm * a1, NuccAnm* anm)
	{
		reinterpret_cast<void(__fastcall*)(ccCameraOperatorAnm*, NuccAnm*)>(moduleBase + 0x853BE8)(a1, anm);
	}

	static void Clear(ccCameraOperatorAnm * a1)
	{
		reinterpret_cast<void(__fastcall*)(ccCameraOperatorAnm*)>(moduleBase + 0x853C14)(a1);
	}
};

