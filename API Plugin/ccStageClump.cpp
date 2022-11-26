#include "ccStageClump.h"

__int64 ccStageClump::SetPosition(ccStageClump* c, Vector3* pos)
{
	typedef __int64(__fastcall * funct)(ccStageClump * c, Vector3* pos);
	funct fc = (funct)(moduleBase + 0x80F740);
	return fc(c, pos);
}

__int64 ccStageClump::SetRotation(ccStageClump* c, Vector3* rot)
{
	//typedef __int64(__fastcall * funct)(ccStageClump * c, Vector3* rot);
	//funct fc = (funct)(moduleBase + 0x80F740);
	//return fc(c, pos);
	return 0;
}

__int64 ccStageClump::SetScale(ccStageClump* c, Vector3* scale)
{
	typedef __int64(__fastcall * funct)(ccStageClump * c, Vector3* scale);
	funct fc = (funct)(moduleBase + 0x80F9A8);
	return fc(c, scale);
	return 0;
}