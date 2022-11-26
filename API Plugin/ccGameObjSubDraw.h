#pragma once
#include "Common.h"
#include "Vector3.h"

class ccGameObjSubDraw
{
public:
	__int64 vtable; // 0x00 to 0x08
	char padding0[0x10]; // 0x08 to 0x18
	int m_flag07; // 0x18 to 0x1C
	char padding1[0x0C]; // 0x1C to 0x28
	int m_updateAndDraw; // 0x28 to 0x2C
	char padding2[0x38C]; // 0x2C to 0x3B8
	int m_flag11; // 0x3B8 to 0x3BC
	int m_flag12; // 0x3BC to 0x3C0
	char padding3[0x20]; // 0x3C0 to 0x3E0
	int m_flag00; // 0x3E0 to 0x3E4
	char padding4[0x24]; // 0x3E4 to 0x408
	int m_flag01; // 0x408 to 0x40C
	char padding5[0x2464]; // 0x40C to 0x2870
	int m_flag09; // 0x2870 to 0x2874
	char padding6[0xC4]; // 0x2874 to 0x2938
	int m_flag02; // 0x2938 to 0x293C
	char padding7[0x54]; // 0x293C to 0x2990
	int m_flag03; // 0x2990 to 0x2994
	char padding8[0x24]; // 0x2994 to 0x29B8
	int m_flag04; // 0x29B8 to 0x29BC
	char padding9[0x24]; // 0x29BC to 0x29E0
	int m_flag05; // 0x29E0 to 0x29E4
	char padding10[0x24]; // 0x29E4 to 0x2A08
	int m_flag06; // 0x2A08 to 0x2A0C
	char padding11[0x04]; // 0x2A0C to 0x2A10
	int m_flag10; // 0x2A10 to 0x2A14
	char padding12[0x94]; // 0x2A14 to 0x2AA8
	char m_str00; // 0x2AA8 to 0x2AA9
	char padding13[0x37]; // 0x2AA9 to 0x2AE0
	char m_str01; // 0x2AE0 to 0x2AE1
	char padding14[0x37]; // 0x2AE1 to 0x2B18
	char m_str02; // 0x2B18 to 0x2B19
	char padding15[0x37]; // 0x2B19 to 0x2B50
	char m_str03; // 0x2B50 to 0x2B51
	char padding16[0x37]; // 0x2B51 to 0x2B88
	char m_str04; // 0x2B88 to 0x2B89
	char padding17[0x37]; // 0x2B89 to 0x2BC0
	char m_str05; // 0x2BC0 to 0x2BC1
	char padding18[0x37]; // 0x2BC1 to 0x2BF8
	char m_str06; // 0x2BF8 to 0x2BF9
	char padding19[0x37]; // 0x2BF9 to 0x2C30
	char m_str07; // 0x2C30 to 0x2C31

	static __int64 __fastcall GameObjSubDraw(__int64 a1)
	{
		typedef __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0x552218);
		return fc(a1);
	}

	static __int64 __fastcall Create(__int64 obj, __int64 xfbin, const char* bod)
	{
		typedef __int64(__fastcall * funct)(__int64 obj, __int64 xfbin, const char* bod);
		funct fc = (funct)(moduleBase + 0x554550);
		return fc(obj, xfbin, bod);
	}

	static __int64 __fastcall CreateA(__int64 obj, __int64 xfbin, const char* bod)
	{
		typedef __int64(__fastcall * funct)(__int64 obj, __int64 xfbin, const char* bod);
		funct fc = (funct)(moduleBase + 0x553CA4);
		return fc(obj, xfbin, bod);
	}

	static __int64 __fastcall GetCoordByPartialName(ccGameObjSubDraw * gObj, Vector3 * v, const char* coord)
	{
		typedef __int64(__fastcall * funct)(ccGameObjSubDraw * gObj, const char* coord);
		funct fc = (funct)(moduleBase + 0x5577C8);
		return fc(gObj, coord);
	}

	static __int64 __fastcall GetCoordPosByPartialName(ccGameObjSubDraw * gObj, Vector3 * v, const char* coord)
	{
		typedef __int64(__fastcall * funct)(ccGameObjSubDraw * gObj, Vector3 * v, const char* coord);
		funct fc = (funct)(moduleBase + 0x557E50);
		return fc(gObj, v, coord);
	}

	
	//static __
};