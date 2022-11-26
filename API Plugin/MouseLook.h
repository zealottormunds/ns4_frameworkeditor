#pragma once
#include "Vector3.h"
#include "Component.h"
#include <cmath>

#include <windows.h>

namespace Editor
{
	class MouseLook
	{
	public:
		static MouseLook * instance;

		Vector3 campos = Vector3(0, 0, 0);
		Vector3 camlook = Vector3(0, 0, 0);

		POINT pPrev;
		POINT pNew;

		float camSpeed = 0.5;

		void Update(HWND hwnd)
		{
			GetCursorPos(&pNew);
			ScreenToClient(hwnd, &pNew);

			if (GetKeyState(VK_RBUTTON) & 0x8000)
			{
				// Center cursor
				POINT center;
				center.x = 0;
				center.y = 0;
				ScreenToClient(hwnd, &center);
				//SetCursorPos(center.x, center.y);

				int diff = pNew.x - pPrev.x;
				camlook.x += diff * -camSpeed;

				diff = pNew.y - pPrev.y;
				camlook.y += diff * -camSpeed;
				if (camlook.y > 85) camlook.y = 85;
				if (camlook.y < -85) camlook.y = -85;

				pPrev = pNew;
			}
			else
			{
				pPrev = pNew;
			}
		}

		Vector3 CalculateLookPoint()
		{
			float _cos = cos(ToRad(camlook.x));
			float _sin = sin(ToRad(camlook.x));

			float _cos2 = cos(ToRad(camlook.y));
			float _sin2 = sin(ToRad(camlook.y));

			Vector3 pos = Vector3( _cos * _cos2, _sin * _cos2, _sin2);

			return pos;
		}

		float ToRad(float d)
		{
			return d * 3.14159 / 180;
		}
	};
}