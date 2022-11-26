#pragma once
#include "Utilities.h"
#include "ccUiFlash.h"

class ccSceneGameModeSelect
{
public:
	virtual void __fastcall Function_00() = 0;
	virtual void __fastcall Function_08() = 0;
	virtual void __fastcall Function_16() = 0;
	virtual void __fastcall Function_24() = 0;
	virtual void __fastcall Function_32() = 0;
	virtual void __fastcall Function_40() = 0;
	virtual void __fastcall Function_48() = 0;
	virtual void __fastcall Function_56() = 0;
	virtual void __fastcall Function_64() = 0;
	virtual void __fastcall Function_72() = 0;
	virtual void __fastcall Function_80() = 0;
	virtual void __fastcall Function_88(...) = 0;
	virtual void __fastcall Function_96() = 0;
	virtual void __fastcall Function_104(__int64, int) = 0;
	virtual void __fastcall Function_112() = 0;
	virtual void __fastcall Function_120() = 0;

	static void __fastcall ShowEula(ccSceneGameModeSelect * scene)
	{
		__int64 a1 = (__int64)(scene);

		__int64 v2 = 0; // Function
		__int64 v3 = 0;
		__int64 v4 = 0;

		v2 = *((__int64*)(a1 + 0x68));
		v3 = 0;

		if (v2)
		{
			typedef void(__fastcall * funct)(__int64, __int64);
			__int64 * v2temp = (__int64*)(v2);
			v2temp = (__int64*)(*v2temp);
			v2temp = (__int64*)(*v2temp);

			funct fc = (funct)v2temp;
			fc(v2, 1);

			// funct 
			*(__int64*)(a1 + 104) = 0;
		}

		*((__int64*)(a1 + 436)) = 1;
		*((__int64*)(a1 + 96)) = 1;
		*((__int64*)(a1 + 84)) = 1;
		return;

		/*if(acceptedEula == 1)
		{
			*(a1 + 436) = 1;
			*(a1 + 96) = 1;
			*(a1 + 84) = 1;
		}
		else*/
		{
			std::cout << "Opening eula..." << std::endl;

			v4 = Game::operator_new(0x98, "", 0x24);
			if (v4)
				v3 = ccUiFlash::ccUiFlashEulaCheck(v4);
			*(__int64*)(a1 + 104) = v3;
		}
	}
};