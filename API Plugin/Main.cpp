#include "Main.h"
#include <stdio.h>
#include <vector>
#include <iostream>

#include <winsock2.h>

#include "DebugMouseSupport.h"
#include "Utilities.h"
#include "PatternScan.h"
#include "CoopMod2.h"
#include "Commands.h"
#include "NoPause.h"

#include "ImGUI/imgui.h"
#include "DirectX.h"

#include "ccSceneGameModeSelect.h"
#include "EditorGUI.h"
#include "CustomStageSelect.h"
#include "ccStageInfoData.h"

#include "ccSceneZealot.h"
#include "ScenePatcher.h"
#include "ccSceneManager.h"
#include "ccSceneBoss12_Phase01.h"
#include "ccUiFlash.h"

using namespace std;
using namespace Editor;

__int64 moduleBase = 0;
__int64 moduleLength = 0;
bool isEditorOpen = false;
__int64 g_editorGUI = 0;
__int64 hookFunct = 0;
__int64 hwndGlobal = 0;

vector<__int64> Main::API_FunctionList;
bool Main::isDebug = false;

EditorBase Main::editor = EditorBase();
__int64 g_editorPtr = 0;

void __stdcall InitializePlugin(__int64 a, std::vector<__int64> b)
{
	// Initial config of plugin
	moduleBase = a;
	g_editorPtr = (__int64)(&(Main::editor));
	Main::API_FunctionList = b;

	// Init pattern scan
	PatternScan::InitializePatternScanUtility();

	// Check if debug
	Main::isDebug = Utilities::IsDebugVersion();
	if (Main::isDebug) cout << "Utilities :: Debug version detected" << endl;

	// Add custom scene
	ScenePatcher::AddCustomScene("ccSceneZealot", 0xFFFF, ccSceneZealot::Create);

	// No pause mod
	NoPause::Init();
}

void __stdcall InitializeCommands(__int64 a, __int64 addCommandFunctionAddress)
{
	typedef void(__stdcall *AddCmd)(std::string command, __int64 function, int paramcount);
	AddCmd AddCommand = (AddCmd)addCommandFunctionAddress;

	//AddCommand("Spawn", (__int64)EditorCommands::cmdCreateSelection, 0);
	AddCommand("Load", (__int64)Commands::cmdLoadHelperTest, 0);
	AddCommand("Framework", (__int64)Commands::cmdGetFrameworkPointers, 0);
	AddCommand("Msg", (__int64)Commands::cmdOpenMsg, 0);
}

ccSceneZealot * sz;
void __stdcall InitializeHooks(__int64 a, __int64 hookFunctionAddress)
{
	HookFunct Hook = (HookFunct)hookFunctionAddress;
	hookFunct = hookFunctionAddress;

	//ccStageInfoData::DoCreateHook();
	//Hook((void*)(moduleBase + 0x6f2658), sub_1406F3258, 18);

	char bootToMenu[4] = { 0x63, 0x00, 0x0, 0x0 };
	Utilities::PasteBytes(moduleBase + 0x862D62, (void*)&bootToMenu[0], 4);

	char titleToZealot[4] = { 0xFF, 0xFF, 0x0, 0x0 };
	//Utilities::PasteBytes(moduleBase + 0x71BEF6, (void*)&titleToZealot[0], 4);

	Hook((void*)(moduleBase + 0x6E43AC), ScenePatcher::InitializeScenes, 15);
	ccSceneBoss12_Phase01::ReplaceVirtuals();

	//sz = new ccSceneZealot();
	//std::cout << "sz: " << std::hex << std::uppercase << sz << std::endl;
	//FrameworkHelpers::ReplaceVirtualFunction(0x1414F9668, ccSceneZealot::Create);
	//FrameworkHelpers::ReplaceVirtualFunction(0x1414F9428, ccSceneZealot::Create);
}

void __stdcall InitializeLuaCommands(__int64 a, __int64 addCommandFunction)
{
	typedef void(__stdcall *LuaAddFc)(std::string command, __int64 function);
	LuaAddFc LuaAddFunct = (LuaAddFc)addCommandFunction;
	// LuaAddFunct("LuaTest", (__int64)LuaTest);
}

void __stdcall Unload()
{
	std::cout << "Realtime Editor : Removing hooks..." << std::endl;
	FrameworkHelpers::EnableCameraMovement();
}

