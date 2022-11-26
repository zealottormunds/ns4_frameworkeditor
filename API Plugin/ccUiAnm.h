#pragma once
class ccUiAnm
{
public:
	static void __fastcall RequestPlay(ccUiAnm* a1)
	{
		*(int*)(a1 + 52) = 0; // ccUiAnm * 52 = 208 bytes
	}
};