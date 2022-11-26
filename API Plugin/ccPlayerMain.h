#pragma once
#include "ccGameObjSubDraw.h"

class ccPlayerMain
{
public:
	__int64 vtable; // 0x00 to 0x08
	char padding0[0x68]; // 0x08 to 0x70
	Vector3 m_position; // 0x70 to 0x7C
	char padding1[0x2C]; // 0x7C to 0xA8
	Vector3 m_moveDir; // 0xA8 to 0xB4
	char padding2[0x94]; // 0xB4 to 0x148
	Vector3 m_speedVector; // 0x148 to 0x154
	float m_speedForward; // 0x154 to 0x158
	float m_gravity; // 0x158 to 0x15C
	float m_speedVertical; // 0x15C to 0x160
	char padding3[0xA0]; // 0x160 to 0x200
	float m_modelScale; // 0x200 to 0x204
	char padding4[0x04]; // 0x204 to 0x208
	ccGameObjSubDraw* m_gameObjSubDraw; // 0x208 to 0x210
	char padding5[0x08]; // 0x210 to 0x218
	__int64 m_playerPad; // 0x218 to 0x220
	float m_pad_analogL; // 0x220 to 0x224
	char padding6[0xA64]; // 0x224 to 0xC88
	int m_playerIndex; // 0xC88 to 0xC8C
	int m_characterID; // 0xC8C to 0xC90
	char padding7[0x1C]; // 0xC90 to 0xCAC
	int m_enableInput; // 0xCAC to 0xCB0
	int m_enableControl; // 0xCB0 to 0xCB4
	char padding8[0x04]; // 0xCB4 to 0xCB8
	int m_enableDraw; // 0xCB8 to 0xCBC
	int m_unknownFlag; // 0xCBC to 0xCC0
	int m_PL_ACT_CURRENT; // 0xCC0 to 0xCC4
	int m_PL_ACT_PREVIOUS; // 0xCC4 to 0xCC8
	int m_PL_ACT_NEXT; // 0xCC8 to 0xCCC
	int m_isPlActAvailable; // 0xCCC to 0xCD0
	int m_isPlayerStateAvailable; // 0xCD0 to 0xCD4
	char padding9[0x3AC]; // 0xCD4 to 0x1080
	int m_PL_ANM_CURRENT; // 0x1080 to 0x1084
	float m_PL_ANM_CURRENT_unkFloat; // 0x1084 to 0x1088
	char padding10[0x0C]; // 0x1088 to 0x1094
	float m_PL_ANM_PREVIOUS; // 0x1094 to 0x1098
};