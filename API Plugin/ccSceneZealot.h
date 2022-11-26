#pragma once
#include "FrameworkScene.h"

#include <xmmintrin.h>
#include <emmintrin.h>
#include "RestoreDebugFont.h"
#include "ccUiLayoutParts.h"
#include "FrameworkFont.h"
#include "ccStageObjectManager.h"
#include "ccGameRootStateMachine.h"
#include "ccStageInfoManager.h"
#include "MouseLook.h"
#include "GameObjectCreator.h"
#include "ccUiFlash.h"

class ccSceneZealot : FrameworkScene
{
public:
	static const char* ID;
	static ccSceneZealot * Allocate(const char* a1)
	{
		ccSceneZealot * thisScene = new ccSceneZealot();
		ccScene::SetSceneName((ccScene*)thisScene, a1);
		return thisScene;
	}
	
	struct ccSceneZealotParams
	{
		float defaultFontSize;
		float defaultSpacing;

		ccFileLoadListForUi * m_fileLoadListUi;
		FrameworkFont m_txt_title;
		FrameworkFont m_txt_campos;

		int m_actualOption = 0;
		FrameworkFont m_txt_marker;
		std::vector<FrameworkFont*> m_txt_options;
		float m_markerDefaultY = 0;
		bool fade = false;

		std::string optionList[3] =
		{
			"Model Viewer",
			"Texture Viewer",
			"Boot to ccSceneTitle"
		};

		ccStageObjectManager * m_stageObjectManager;
		Editor::MouseLook * m_mouseLook;
		Vector3 * m_camPos = new Vector3();
	};

	__int64 __fastcall Initialize(__int64 mem) override
	{
		delete01((__int64)this);

		//std::cout << "Initialize" << std::endl;

		float resx = Game::GetResX();
		float resy = Game::GetResY();

		ccCmnFade::StartFadeOut(ccCmnFade::GetInstance(), 0);

		// Background
		//mp->m_uiTest2 = ccUiSimpleDraw::ccCreateSimpleDrawUi("");
		//ccUiTaskBase::SetEnableTask(mp->m_uiTest2, 0);
		//ccUiSimpleDraw::CreateUiObj(mp->m_uiTest2, "data/ui/max/boot_logo/boot_logo.xfbin", mp->imageCollection[1].c_str(), 2);
		//ccUiTaskBase::SetEnableTask(mp->m_uiTest2, 1);
		//Nucc::Vector2::Div(mp->m_uiTest2, *(INT16*)(Game::gameInfo() + 0x470), *(INT16*)(Game::gameInfo() + 0x472));

		float fontSize = (resx * 0.01) * 1.15;
		mp->defaultFontSize = fontSize;
		mp->defaultSpacing = fontSize * 1.75;

		mp->m_txt_title.size = fontSize;
		mp->m_txt_title.SetText("STORM Framework 1.8-nightly-382022a by Zealot Tormunds", resx * 0.02, resy * 0.025);

		/*mp->m_txt_marker.size = fontSize;
		mp->m_txt_marker.SetText(">", resx * 0.08, resy * 0.08);
		mp->m_markerDefaultY = mp->m_txt_marker.position->y;
		
		float actual_y = resy * 0.1;
		for (int x = 0; x < 3; x++)
		{
			FrameworkFont * newText = new FrameworkFont();
			newText->size = fontSize;
			newText->SetText(mp->optionList[x], resx * 0.095, actual_y);

			mp->m_txt_options.push_back(newText);
			actual_y += mp->defaultSpacing;
		}*/

		return pop00((__int64)this);
	}

	void __fastcall Execute(__int64 mem) override;

	__int64 __fastcall Finalize(__int64 mem) override
	{
		std::cout << "Finalize" << std::endl;
		return mem;
	}

	__int64 __fastcall Activated(__int64 mem) override
	{
		std::cout << "Activated" << std::endl;
		return mem;
	}

