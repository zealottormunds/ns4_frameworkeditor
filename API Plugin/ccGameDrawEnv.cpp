#include "ccGameDrawEnv.h"
#include "Utilities.h"

void ccGameDrawEnv::SetForceDircEnable(bool enable)
{
	int a2 = 0;
	if (enable) a2 = 1;

	typedef void(__fastcall * funct)(__int64 a1, int a2);
	funct fc = (funct)(moduleBase + 0x85F1F0);
	fc(Game::ObjectList_GetPtrLightsAndFog(), a2);
}

void ccGameDrawEnv::SetForceDircParam(Vector3 * c)
{
	typedef __int64(__fastcall * funct)(__int64 a1, Vector3* c);
	funct fc = (funct)(moduleBase + 0x85F1F8);
	fc(Game::ObjectList_GetPtrLightsAndFog(), c);
}