#pragma once
#include "Common.h"
#include "Vector3.h"
#include "ccStageBaseClump.h"

class ccStageClump
{
public:
	__int64 vtable; // 0x00 to 0x08
	__int64 m_unk00; // 0x08 to 0x10
	int m_alwaysUpdate; // 0x10 to 0x14
	char padding0[0x04]; // 0x14 to 0x18
	ccStageBaseClump* m_stageBaseClump; // 0x18 to 0x20
	char m_name[10]; // 0x20 to 0x30
	char padding1[0x50]; // 0x30 to 0x80
	int m_flag01; // 0x80 to 0x84
	int m_flag02; // 0x84 to 0x88
	int m_flag03; // 0x88 to 0x8C
	int m_flag04; // 0x8C to 0x90
	__int64 m_unk01; // 0x90 to 0x98
	int m_draw; // 0x98 to 0x9C
	char padding2[0x04]; // 0x9C to 0xA0
	__int64 m_unk02; // 0xA0 to 0xA8
	__int64 m_unk03; // 0xA8 to 0xB0
	Vector3 m_vector00; // 0xB0 to 0xBC

	static __int64 SetPosition(ccStageClump* c, Vector3* pos);
	static __int64 SetRotation(ccStageClump* c, Vector3* rot);
	static __int64 SetScale(ccStageClump* c, Vector3* scale);

	static Vector3 GetPosition(ccStageClump* c)
	{
		__int64 v2 = *(__int64*)((__int64)(c)+24);
		Vector3 result = Vector3(0, 0, 0);

		if (v2)
		{
			Vector3 * objPos = (Vector3*)(v2 + 32);
			result = Vector3(objPos->x, objPos->y, objPos->z);
		}

		return result;
	}

	static Vector3 GetScale(ccStageClump * c)
	{
		__int64 v2 = *(__int64*)((__int64)(c)+24);
		Vector3 result = Vector3(0, 0, 0);

		if (v2)
		{
			Vector3 * objScale = (Vector3*)(v2 + 108);
			result = Vector3(objScale->x, objScale->y, objScale->z);
		}

		return result;
	}

	static ccStageClump * __fastcall StageClump(ccStageClump * a1)
	{
		typedef ccStageClump *(__fastcall * funct)(ccStageClump * a1);
		funct fc = (funct)(moduleBase + 0x80EF24);
		return fc(a1);
	}

	static __int64 CreateClump(ccStageClump * dst, const char * path, const char* mesh)
	{
		typedef __int64(__fastcall * funct)(ccStageClump * dst, const char * path, const char* mesh);
		funct fc = (funct)(moduleBase + 0x80F2C0);
		return fc(dst, path, mesh);
	}

	static __int64 __fastcall Ctrl(ccStageClump * c)
	{
		typedef int(__fastcall * funct)(ccStageClump * c);
		funct fc = (funct)(moduleBase + 0x80F594);
		return fc(c);
	}

	static __int64 __fastcall Draw(ccStageClump * c)
	{
		typedef __int64(__fastcall * funct)(ccStageClump * c);
		funct fc = (funct)(moduleBase + 0x80F5AC);
		return fc(c);
	}
};