	__int64 __fastcall Deactivated(__int64 mem) override
	{
		if (mp->m_stageObjectManager)
		{
			ccTaskBase::DeleteAllTask((ccTaskBase*)(mp->m_stageObjectManager));
			ccStageObjectList* objList = ccStageObjectManager::GetObjectList(mp->m_stageObjectManager, 0);
			ccStageObjectList::Clear(objList);
			mp->m_stageObjectManager = nullptr;
			std::cout << "ccSceneZealot :: Destroying objects" << std::endl;
		}

		mp->m_txt_campos.Clear();
		mp->m_txt_marker.Clear();
		mp->m_txt_title.Clear();
		for (int x = 0; x < mp->m_txt_options.size(); x++)
		{
			FrameworkFont * f = mp->m_txt_options[x];
			f->Clear();
		}

		std::cout << "Deactivated" << std::endl;
		return mem;
	}

	__int64 __fastcall Idling(__int64 mem) override
	{
		std::cout << "Idling" << std::endl;
		return mem;
	}

	char padding[288];
	int m_hasKeyHelper;
	int m_unk00;
	static ccSceneZealotParams * mp;

	static ccSceneZealot * Create(const char* sceneName)
	{
		std::cout << sceneName << std::endl;
		
		ccSceneZealot dummy;
		__int64 vtable = *(__int64*)(&dummy);

		__int64 scenePtr = Game::operator_new(0x138 + 0x20, "", 0x2E9); // allocate scene
		//std::cout << "sceneptr: " << std::hex << std::uppercase << scenePtr << std::endl;

		ccSceneZealot * zealotScene = 0; // reinterpret as zealot
		zealotScene = (ccSceneZealot*)(ccScene::Constructor((ccScene*)scenePtr)); // default constructor for scene

		*((__int64*)(zealotScene)) = vtable;

		*(__int64*)(((__int64)(zealotScene)) + 296) = 0;
		*(__int64*)(((__int64)(zealotScene)) + 304) = 0;

		// Create params
		zealotScene->mp = new ccSceneZealotParams();
		zealotScene->mp->m_fileLoadListUi = ccFileLoadListForUi::Instantiate();
		ccFileLoadListForUi::LoadTh(zealotScene->mp->m_fileLoadListUi, "data/ui/max/boot_logo/boot_logo.xfbin");
		ccFileLoadListForUi::LoadTh(zealotScene->mp->m_fileLoadListUi, "disc:data/system/xftool.fnt.xfbin");
		ccFileLoadListForUi::LoadTh(zealotScene->mp->m_fileLoadListUi, "data/ui/cmn/xcmn00.xfbin");
		ccFileLoadListForUi::LoadTh(zealotScene->mp->m_fileLoadListUi, "data/spc/2nrtbod1.xfbin");
		LoadHelper("data/spc/1cmnbod1.xfbin");
		LoadHelper("data/stage/si42a.xfbin");
		LoadHelper("data/spc/2nrtbod1.xfbin");
		FrameworkFont::LoadDefaultFont((__int64)(zealotScene->mp->m_fileLoadListUi));

		Sleep(1000);

		// search
		/*nuccChunkList* data = (nuccChunkList*)malloc(8 * 4);
		__int64 doc = nuccXfbinDocManager::Search("data/spc/1cmnbod1.xfbin");
		if (doc)
		{
			nuccChunkList::NuccChunkList((__int64)data);
			nuccXfbinDocument::SearchChunkList((nuccXfbinDocument*)doc, (nuccXfbinDocument::ChunkSearchType*)(moduleBase + 0x141560B08 - 0x140000C00), (__int64)data);
			int actualChunk = 0;
			if (nuccChunkList::GetSize(data))
			{
				while (actualChunk < nuccChunkList::GetSize(data))
				{
					nuccChunk* chunkData = nuccChunkList::GetChunk(data, actualChunk);
					const char* chunkName = nuccChunk::GetName(chunkData);
					std::cout << "Chunk: " << chunkName << std::endl;

					actualChunk++;
				}
			}
		}*/

		//std::cout << "set scene: " << sceneName << std::endl;
		ccScene::SetSceneName((ccScene*)zealotScene, sceneName);

		return zealotScene;
	}

