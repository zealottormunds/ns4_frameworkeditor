#include "ScenePatcher.h"
#include "ccSceneManager.h"

__int64 ScenePatcher::sceneList = 0;
int ScenePatcher::totalSceneCount = 0;
std::vector<ScenePatcher::customSceneData*> ScenePatcher::scenePtrList;

__int64 __fastcall ScenePatcher::InitializeScenes(__int64 a1)
{
	// Get scene list from original game
	int sceneCount = ccSceneManager::defaultSceneCount;
	totalSceneCount = sceneCount + scenePtrList.size();
	sceneList = (__int64)malloc(totalSceneCount * 0x90);
	memcpy((void*)sceneList, (void*)(moduleBase + ccSceneManager::defaultSceneList - 0x140000C00), sceneCount * 0x90);

	// Write new scenes
	for (int x = 0; x < scenePtrList.size(); x++)
	{
		customSceneData * d = scenePtrList[x];

		int id = d->id;
		__int64 createFunction = d->createPointer;

		__int64 startAddress = sceneList + ((sceneCount + x) * 0x90);
		*(int*)(startAddress) = id;
		*(__int64*)(startAddress + 8) = createFunction;
		memcpy((void*)(startAddress + 0x10), (void*)(d->name.c_str()), d->name.length());
	}

	// Continue as normal
	__int64 sceneAddress = sceneList;
	const char* sceneName = (const char*)(sceneList + 0x10);

	__int64 result = 0;
	for (int x = 0; x < totalSceneCount; x++)
	{
		sceneAddress += 0x90;
		sceneName = (const char*)(sceneAddress + 0x10);
		result = ccSceneManager::EntryCreateSceneCommandJump(ccSceneManager::GetInstance(), sceneName, *(int*)sceneAddress, *(__int64*)(sceneAddress + 8));
	}

	return result;
}