#pragma once
#include "Common.h"

#include <iostream>
#include "ccEntryModelTest.h"

class Commands
{
public:
	static void cmdCreate1Cmn()
	{
		const char* path = "data/spc/1cmnbod1.xfbin";
		const char* bod = "1cmnbod1";

		cmdCreateObject(path, bod);
	}

	static void cmdCreateObjectInput()
	{
		char* path = new char(255);
		char* bod = new char(255);

		std::cout << "Xfbin Path: ";
		std::cin >> path;
		std::cout << std::endl;

		std::cout << "Bod: ";
		std::cin >> bod;
		std::cout << std::endl;

		cmdCreateObject(path, bod);
	}

	static void cmdCreateObject(const char * path, const char* bod)
	{
		/*std::cout << "Attempting to create " << bod << " in " << path << std::endl;

		__int64 v53 = nuccXfbinDocManager::Search("data/rpg/rhgrbod1.xfbin");
		std::cout << "Finished searching" << std::endl;

		__int64 v55 = Game::operator_new(0x2E30, bod, 0x2AA); // operator_new in memory
		std::cout << "Allocated memory" << std::endl;

		if (v55)
		{
			__int64 v56 = ccGameObjSubDraw::GameObjSubDraw(v55);
			std::cout << "Initialized gameObject" << std::endl;

			ccGameObjSubDraw::Create(v56, v53, (__int64)bod);
			std::cout << "Created successfully" << std::endl;
		}
		else
		{
			std::cout << "Error creating gameObject" << std::endl;
		}*/
	}

	static void cmdCreatePlayer()
	{
		/*__int64 pl = ccPlayerMain::New();
		
		if (pl)
		{
			std::cout << "Created player at 0x" << std::hex << std::uppercase << pl << std::endl;

			__int64 v2 = ccPlayerMain::PlayerMain(pl);
			std::cout << "ccPlayerMain::ccPlayerMain(pl) = " << std::hex << std::uppercase << v2 << std::endl;

			__int64 v3 = ccPlayerMain::ccGameObject__FunctionInit(v2);
			std::cout << "ccPlayerMain::ccGameObject::FunctionInit(v2) = " << std::hex << std::uppercase << v3 << std::endl;
		}
		else
		{
			std::cout << "Error creating player" << std::endl;
		}*/
	}

	static void cmdCreateCamManager()
	{


		/*std::cout << "Attempting to create camera manager" << std::endl;
		ccCameraManager::Create(ccCameraManager::GetInstance());
		std::cout << "Created camera manager at " << std::hex << std::uppercase << ccCameraManager::GetInstance() << std::endl;*/
	}

	static void cmdLoadHelperTest()
	{
		std::string path = "";
		std::cin >> path;

		nuccFileLoadList::LoadHelper(0, path.c_str());
		std::cout << "Loaded " << path << std::endl;
	}

	static void cmdCreateGameObject()
	{
		std::string objectToCreate = "null";

		std::cin >> objectToCreate;

		__int64 obj = 0;

		if (objectToCreate == "ccChakraBall")
		{
			obj = Game::operator_new(0xB0, "", 0x4F);
			obj = ccChakraBall::CcChakraBall(obj);
			ccChakraBall::Initialize(obj);

			std::cout << "Object: " << std::hex << std::uppercase << obj << std::endl;
		}
		else if (objectToCreate == "test")
		{
			__int64 advInstance = Game::ObjectList_GetInstanceAdventure();

			if (advInstance)
			{
				__int64 a = unnamed::sub_1404DA8A8(Game::ObjectList_GetInstanceAdventure(), "data/spc/1cmnbod1", "1cmnbod1");
			}
		}
		else
		{
			std::cout << "Invalid Type" << std::endl;
		}
	}

	static void cmdCreateFilter()
	{
		__int64 a = unnamed::ccCreateFilter("data/spc/1cmnbod1.xfbin", "1cmnbody");
		std::cout << std::hex << std::uppercase << a << std::endl;
	}

	static void cmdGetFrameworkPointers()
	{
		__int64 framework = (__int64)Game::GetFramework();
		std::cout << std::hex << std::uppercase << (__int64)(framework) << std::endl;
	}

	static void cmdOpenMsg()
	{
		__int64 result;
		__int64 v3; // rsi
		__int64 v4; // rbx
		__int64 v5; // rsi
		__int64 v6; // rbx
		__int64 v7; // rax
		__int64 v8; // rax
		__int64 v9; // rdx

		int v10;

		int v11;
		int v12;
		const char *v13;

		int spacing = 0;
		int v14;
		int v15;
		const char *v16;

		const char * meshPath = "data/spc/1cmnbod1.xfbin";
		const char * meshBod = "1cmnbod1";

		char v46[0x200];

		result = nuccXfbinDocManager::GetXfbinLoadState(meshPath);
		if (result == 2)
		{
			v3 = nuccXfbinDocManager::Search(meshPath);
			std::cout << "v3 = " << std::hex << std::uppercase << v3 << std::endl;

			if (v3)
			{
				v13 = meshBod;
				v11 = Nucc::CalcHashFromStr(meshBod);
				v12 = 1;

				// [TOFIX]
				//v5 = nuccXfbinDocument::SearchChunk(v3, (__int64)meshPath, (__int64)(&v11));
				v5 = 0;
				if (v5)
				{
					std::cout << "Chunk : " << std::hex << std::uppercase << v5 << std::endl;

					nuccChunkClump::GetWorldMatrix(v5, 0, (__int64)&v46[0]);
					
					for (int x = 0; x < 0x200; x = x + 2)
					{
						std::cout << std::hex << (int)(v46[x]) << std::hex << (int)(v46[x + 1]) << " ";
					}

					std::cout << std::endl;
				}
			}
		}
	}

	static void cmdOpenEditor()
	{
		/*if (isEditorOpen == false)
		{
			((EditorBase*)g_editorPtr)->OpenEditorGUI();
		}
		else
		{
			std::cout << "Editor is already open" << std::endl;
		}*/
	}
};