bool didChange = false;
void __stdcall GameLoop(__int64 a)
{
	// No pause update
	NoPause::Update();

	if (GetAsyncKeyState(VK_F9))
	{
		if (didChange == false)
		{
			didChange = true;
			std::cout << "Doing garbage" << std::endl;

			struct test
			{
				__int64 result; // rax
				__m128i si128; // [rsp+40h] [rbp-38h] BYREF
				__int64 v4; // [rsp+50h] [rbp-28h]
				unsigned int v5; // [rsp+58h] [rbp-20h]
				const char *versionText; // [rsp+60h] [rbp-18h]
			};

			test str;
			str.v4 = 0;
			str.v5 = 6;
			str.versionText = "Storm Framework by Zealot Tomato";

			ccGameProperty* prop = ccGameProperty::GetPropertyHelper(0x1416BDA20, "titleUi");
			__int64 v3 = prop->m_valueB;
			__int64 v3funct = Utilities::GetVirtualFunction(v3, 1);
			__int64 propfunct = Utilities::GetVirtualFunction((__int64)(prop)+8, 2);
			__int64 v4 = (moduleBase + 0x14160E8F0 - 0x140000C00) == Utilities::DoSimpleFunction(v3funct, v3) ? propfunct : 0;

			std::cout << "Prop: " << std::hex << prop << std::endl;
			std::cout << "v3: " << std::hex << v3 << std::endl;
			std::cout << "v3funct: " << std::hex << v3funct << std::endl;
			std::cout << "propfunct: " << std::hex << propfunct << std::endl;

			/*__int64 xd = *(__int64*)((moduleBase + 0x1416BDA20 - 0x140000C00) + 8);
			__int64 prop = ccGameProperty::GetProperty(xd, "titleUi");
			std::cout << "Prop: " << std::hex << prop << std::endl;
			__int64 v3 = *(__int64*)(prop + 8);
			std::cout << "v3: " << std::hex << v3 << std::endl;

			__int64 v3funct = *(__int64*)((*(__int64*)(v3)) + 8);
			__int64 propfunct = *(__int64*)((*(__int64*)(prop + 8)) + 16);
			__int64 v4 = (moduleBase + 0x14160E8F0 - 0x140000C00) == reinterpret_cast<__int64(__fastcall*)(__int64)>(v3funct)(v3) ? propfunct : 0;*/

			if (v4)
			{
				std::cout << "v4 yes: " << std::hex << v4 << std::endl;
				ccUiFlash::InvokeFunction((ccUiFlash*)v4, "data/ui/flash/FLASH_PLAT/gametitle/gametitle.swf", "_root.all_nut", "SetVersionText", 0, (__int64)(&(str.si128)), 1);
			}
			else
			{
				std::cout << "v4 no: " << std::hex << v4 << std::endl;
			}

			__int64 result = str.v5 >> 6;
			if ((str.v5 & 0x40) != 0)
			{
				__int64 funct = Utilities::GetVirtualFunction(v4, 2);
				reinterpret_cast<__int64(__fastcall*)(__int64, __int64, __int64)>(funct)(v4, (__int64)(&(str.si128)), (__int64)(str.versionText));
			}
		}
	}
	else
	{
		didChange = false;
	}

	if (GetAsyncKeyState(VK_F1))
	{
		for (int x = 0; x < 0x64; x++)
		{
			std::cout << "Scene " << std::hex << std::uppercase << x << " = Rank " << ccSceneManager::SearchSceneRank(ccSceneManager::GetInstance(), x) << std::endl;
		}
	}

	if (GetAsyncKeyState(VK_F2))
	{
		int sceneKey = ccSceneManager::GetCurrentSceneKey(ccSceneManager::GetInstance());
		std::cout << "Scene Key: " << std::hex << sceneKey << std::endl;
		__int64 sceneList = ScenePatcher::sceneList;
		int sceneIndexInList = -1;

		std::cout << "Scene Name: " << ccSceneManager::GetSceneNameByKey(sceneList, ScenePatcher::totalSceneCount, sceneKey) << std::endl;
	}

	if (GetAsyncKeyState(VK_F6) & 0x01)
	{
		for (int x = 0; x < 0x64; x++)
		{
			std::cout << "Scene " << std::hex << std::uppercase << x << " = Rank " << ccSceneManager::SearchSceneRank(ccSceneManager::GetInstance(), x) << std::endl;
		}

		ccSceneManager::Push(ccSceneManager::GetInstance(), 0xFFFF);
	}

	return;
	if (GetAsyncKeyState('U') & 0x01 && false)
	{
		ccSceneManager::Pop(ccSceneManager::GetInstance());
	}

	ccPlayerMain * pl = BattleUtils::ccGame_GetPlayerLeader(0);
	if (pl)
	{
		if (GetAsyncKeyState('P'))
		{
			int newState = 2;
			int * state = (int*)(((__int64)(pl)) + 0xCC0);
			if(*state != newState) ccPlayer::SetActionImmediate((ccPlayer*)pl, newState);
		}
		//int * state = (int*)(((__int64)(pl)) + 0xCC0);
		//const char ** anm = (const char**)((__int64)(moduleBase + 0x1536DD0 + 0x400 + *state * 0x20));
		//std::cout << "anm = " << *anm << std::endl;
		// 1536DD0+nsuns4.exe+c00+0x400
		//std::cout << "anm = " << std::hex << std::uppercase << *state << " : " << ccPlayerAnmIdManager::GetName(*state) << std::endl;
	}

	__int64 adv = unnamed::GetAdvManager();
	if (adv)
	{
		ccCmnScreenManager* cmnScreenManager = Game::GetCmnScreenManager();
		if (cmnScreenManager)
		{
			ccCmnCameraDirector* camDirector = ccCmnScreenManager::GetCameraDirector(cmnScreenManager, 0);

			if (camDirector)
			{
				ccCmnCamera* cam = ccCmnCameraDirector::GetActiveCamera(camDirector);

				if (cam)
				{
					//ccCmnCameraDirector::ClearAllCameraOperator(camDirector);
					//Vector3 newPos = Vector3(100, 0, 0);
					//ccCmnCamera::SetCameraPosNew(cam, (__int64)&newPos);
				}
			}
		}
	}

	if(false)
	{
		ccCmnCameraDirector* camDir = ccCmnScreenManager::GetCameraDirector(Game::GetCmnScreenManager(), 0);
		if (camDir)
		{
			ccCmnCamera* camera_ = ccCmnCameraDirector::GetActiveCamera(camDir);

			if (camera_)
			{
				ccCmnCameraDirector * camDirectorStruct = (ccCmnCameraDirector*)(camDir);
				ccCmnCamera::Init(camera_);

				std::cout << "Cam " << std::hex << camDirectorStruct->actualCamera << " : " << std::hex << camera_ << std::endl;

				float * xp = (float*)(camera_ + 0x3C);
				float * yp = (float*)(camera_ + 0x4C);
				float * zp = (float*)(camera_ + 0x5C);

				if (xp && yp && zp)
				{
					//*xp = test.x;
					//*yp = test.y;
					//*zp = test.z;

					std::cout << "x: " << *xp << ", " << *yp << std::endl;
				}
			}

			//ccCmnCameraDirector::ClearAllCameraOperator(camDir);
		}
	}

	if (GetAsyncKeyState(VK_F1) & 0x01)
	{
		ccStageObjectManager* a = nummNudInfo::GetHeader();
		std::cout << "nummNudInfo::GetHeader(pGPUDevice) = " << std::hex << std::uppercase << a << std::endl;
	}

	if (GetAsyncKeyState(VK_F5) & 0x01)
	{
		ccCmnCameraDirector* camDirector = ccCmnScreenManager::GetCameraDirector(Game::GetCmnScreenManager(), 0);
		std::cout << "CameraDirector : " << std::hex << std::uppercase << camDirector;
		std::cout << std::endl;
	}

	if (GetAsyncKeyState(VK_F6) & 0x01)
	{
		ccCmnCameraDirector* camDirector = ccCmnScreenManager::GetCameraDirector(Game::GetCmnScreenManager(), 0);
		int * camCount = (int*)((__int64)camDirector + 12);

		for (int x = 1; x <= *camCount; x++)
		{
			ccCmnCamera* camera = ccCmnCameraDirector::GetCamera(camDirector, x);
			std::cout << "CAM_" << x << " : " << std::hex << std::uppercase << camera << ", x: " << camera->m_position.x << ", y: " << camera->m_position.y << ", z: " << camera->m_position.z << ", fov: " << camera->m_fov << std::endl;
		}
		std::cout << std::endl;
	}

	if (GetAsyncKeyState(VK_F7) & 0x01)
	{
		ccCmnCameraDirector* camDirector = ccCmnScreenManager::GetCameraDirector(Game::GetCmnScreenManager(), 0);
		int * camCount = (int*)(camDirector + 12);

		std::cout << "Set camera to " << 0xB << std::endl;
		ccCmnCameraDirector::ChangeCamera(camDirector, 1, 0xB);
	}
}

void __stdcall PreRender()
{

}

void __stdcall PostRender()
{
	
}

bool Main::initGUI = false;
void __stdcall OnGUI(bool frameworkShow, __int64 hwnd, __int64 imguiContext)
{
	if (Main::initGUI == false)
	{
		std::cout << "Framework Editor :: Initialized GUI" << std::endl;
		Main::initGUI = true;
		ImGui::SetCurrentContext((ImGuiContext*)imguiContext);

		// Start editor GUI
		Main::editor.Start();
	}

	Main::editor.Update();
	hwndGlobal = hwnd;
	EditorGUI::LoopGUI(frameworkShow, hwnd);
}

bool __stdcall ParseApiFiles(__int64 a, std::string filePath, std::vector<char> fileBytes)
{
	return false;
}