	static __int64 CreateWindow4()
	{
		ccUiFont* b0 = (ccUiFont*)(Game::operator_new(0x1E8, "", 0x8C));
		std::cout << "text: " << std::hex << std::uppercase << b0 << std::endl;

		__int64 result = LoadHelper("disc:data/system/xftool.fnt.xfbin");
		std::cout << "LoadHelper result: " << std::hex << result << std::endl;

		/*ccUiFont::CcUiFont(b0, 1);
		ccUiFont::Initialize(b0, "data/ui/xftool.fnt.xfbin", "xftool");
		ccUiFont::SetScale(b0, 30, 30);
		ccUiFont::SetPivot(b0, 1);
		ccUiFont::SetRubyEnable(b0, 1);
		ccUiFont::SetText(b0, "+Holaaaaaa");*/
		//__int64 v8 = (__int64)b0;

		__int64 v8 = Game::operator_new(0x88, "", 0x277);
		std::cout << "Message: " << std::hex << v8 << std::endl;
		if (v8)
		{
			v8 = ccUiWindow4::Create(v8);
			ccUiWindow1::AllocateMessageWindow(v8, "+Message 1");
			ccUiWindow1::SetTitleText(v8, "+<color white>STORM Framework</color>", 1);
			ccUiWindow1::SetMenuText(v8, "+<color white>Mods that are installed:\n<color yellow>Test</color>\n<color red>Test2</color></color>", 1);
			ccUiWindow1::Open(v8);
			ccUiWindow1::SetWindowSize(v8, 780, 400);
		}

		return v8;
	}

	static __int64 LoadHelper(const char* path)
	{
		__int64 result = 0;

		result = nuccFileLoadList::LoadHelper(0, path);

		// Check if loaded
		int timeout = 600;
		int isFileLoaded = -1;
		bool found = false;

		while (timeout > 0 && !found)
		{
			found = (nuccXfbinDocManager::GetXfbinLoadState(path) == 2);
			timeout--;
			Sleep(1);
		}

		if (found)
		{
			std::cout << "Result " << path << " = " << std::hex << std::uppercase << result << std::endl;
		}
		else
		{
			std::cout << "Error loading file " << path << std::endl;
			result = 0;
		}

		return result;
	}

	static void SetTextColor(ccUiFlash * a1, int a2)
	{
		__int64 result = 0; // rax

		__m128i a6; // [rsp+40h] [rbp-38h] BYREF
		__int64 v4 = 0; // [rsp+50h] [rbp-28h]
		unsigned int v5 = 0; // [rsp+58h] [rbp-20h]
		unsigned int v6[2] = { 0, 0 }; // [rsp+60h] [rbp-18h]

		//std::cout << std::hex << a6 << std::endl;

		a6 = _mm_load_si128((const __m128i*)(moduleBase + 0x140EED780 - 0x140000C00));

		v4 = 0;
		v5 = 4;
		v6[0] = 16770048;
		v6[1] = 16770048;
		ccUiFlash::InvokeFunction(a1, "data/ui/flash/FLASH_PLAT/xcmn_win1/xcmn_win1.swf", "_root.all_nut.all_win1", "SetMenuTextColor", 0i64, (__int64)&testVar[0], 1);
		//ccUiFlash::SetVariable(a1, "data/ui/flash/FLASH_PLAT/xcmn_win1/xcmn_win1.swf", "_root.all_nut.all_win1.mc_win", "visible", (__int64)a6);

		if ((v5 & 0x40) != 0)
		{
			__int64 functAdd = v4;
			functAdd = *(__int64*)functAdd;
			functAdd += 16;
			functAdd = *(__int64*)functAdd;

			reinterpret_cast<__int64(__fastcall*)(__int64 a1, __int64 a2, __int64 a3)>(functAdd)(v4, (__int64)&a6, (__int64)v6);
			//std::cout << "Did stuff at " << std::hex << v4 << " , " << std::hex << functAdd << std::endl;
		}
		else
		{
			//std::cout << "XD " << std::hex << a6[0] << " , " << std::hex << a6[1] << std::endl;
		}

		//ccUiFlash::InvokeFunction(a1, "data/ui/flash/FLASH_PLAT/xcmn_win1/xcmn_win1.swf", "_root.all_nut.all_win1", "SetTitleTextColor", 0i64, (__int64)a6, 1);
	}
};