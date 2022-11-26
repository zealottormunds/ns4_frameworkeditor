#include "CustomStageSelect.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGUI/imgui_impl_win32.h"

#include "GraphicSettings.h"

#include <xmmintrin.h>
#include <emmintrin.h>

CustomStageSelect* CustomStageSelect::css;
__int64 CustomStageSelect::window = 0;

__int64 __fastcall CustomStageSelect::ChangeSelection(__int64 a1, __int64 a2)
{
	return 0;

	// 48 89 5C 24 08 55 48 8B  EC 48 83 EC 70 48 8B 42 30
	char unpatch[] = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x55, 0x48, 0x8B, 0xEC, 0x48, 0x83, 0xEC, 0x70, 0x48, 0x8B, 0x42, 0x30 };

	// Undo hook
	DWORD dwOld = Utilities::ChangeProtect(moduleBase + 0x68B770, 17, PAGE_EXECUTE_READWRITE);
	memcpy((void*)(moduleBase + 0x68B770), &unpatch[0], 17);
	Utilities::ChangeProtect(moduleBase + 0x68B770, 17, dwOld);

	int page = 1;
	__int64 actualStagePtr = *(__int64*)(a2 + 32);
	double * actualStage = (double*)(actualStagePtr + 32);
	*actualStage = *actualStage;

	// Execute original
	typedef __int64(__fastcall * funct)(__int64 a1, __int64 a2);
	funct fc = (funct)(moduleBase + 0x68B770);
	__int64 ret = fc(a1, a2);

	//std::cout << "Set stage to " << (int)*actualStage << std::endl;
	//int test = *(int*)(a2 + 48);
	//std::cout << test << std::endl;

	// Redo hook
	typedef void(__stdcall *HookFunct)(void* toHook, void* ourFunct, int len);
	HookFunct Hook = (HookFunct)hookFunct;
	Hook((void*)(moduleBase + 0x68B770), CustomStageSelect::ChangeSelection, 17);

	return ret;



	/*__int64 stageChosen; // rax
	__int64 result; // rax
	__int64 v5; // rcx
	__int64 v6; // xmm0_8
	__int64 v7; // rcx
	int actualStage; // edx
	__int64 v9; // rcx

	__m128i si128; // [rsp+40h] [rbp-30h]
	//__int64 si128A;
	//__int64 si128B;

	__int64 v11; // [rsp+50h] [rbp-20h]
	int v12; // [rsp+58h] [rbp-18h]
	__int64 v13; // [rsp+60h] [rbp-10h]

	stageChosen = *(__int64*)(a2 + 48);
	if (stageChosen)
	{
		result = stageChosen - 1;
		if (!result)
		{
			*(int*)(a1 + 28) = 1;
			v7 = *(__int64*)(a1 + 16);
			if (!v7)
				return result;
			unnamed::DoFlashFunctionJump_0(
				v7,
				"data/ui/flash/FLASH_PLAT/stagesel/stagesel.swf",
				"_root.all_nut.all_stagesel",
				"Decide");
			v5 = *(__int64*)(a1 + 16);
			si128 = _mm_load_si128((const __m128i*)(moduleBase + 0x140EED780 - 0x140000C00));
			//_mm_load_si128
			//memcpy(&si128A, (void*)(moduleBase + 0x140EED780 - 0x140000C00), 8);
			//si128A = -1;
			//si128B = -1;
			v6 = 0x402E000000000000i64;

			// goto label 8
			v11 = 0i64;
			v13 = v6;
			v12 = 5;
			unnamed::DoFlashFunction(
				v5,
				"data/ui/flash/FLASH_PLAT/stagesel/stagesel.swf",
				"_root.all_nut.all_stagesel",
				"StartOut",
				0i64);
			return 0i64;
		}
		if (!--result)
		{
			*(int*)(a1 + 28) = 2;
			v5 = *(__int64*)(a1 + 16);
			if (v5)
			{
				si128 = _mm_load_si128((const __m128i*)(moduleBase + 0x140EED780 - 0x140000C00));
				//si128A = -1;
				//si128B = -1;
				v6 = 0i64;
			//LABEL_8:
				v11 = 0i64;
				v13 = v6;
				v12 = 5;
				unnamed::DoFlashFunction(
					v5,
					"data/ui/flash/FLASH_PLAT/stagesel/stagesel.swf",
					"_root.all_nut.all_stagesel",
					"StartOut",
					0i64);
				return 0i64;
			}
		}
	}
	else
	{
		result = *(__int64*)(a2 + 32);
		actualStage = (int)*(double*)(result + 32);
		*(int*)(a1 + 24) = actualStage;
		v9 = *(__int64*)(a1 + 16);
		if (v9)
			return unnamed::SetStageInfo(v9, actualStage);
	}
	return result;*/
}

void CustomStageSelect::UpdateGUI()
{
	if (!css) return;

	GraphicSettings* g = GraphicSettings::GetResolutionPointer();

	int resx = g->resx;
	int resy = g->resy;

	ImGui::SetNextWindowSize(ImVec2(resx, resy));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("Select a Stage");
	ImGui::TextWrapped("Select a stage from the list.");

	int stageCount = css->stageList.size();

	if (ImGui::ListBoxHeader("Stage List", ImVec2(resx * 1, resy * 0.9)))
	{
		for (int x = 0; x < stageCount; x++)
		{
			StageInfoFramework* stg = css->stageList[x];
			std::string name = stg->stageId + " : " + stg->stageMsg;

			if (ImGui::Selectable(name.c_str(), x == css->currentSelection))
			{
				css->currentSelection = x;
			}
		}
		ImGui::ListBoxFooter();
	}

	if (GetAsyncKeyState('W') & 0x01)
	{
		css->currentSelection--;
		if (css->currentSelection < 0) css->currentSelection = 0;
	}

	if (GetAsyncKeyState('S') & 0x01)
	{
		css->currentSelection++;
		if (css->currentSelection >= stageCount) css->currentSelection = 0;
	}

	if (GetAsyncKeyState('Q') & 0x01)
	{
		css->Close();

		//__int64 * ab = (__int64*)(moduleBase + 0x1416BDA18 - 0x140000C00);
		//GameUtilities::ccSceneManager_Pop(*ab);
	}

	ImGui::End();
}