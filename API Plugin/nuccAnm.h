#pragma once
#include "Common.h"
#include "Vector3.h"

class NuccAnm
{
public:
	__int64 vtable; // 0x00 to 0x08
	char padding0[0x34]; // 0x08 to 0x3C
	int m_actualFrame; // 0x3C to 0x40
	int m_maxFrame; // 0x40 to 0x44
	char padding1[0x12C]; // 0x44 to 0x170
	int m_actualFrameReadOnly; // 0x170 to 0x174

	static __int64 __fastcall nuccAnm(__int64 obj)
	{
		typedef __int64(__fastcall * funct)(__int64 obj);
		funct fc = (funct)(moduleBase + 0xA13EB0);
		return fc(obj);
	}

	static __int64 __fastcall ApplyClump(__int64 anm, __int64 clump)
	{
		typedef __int64(__fastcall * funct)(__int64 anm, __int64 clump);
		funct fc = (funct)(moduleBase + 0xA14930);
		return fc(anm, clump);
	}

	static __int64 __fastcall cmnAnmUtil_Create(const char * path, const char * xfbin)
	{
		typedef __int64(__fastcall * funct)(const char * path, const char * xfbin);
		funct fc = (funct)(moduleBase + 0x8639E8);
		return fc(path, xfbin);
	}

	static __int64 __fastcall SetAnm(NuccAnm* anm, __int64 chunk, int a3, int a4, int a5, int a6)
	{
		typedef __int64(__fastcall* funct)(NuccAnm* anm, __int64 chunk, int a3, int a4, int a5, int a6);
		funct fc = (funct)(moduleBase + 0xA170E0);
		return fc(anm, chunk, a3, a4, a5, a6);
	}

	static void Draw(NuccAnm* anm)
	{
		reinterpret_cast<void(__fastcall*)(NuccAnm* anm)>(moduleBase + 0xA16040)(anm);
	}

	static void Animate(NuccAnm* anm)
	{
		reinterpret_cast<void(__fastcall*)(NuccAnm* anm)>(moduleBase + 0xA14760)(anm);
	}

	static void Update(NuccAnm* anm)
	{
		reinterpret_cast<void(__fastcall*)(NuccAnm* anm)>(moduleBase + 0xA1B190)(anm);
	}
};

struct nuccAnimChunkParams
{
	char padding[64];
	Vector3 position;
	Vector3 rotation;
	char padding2[48];
	float scaleMultiplier;
	Vector3 scale;
	int display;
	float speed;
	int unkBool;
	int isUpdated;
};

struct nuccAnimParams
{
	char padding[32];
	nuccAnimChunkParams * chunkParam;

	void SetPosition(Vector3 pos)
	{
		if (!chunkParam) return;
		chunkParam->position = pos;
	}

	Vector3 GetPosition()
	{
		if (!chunkParam) return Vector3(0, 0, 0);
		else return chunkParam->position;
	}

	void SetRotation(Vector3 rot)
	{
		if (!chunkParam) return;
		chunkParam->rotation = rot;
	}

	void SetScaleMultiplier(float mag)
	{
		if (!chunkParam) return;
		chunkParam->scaleMultiplier = mag;
	}

	float GetScaleMultiplier()
	{
		if (!chunkParam) return 0;
		return chunkParam->scaleMultiplier;
	}

	void SetScale(Vector3 scale)
	{
		if (!chunkParam) return;
		chunkParam->scale = scale;
	}

	Vector3 GetScale()
	{
		if (!chunkParam) return Vector3(0, 0, 0);
		else return chunkParam->scale;
	}

	void SetDisplay(bool display)
	{
		if (!chunkParam) return;

		if (display) chunkParam->display = 1;
		else chunkParam->display = 0;
	}

	void SetSpeed(float spd)
	{
		if (!chunkParam) return;
		chunkParam->speed = spd;
	}

	void Update()
	{
		if (!chunkParam) return;
		chunkParam->isUpdated = 0;
	}
};