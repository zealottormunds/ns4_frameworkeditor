#pragma once
#include "Common.h"
#include "LuaMachine.h"
#include <vector>

class CustomStageSelect
{
public:
	static CustomStageSelect* css;
	static __int64 window;

	struct StageInfoGame
	{
		__int64 unk00;
		__int64 unk01;
		int unk02;
		int index;
		char stageName[0x20];
		char stageId[0x20];
		int unk03;
		int index2;
		__int64 unk04;
		__int64 unk05;
	};

	struct StageInfoFramework
	{
		int stageIndex;
		std::string stageId;
		std::string stageMsg;
	};

	int currentSelection = 0;
	int currentPage = 0;
	std::vector<StageInfoFramework*> stageList;

	static __int64 GetStageInfo()
	{
		__int64 ptr = *(__int64*)(moduleBase + 0x14161C938 - 0x140000C00);
		ptr = *(__int64*)(ptr + 64);
		return ptr;
	}

	void ParseStageInfo()
	{
		stageList.clear();
		StageInfoGame * stage = (StageInfoGame*)(GetStageInfo());
		int prevIndex = stage->index - 1;
		std::cout << "Info: " << std::hex << stage << std::endl;

		while (stage->index == prevIndex + 1 && stage->unk05 == 0x73)
		{
			StageInfoFramework * newStage = new StageInfoFramework();
			newStage->stageIndex = stage->index;
			newStage->stageId = std::string(&(stage->stageId[0]));
			newStage->stageMsg = std::string(&(stage->stageName[0]));

			std::cout << newStage->stageId << ", " << newStage->stageMsg << std::endl;
			prevIndex = stage->index;

			stageList.push_back(newStage);
			stage = (StageInfoGame*)((__int64)(stage) + 0x70);
		}
	}

	static void UpdateGUI();

	static void __fastcall Show(__int64 a1, int a2)
	{
		if (css) Close();

		unnamed::ccIa_FadeIn(30, 1, 1, 1);
		css = new CustomStageSelect();
		css->currentSelection = 0;
		css->ParseStageInfo();

		// 14161C8E8
		//ccUiSelectWindow * v3 = (ccUiSelectWindow*)(moduleBase + 0x14161C8E8 - 0x140000C00);
		//ccUiSelectList::PushKeyHelp(v3);
	}

	static __int64 __fastcall ChangeSelection(__int64 a1, __int64 a2);
	
	static void Close()
	{
		delete css;
		css = nullptr;
	}

	static void Hook()
	{
		typedef void(__stdcall *HookFunct)(void* toHook, void* ourFunct, int len);
		HookFunct Hook = (HookFunct)hookFunct;
		Hook((void*)(moduleBase + 0x68B93C), Show, 14);
	}
};