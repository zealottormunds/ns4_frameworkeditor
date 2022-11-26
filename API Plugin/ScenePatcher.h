#pragma once
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "FrameworkScene.h"

class ScenePatcher
{
public:
	static __int64 sceneList;
	static int totalSceneCount;

	struct customSceneData
	{
		std::string name;
		int id;
		__int64 createPointer;
	};

	static std::vector<customSceneData*> scenePtrList;

	static bool AddCustomScene(std::string name, int id, void* createPointer)
	{
		customSceneData * thisData = new customSceneData();
		thisData->name = name;
		thisData->id = id;
		thisData->createPointer = (__int64)createPointer;
		scenePtrList.push_back(thisData);
	}

	static __int64 __fastcall InitializeScenes(__int64 a1);
};