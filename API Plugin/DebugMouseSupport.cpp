#include <stdio.h>
#include "Common.h"

#include "Vector3.h"
#include "DebugMouseSupport.h"

#include <winsock2.h>

using namespace std;

void DebugMouseSupport::UpdateMouse()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(NULL, &p);
	Vector3 * mousePos = (Vector3*)(moduleBase + 0x19AB54C);
	mousePos->x = (float)p.x;
	mousePos->y = (float)p.y;
}