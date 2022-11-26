#pragma once
#include <iostream>
#include "Component.h"
#include <vector>
#include "Vector3.h"

namespace Editor
{
	struct AnimationPoint
	{
		Vector3 position;
		Vector3 scale;

		AnimationPoint()
		{
			position = Vector3();
			scale = Vector3(1, 1, 1);
		}

		AnimationPoint(Vector3 p)
		{
			position = p;
			scale = Vector3(1, 1, 1);
		}

		AnimationPoint(Vector3 p, Vector3 s)
		{
			position = p;
			scale = Vector3(1, 1, 1);
		}
	};

	class Animation : public Component
	{
	private:
		Vector3 initialLerpPos = Vector3();
		Vector3 finalLerpPos = Vector3();

		Vector3 initialLerpScale = Vector3();
		Vector3 finalLerpScale = Vector3();
	public:
		bool legacyMode = false;
		Vector3 anmOffset = Vector3();

		void Start(__int64 obj) override
		{
			componentType = Component::Types::Animation;
			editorObject = obj;
			std::cout << "AddComponent<Animation>() to " << editorObject << std::endl;
		}

		void Update() override
		{
			UpdateAnimation();
		}

		ccStageClump* clump = 0;

		void SetClump(ccStageClump * c)
		{
			clump = c;
		}

		void ClearAnimation()
		{
			animationPoints.clear();
		}

		void AddAnimationPoint(AnimationPoint point)
		{
			animationPoints.push_back(point);
		}

		void SetAnimationNextFrame()
		{
			if (animationPoints.size() <= nextAnmPoint) return;

			initialLerpPos = Vector3(animationPoints[actualAnmPoint].position.x, animationPoints[actualAnmPoint].position.y, animationPoints[actualAnmPoint].position.z);
			finalLerpPos = Vector3(animationPoints[nextAnmPoint].position.x, animationPoints[nextAnmPoint].position.y, animationPoints[nextAnmPoint].position.z);

			initialLerpScale = Vector3(animationPoints[actualAnmPoint].scale.x, animationPoints[actualAnmPoint].scale.y, animationPoints[actualAnmPoint].scale.z);
			finalLerpScale = Vector3(animationPoints[nextAnmPoint].scale.x, animationPoints[nextAnmPoint].scale.y, animationPoints[nextAnmPoint].scale.z);
		}

		std::vector<AnimationPoint> animationPoints;
		int actualAnmPoint = 0;
		int nextAnmPoint = 1;
		const float defaultLerpSpeed = 60;
		float lerpSpeed = 60;
		float actualTime = 0;

		Vector3 Position()
		{
			return Vector3(0, 0, 0);

			//if(x && y && z) return Vector3(*x, *y, *z);
			//else return Vector3();
		}

		Vector3 Scale()
		{
			return Vector3(1, 1, 1);

			//if (sx && sy && sz) return Vector3(*sx, *sy, *sz);
			//else return Vector3();
		}

		void SetPositionLegacy(Vector3 pos)
		{
			__int64 clump_old = (__int64)clump;

			std::cout << "Clump: " << std::hex << clump_old << std::endl;

			*(float*)(clump_old + 72) = pos.x;
			*(float*)(clump_old + 88) = pos.y;
			*(float*)(clump_old + 104) = pos.z;
		}

		void SetScaleLegacy(Vector3 scl)
		{
			__int64 clump_old = (__int64)clump;
			*(float*)(clump_old + 60) = scl.x;
			*(float*)(clump_old + 80) = scl.y;
			*(float*)(clump_old + 100) = scl.z;
		}

		void UpdateAnimation()
		{
			if (clump && animationPoints.size() > 0)
			{
				//std::cout << "Updating anm" << std::endl;

				if (actualTime < lerpSpeed)
				{
					Vector3 actualPos = Vector3::Lerp(&initialLerpPos, &finalLerpPos, actualTime / lerpSpeed) + anmOffset;
					if(legacyMode == false) ccStageClump::SetPosition(clump, &actualPos);
					else SetPositionLegacy(actualPos);

					Vector3 actualScale = Vector3::Lerp(&initialLerpScale, &finalLerpScale, actualTime / lerpSpeed);
					if (legacyMode == false) ccStageClump::SetScale(clump, &actualScale);
					else SetScaleLegacy(actualScale);

					actualTime++;
				}
				else
				{
					Vector3 actualPos = finalLerpPos + anmOffset;
					if (legacyMode == false) ccStageClump::SetPosition(clump, &actualPos);
					else SetPositionLegacy(actualPos);

					Vector3 actualScale = finalLerpScale;
					if (legacyMode == false) ccStageClump::SetScale(clump, &actualScale);
					else SetScaleLegacy(actualScale);

					actualAnmPoint = nextAnmPoint;
					nextAnmPoint++;

					if (nextAnmPoint >= animationPoints.size())
					{
						nextAnmPoint = 0;
					}

					SetAnimationNextFrame();
					actualTime = 0;
				}
			}
		}
	};
}