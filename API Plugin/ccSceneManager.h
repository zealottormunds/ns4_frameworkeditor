#include "Common.h"

class ccSceneManager
{
public:
	static __int64 defaultSceneList;
	static int defaultSceneCount;

	static ccSceneManager* GetInstance() // For permanent objects
	{
		return (ccSceneManager*)*((__int64*)(moduleBase + 0x1416BDA18 - 0x140000C00));
	}

	static __int64 __fastcall Push(ccSceneManager* sceneManager, unsigned int s)
	{
		typedef __int64(__fastcall * funct)(ccSceneManager* sceneManager, unsigned int s);
		funct fc = (funct)(moduleBase + 0xAB4D20);
		return fc(sceneManager, s);
	}

	static __int64 __fastcall Pop(ccSceneManager* sceneManager)
	{
		typedef __int64(__fastcall * funct)(ccSceneManager* sceneManager);
		funct fc = (funct)(moduleBase + 0xAB5020);
		return fc(sceneManager);
	}

	static __int64 __fastcall PopAll(ccSceneManager* sceneManager)
	{
		typedef __int64(__fastcall * funct)(ccSceneManager* sceneManager);
		funct fc = (funct)(moduleBase + 0xAB5410);
		return fc(sceneManager);
	}

	static __int64 __fastcall Execute(ccSceneManager* sceneManager)
	{
		typedef __int64(__fastcall * funct)(ccSceneManager* sceneManager);
		funct fc = (funct)(moduleBase + 0xAB4C10);
		return fc(sceneManager);
	}

	static void __fastcall Change(ccSceneManager* sceneManager, unsigned int a2)
	{
		typedef void(__fastcall * funct)(ccSceneManager* a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0xAB54D0);
		fc(sceneManager, a2);
	}

	static __int64 __fastcall PushPromptly(ccSceneManager* sceneManager, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(ccSceneManager* a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0xAB4EA0);
		return fc(sceneManager, a2);
	}

	static __int64 __fastcall PopTo(ccSceneManager* sceneManager, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(ccSceneManager* a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0xAB52C0);
		return fc(sceneManager, a2);
	}

	static __int64 __fastcall SearchSceneRank(ccSceneManager* sceneManager, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(ccSceneManager* a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0xAB5B00);
		return fc(sceneManager, a2);
	}

	static __int64 __fastcall EntryCreateSceneCommandJump(ccSceneManager* a1, const char* sceneName, int sceneNumber, __int64 sceneAddress)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccSceneManager* a1, const char* sceneName, int sceneNumber, __int64 sceneAddress)>(moduleBase + 0x6E436C)(a1, sceneName, sceneNumber, sceneAddress);
	}

	static __int64 __fastcall GetCurrentSceneKey(ccSceneManager* a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccSceneManager* a1)>(moduleBase + 0xAB5A70)(a1);
	}

	static const char * GetSceneNameByKey(__int64 sceneList, int totalSceneCount, int sceneKey)
	{
		int sceneIndexInList = -1;

		for (int x = 0; x < totalSceneCount; x++)
		{
			if (*(int*)(sceneList + 0x90 * x) == sceneKey)
			{
				sceneIndexInList = x;
				x = totalSceneCount;
				break;
			}
		}

		const char* sceneName = "[null]";

		if (sceneIndexInList != -1)
		{
			sceneName = (const char*)((sceneList + 0x10) + (0x90 * sceneIndexInList));
		}

		return sceneName;
	}
};
