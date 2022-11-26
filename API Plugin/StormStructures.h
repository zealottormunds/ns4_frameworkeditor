#pragma once
#include "Vector3.h"

class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 forward;

	float GetFov()
	{
		float * fov = (float*)(&position - 0x44);
	}

	float SetFov(float newfov)
	{
		float * fov = (float*)(&position - 0x44);
		*fov = newfov;
	}
};

class PlayerInfo
{
public:
	__int64 base = 0;

	Vector3 * position; // 0x0
	Vector3 * position2; // 0x4
	Vector3 unk1; // 0x8
	Vector3 unk2; // 0xC
	float unk3; // 0x10
	float unk4; // 0x14
	Vector3 * lookDirection; // 0x18
	Vector3 * lookDirectionRead; // 0x1C
	Vector3 * moveDirection; // 0x20

	float * forwardSpeed; // 0xE0
	float * gravity; // 0xE4;
	float * verticalSpeed; // 0xE8;

	PlayerInfo(__int64 address)
	{
		base = address;

		position = (Vector3*)base;
		position2 = (Vector3*)(base + 4);
		lookDirection = (Vector3*)(base + 0x18);
		lookDirectionRead = (Vector3*)(base + 0x1C);
		moveDirection = (Vector3*)(base + 0x20);
		
		forwardSpeed = (float*)(base + 0xE0);
		gravity = (float*)(base + 0xE4);
		verticalSpeed = (float*)(base + 0xE8);
	};
};