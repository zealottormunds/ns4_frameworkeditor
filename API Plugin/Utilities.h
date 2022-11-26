#pragma once
#include <iostream>
#include <vector>
#include <sstream>

#include "Common.h"
#include "StormStructures.h"
#include "PatternScan.h"
#include "ccStageObjectManager.h"
#include "ccPlayer.h"
#include "ccPlayerMain.h"
#include "ccGameDrawEnv.h"
#include "ccCmnScreenManager.h"

class Utilities
{
public:
	static __int64 GetPointer(__int64 baseAddress, std::vector<int> offsets)
	{
		__int64 * firstPointer = (__int64*)baseAddress;
		__int64 actualPointer = 0;
		__int64 finalPointer = 0;

		if (firstPointer == 0 || *firstPointer == 0) return 0;
		actualPointer = *firstPointer;

		for (int x = 0; x < offsets.size(); x++)
		{
			if (actualPointer == 0) return 0; // If pointer is invalid

			actualPointer = actualPointer + offsets[x];
			if (x < offsets.size() - 1)
			{
				actualPointer = *(__int64*)(actualPointer);
			}
		}

		finalPointer = actualPointer;
		return finalPointer;
	}

	static void Nop(__int64 address, int bytes)
	{
		DWORD dwOld = 0;
		VirtualProtect((void*)(address), bytes, PAGE_EXECUTE_READWRITE, &dwOld);
		memset((void*)address, 0x90, bytes);
		VirtualProtect((void*)(address), bytes, dwOld, &dwOld);
	}

	static DWORD ChangeProtect(__int64 address, int bytes, int pageProtection)
	{
		DWORD dwOld = 0;
		VirtualProtect((void*)(address), bytes, pageProtection, &dwOld);
		return dwOld;
	}

	static void PasteBytes(__int64 address, void * bytes, int byteCount)
	{
		DWORD dwOld = 0;
		VirtualProtect((void*)(address), byteCount, PAGE_EXECUTE_READWRITE, &dwOld);

		memcpy((void*)address, bytes, byteCount);

		VirtualProtect((void*)(address), byteCount, dwOld, &dwOld);
	}

	static bool IsDebugVersion()
	{
		return (PatternScan::Scan("636344656275674D656E75") > 0);
	}

	static __int64 GetVirtualFunction(__int64 vtableObject, int index)
	{
		return *(__int64*)((*(__int64*)(vtableObject)) + (index * 8));
	}

	static __int64 DoSimpleFunction(__int64 fc, __int64 param)
	{
		return reinterpret_cast<__int64(__fastcall*)(__int64)>(fc)(param);
	}

	static std::string HexToString(__int64 h)
	{
		std::stringstream ptrRead;
		ptrRead << std::hex << std::uppercase << h;
		std::string ptrRead_str = ptrRead.str();
		return ptrRead_str;
	}

	/*static Camera * GetCameraDebug()
	{
		__int64 ptr = (moduleBase + 0x1959A88);
		std::vector<int> offsets{ 0x10, 0x10, 0x20, 0x8, 0xB0 };
		Camera * c = (Camera*)GetPointer(ptr, offsets);
		return c;
	}*/
};

class ccCameraOperatorDisp
{
public:
	static __int64 __fastcall CcCameraOperatorDisp(__int64 a)
	{
		typedef __int64(__fastcall * funct)(__int64 a);
		funct fc = (funct)(moduleBase + 0x8543BC);
		return fc(a);
	}
};

class GameUtilities
{
public:

	struct ccFrameworkPointers
	{
		__int64 * ptr0;
		__int64 * ptr1;
		__int64 * ptr2;
		__int64 * ptr3;
		__int64 * ptr4;
		__int64 * ptr5;
		__int64 * ptr6;
		__int64 * ptr7;
		__int64 * ptr8;
		__int64 * SceneManager;
	};

	static int GameObject__Test()
	{
		typedef int(*funct)();
		funct fc = (funct)(moduleBase + 0xAC4220);
		return fc();
	}

	static __int64 __fastcall ccIa_SetScaleStage(float x, float y, float z)
	{
		typedef __int64(__fastcall * funct)(float x, float y, float z);
		funct fc = (funct)(moduleBase + 0x46B3B4);
		return fc(x, y, z);
	}

	static __int64 __fastcall ccTest(__int64 a)
	{
		std::cout << std::hex << a << std::endl;
		return a;
	}

	static __int64 __fastcall ccSceneManager_Execute(__int64 sceneManager)
	{
		typedef __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0xAB4C10);
		return fc(sceneManager);
	}
};

class DebugUtils
{
public:
	static __int64 __fastcall malloc_sub_140A01930(size_t Size, unsigned int a2, __int64 a3, int a4)
	{
		typedef __int64(__fastcall * funct)(size_t Size, unsigned int a2, __int64 a3, int a4);
		funct fc = (funct)(moduleBase + 0xA00D30);
		return fc(Size, a2, a3, a4);
	}

	static __int64 __fastcall operator_new(__int64 a1, char* a2, __int64 a3)
	{
		std::string disableList[] =
		{
			"nuccChunkAnmCtrlCoord.cpp",
			"nuccAnm.cpp",
			"nuccAnmKey.cpp",
			"nuccUseChunkType.h",
		};

		std::string path(a2);
		bool show = false;
		
		for (int x = 0; x < 4; x++)
		{
			if (path.find(disableList[x]) != std::string::npos)
			{
				show = false;
				x = 999;
			}
		}

		if (show)
		{
			std::cout << "0x" << std::uppercase << std::hex << a1 << " > " << a2 << " > 0x" << std::uppercase << std::hex << a3 << " " << std::endl;
		}

		return malloc_sub_140A01930(a1, 0, (__int64)a2, a3);
	}

	static __int64 __fastcall cameraTest(__int64 a1, int a2, unsigned int a3)
	{
		std::cout << "Called camera change" << std::endl;
		std::cout << "Director: " << std::hex << std::uppercase << a1 << std::endl;
		std::cout << "A2: " << std::hex << std::uppercase << a2 << std::endl;
		std::cout << "A3: " << std::hex << std::uppercase << a3 << std::endl;

		return a1;
	}
};

struct __declspec(align(8)) ccFramework
{
	void *ptr0;
	void *ptr1;
	void *ptr2;
	void *ptr3;
	void *ptr4;
	void *ptr5;
	void *ptr6;
	void *ptr7;
	void *ptr8;
	void *SceneManager;
	void *TaskManager;
	void *GameProperty;
	void *ccTrophyManager;
	void *ccPresenceManager;
	void *ccSaveManager;
	void *CollisionManager;
	void *ccNetStartUp;
	void *ccNetOnlineCheck;
	void *ccMessageManager;
	void *ptr19;
	void *XfbinDocManagerForUi;
	void *UiManager;
	void *ptr22;
	void *ccInvitedParam;
	void *ccParentalControl;
	void *ptr25;
	void *ptr26;
	void *ptr27;
	void *ptr28;
	void *ptr29;
	void *ptr30;
	void *ptr31;
	void *ptr32;
	void *ptr33;
	void *ptr34;
};

class Game
{
public:
	static __int64 __fastcall operator_new(__int64 a1, const char* a2, unsigned int a3)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, const char* a2, unsigned int a3);
		funct fc = (funct)(moduleBase + 0xA00BF0);
		return fc(a1, a2, a3);
	}

	static signed __int64 __fastcall delete_operator(__int64 a1)
	{
		typedef signed __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0xA01180);
		return fc(a1);
	}

	static __int64 __fastcall gameInfoPtr()
	{
		__int64 * gameInfo = (__int64*)(moduleBase + 0x1416663C8 - 0x140000C00);
		return (__int64)gameInfo;
	}

	static __int64 __fastcall gameInfo()
	{
		__int64 * gameInfo = (__int64*)(moduleBase + 0x1416663C8 - 0x140000C00);
		return *gameInfo;
	}

	static __int64 ObjectList_GetInstanceGlobal() // For permanent objects
	{
		return *((__int64*)(moduleBase + 0x14161C948 - 0x140000C00));
	}

	static __int64 ObjectList_GetPtrLightsAndFog()
	{
		return (__int64)(moduleBase + 0x14161A340 - 0x140000C00);
	}

	static __int64 ObjectList_GetInstanceLightsAndFog()
	{
		return *((__int64*)(moduleBase + 0x14161A340 - 0x140000C00));
	}

	static __int64 ObjectList_GetInstanceAdventure()
	{
		return *((__int64*)(moduleBase + 0x1415E7220 - 0x140000C00));
	}

	static __int64 ObjectList_GetInstanceGroupBattle()
	{
		__int64 * objectListPtr = (__int64*)(moduleBase + 0x1415DDDD0 - 0x140000C00);

		if (*objectListPtr)
		{
			objectListPtr = (__int64*)((*objectListPtr) + 72);
			return *objectListPtr;
		}
		else
		{
			return 0;
		}
	}

	static __int64 ObjectList_GetInstanceDuel()
	{
		return *((__int64*)(moduleBase + 0x14161C8C8 - 0x140000C00));
	}

	static __int64 ObjectList_StageObjectManager() // For local objects
	{
		// 14161C8B8
		return *((__int64*)(moduleBase + 0x14161C8B8 - 0x140000C00));
	}

	static __int64 ObjectList_GetInstanceUI()
	{
		return *((__int64*)(moduleBase + 0x14161C8D8 - 0x140000C00));
	}

	static ccCmnScreenManager* GetCmnScreenManager()
	{
		// 14161C780
		return (ccCmnScreenManager*)*((__int64*)(moduleBase + 0x14161C780 - 0x140000C00));
	}

	static __int64 ConvertOffset(__int64 address)
	{
		if (address < 0xEAC000) // text
		{
			return moduleBase + address;
		}
		else if (address < 0xEACF88) // idata
		{
			return moduleBase + address + 0x200;
		}
		else if (address < 0x13B6000) // rdata
		{
			return moduleBase + address + 0x200;
		}
		else if (address < 0x15BD400) // data
		{
			std::cout << "Address is in data" << std::endl;
			return moduleBase + address + 0x400;
		}
		else if (address < 0x1690400) // pdata
		{
			return moduleBase + address + 0x1000;
		}
		else // tls
		{
			return moduleBase + address + 0x1400;
		}
	}

	static ccFramework* GetFramework()
	{
		return (ccFramework*)*((__int64*)(moduleBase + 0x1416BD9D0 - 0x140000C00));
		//return (ccFramework*)((__int64*)(gameInfo() + 0xF40));
	}

	static float GetResX()
	{
		return *(INT16*)(Game::gameInfo() + 0x470);
	}

	static float GetResY()
	{
		return *(INT16*)(Game::gameInfo() + 0x472);
	}

	static short GetFPS()
	{
		return *(short*)(gameInfo() + 0x942);
	}
};

class BattleUtils
{
public:
	static ccPlayerMain * __fastcall ccGame_GetPlayerLeader(unsigned int PLAYER_SIDE)
	{
		typedef ccPlayerMain *(__fastcall * funct)(unsigned int PLAYER_SIDE);
		funct fc = (funct)(moduleBase + 0x85A948);
		return fc(PLAYER_SIDE);
	}

	static __int64 __fastcall GetPlayerContainer(unsigned int PLAYER_SIDE)
	{
		__int64 duel = Game::ObjectList_GetInstanceDuel();
		if (duel <= 0) return 0;

		__int64 a = (duel)+0x20;
		a = *(__int64*)a;
		if (a <= 0) return 0;

		a = a + (PLAYER_SIDE * 0x90);

		return a;
	}

	static __int64 __fastcall ccGame_GetPlayerRole(unsigned int PLAYER_SIDE, unsigned int PLAYER_ROLE)
	{
		return reinterpret_cast<__int64(__fastcall*)(unsigned int PLAYER_SIDE, unsigned int PLAYER_ROLE)>(moduleBase + 0x85A888)(PLAYER_SIDE, PLAYER_ROLE);
	}
};

class ccGameProperty
{
public:
	__int64 m_valueA;
	__int64 m_valueB;

	static ccGameProperty* GetProperty(__int64 prop, const char* a2)
	{
		return reinterpret_cast<ccGameProperty*(__fastcall*)(__int64 prop, const char* a2)>(moduleBase + 0xAB6D30)(prop, a2);
	}

	static ccGameProperty* GetPropertyHelper(__int64 propAddress, const char* propname) // Example: GetPropertyHelper(0x1416BDA20, "titleUi");
	{
		__int64 prop = *(__int64*)((moduleBase + propAddress - 0x140000C00) + 8);
		return GetProperty(prop, propname);
	}

	static void UnknownFunction00(__int64 prop, __int64 a2, const char* a3, ccStageObjectManager* a4)
	{
		reinterpret_cast<void(__fastcall*)(__int64, __int64, const char*, ccStageObjectManager*)>(moduleBase + 0x2AC07C)(prop, a2, a3, a4);
	}
};

class nuccXfbinDocManager
{
public:
	static nuccXfbinDocManager * GetInstance()
	{
		return (nuccXfbinDocManager*)((__int64*)(moduleBase + 0x141665F30 - 0x140000C00));
	}

	static __int64 __fastcall Load(nuccXfbinDocManager * instance, const char* path, int a3)
	{
		// 0xA02B60
		return reinterpret_cast<__int64(__fastcall*)(nuccXfbinDocManager * instance, const char* path, int a3)>(moduleBase + 0xA02B60)(instance, path, a3);
	}

	static __int64 __fastcall Search(const char* path)
	{
		__int64 loadFileVar = moduleBase + 0x141665F30 - 0x140000C00;

		typedef __int64(__fastcall * funct)(__int64 a1, const char* path);
		funct fc = (funct)(moduleBase + 0xA03130);
		return fc(loadFileVar, path);
	}

	static int __fastcall GetXfbinLoadState(const char* a2)
	{
		__int64 loadFileVar = moduleBase + 0x141665F30 - 0x140000C00;

		typedef int(__fastcall * funct)(__int64 a1, const char* a2);
		funct fc = (funct)(moduleBase + 0xA02780);
		return fc(loadFileVar, a2);
	}
};

class nuccChunk
{
public:
	static const char* __fastcall GetName(nuccChunk* a1)
	{
		return reinterpret_cast<const char*(__fastcall*)(nuccChunk* a1)>(moduleBase + 0xA21C40)(a1);
	}
};

class nuccChunkList
{
public:
	static __int64 NuccChunkList(__int64 chunk)
	{
		typedef __int64(__fastcall * funct)(__int64 chunk);
		funct fc = (funct)(moduleBase + 0xA327D0);
		return fc(chunk);
	}

	static __int64 __fastcall GetSize(nuccChunkList* a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(nuccChunkList* a1)>(moduleBase + 0xA32880)(a1);
	}

	static nuccChunk* __fastcall GetChunk(nuccChunkList* a1, unsigned int a2)
	{
		return reinterpret_cast<nuccChunk*(__fastcall*)(nuccChunkList* a1, unsigned int a2)>(moduleBase + 0xA32870)(a1, a2);
	}
};

class nuccXfbinDocument
{
public:
	struct ChunkHash
	{
		int m_hash;
		int m_unk;
		const char* m_string;
	};
	
	struct ChunkSearchType
	{
		const char* chunkName;
		int m_unk00;
		int m_unk01;
		__int64 m_chunkFunct;
	};

	static __int64 SearchChunk(__int64 nuccSearch, ChunkSearchType * nuccName, ChunkHash * searchStruct)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, ChunkSearchType * a2, ChunkHash * a3);
		funct fc = (funct)(moduleBase + 0xA12DF0);
		return fc(nuccSearch, nuccName, searchStruct);
	}

	static __int64 SearchAnm(const char* xfbin, const char* anm)
	{
		typedef __int64(__fastcall * funct)(const char* xfbin, const char* anm);
		funct fc = (funct)(moduleBase + 0x863A98);
		return fc(xfbin, anm);
	}

	static void __fastcall SearchChunkList(nuccXfbinDocument* a1, ChunkSearchType* a2, __int64 a3)
	{
		return reinterpret_cast<void(__fastcall*)(nuccXfbinDocument* a1, ChunkSearchType* a2, __int64 a3)>(moduleBase + 0xA130E0)(a1, a2, a3);
	}
};

class ccGameObject
{
public:
	static __int64 __fastcall Init(__int64 objectList, __int64 object)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, __int64 a2);
		funct fc = (funct)(moduleBase + 0x2D48F4);
		return fc(objectList, object);
	}
};

class GameActor
{
public:
	class Base
	{
	public:
		static __int64 __fastcall SetPositionNew(GameActor::Base* obj, Vector3 * vector3)
		{
			typedef __int64(__fastcall * funct)(GameActor::Base* obj, Vector3 * vector3);
			funct fc = (funct)(moduleBase + 0xAC24E0);
			return fc(obj, vector3);
		}

		static __int64 __fastcall SetPositionNew(GameActor::Base* obj, float x, float z, float y)
		{
			typedef __int64(__fastcall * funct)(GameActor::Base* obj, float x, float z, float y);
			funct fc = (funct)(moduleBase + 0xAC2560);
			return fc(obj, x, z, y);
		}

		static __int64 __fastcall CreateVisibleVolume(GameActor::Base* obj)
		{
			typedef __int64(__fastcall * funct)(GameActor::Base* obj);
			funct fc = (funct)(moduleBase + 0xAC25E0);
			return fc(obj);
		}

		static __int64 __fastcall AddComponent(GameActor::Base* obj, __int64 component)
		{
			typedef __int64(__fastcall * funct)(GameActor::Base* obj, __int64 component);
			funct fc = (funct)(moduleBase + 0xAC2390);
			return fc(obj, component);
		}
	};
};

class ccCameraManager
{
public:
	__int64 vtable;

	static ccCameraManager * GetInstance() // Get current instance of camera manager
	{
		__int64 * a = (__int64*)(moduleBase + 0x14161C908 - 0x140000C00);
		ccCameraManager * b = (ccCameraManager*)(*a);

		return b;
	}

	static ccGameObject * Create(ccCameraManager * instance) // Create new camera
	{
		typedef ccGameObject*(__fastcall * funct)(ccCameraManager * instance);
		funct fc = (funct)(moduleBase + 0x525014);
		return fc(instance);
	}
};

class ccGameObjectCamera
{
public:
	__int64 vtable;

	static ccGameObjectCamera* ccGameObjectCamera_(__int64 obj, ccCameraManager * cameraManager)
	{
		typedef ccGameObjectCamera*(__fastcall * funct)(__int64 obj, ccCameraManager * cameraManager);
		funct fc = (funct)(moduleBase + 0x544FC4);
		return fc(obj, cameraManager);
	}
};

// nucc, matrix44
class Nucc
{
public:
	static int __fastcall CalcHashFromStr(const char* a1)
	{
		typedef int(__fastcall * funct)(const char* a1);
		funct fc = (funct)(moduleBase + 0xA012B0);
		return fc(a1);
	}

	class matrix44_MathGeo
	{
	public:
		char memory[112];

		static __int64 __fastcall Matrix44_MathGeo(matrix44_MathGeo * a1)
		{
			typedef __int64(__fastcall * funct)(matrix44_MathGeo * a1);
			funct fc = (funct)(moduleBase + 0xA0CC10);
			return fc(a1);
		}

		static __int64 __fastcall Matrix44_MathGeo(matrix44_MathGeo * dest, matrix44_MathGeo * source)
		{
			typedef __int64(__fastcall * funct)(matrix44_MathGeo * a1, matrix44_MathGeo * a2);
			funct fc = (funct)(moduleBase + 0xA0CC50);
			return fc(dest, source);
		}

		static __int64 __fastcall identity()
		{
			typedef __int64(__fastcall * funct)();
			funct fc = (funct)(moduleBase + 0xA0E780);
			return fc();
		}

		static __int64 __fastcall SetTranslatePart(matrix44_MathGeo* a1)
		{
			typedef __int64(__fastcall * funct)(matrix44_MathGeo* a1);
			funct fc = (funct)(moduleBase + 0xA0E160);
			return fc(a1);
		}
		
		static __int64 __fastcall SetTranslatePart(matrix44_MathGeo* a1, __int64 vector3)
		{
			typedef __int64(__fastcall * funct)(matrix44_MathGeo* a1, __int64 vector3);
			funct fc = (funct)(moduleBase + 0xA0E530);
			return fc(a1, vector3);
		}

		static __int64 __fastcall TranslatePart(matrix44_MathGeo* a1, Vector3* vector3)
		{
			typedef __int64(__fastcall * funct)(matrix44_MathGeo* a1, Vector3* vector3);
			funct fc = (funct)(moduleBase + 0xA0E530);
			return fc(a1, vector3);
		}
	};

	class Vector2
	{
	public:
		static void __fastcall Div(__int64 a1, float a2, float a3)
		{
			reinterpret_cast<void(__fastcall*)(__int64 a1, float a2, float a3)>(moduleBase + 0x823DC0)(a1, a2, a3);
		}
	};
};

class nuccChunkClump
{
public:
	static __int64 GetCoordNum(__int64 chunk)
	{
		typedef __int64(__fastcall * funct)(__int64 chunk);
		funct fc = (funct)(moduleBase + 0xA87360);
		return fc(chunk);
	}

	static __int64 GetWorldMatrix(__int64 chunk, unsigned __int16 a2, __int64 memory)
	{
		typedef __int64(__fastcall * funct)(__int64 chunk, unsigned __int16 a2, __int64 memory);
		funct fc = (funct)(moduleBase + 0xA873F0);
		return fc(chunk, a2, memory);
	}
};

class nummNudInfo
{
public:
	static ccStageObjectManager* __fastcall GetHeader()
	{
		// 0x1616C40
		typedef ccStageObjectManager*(__fastcall * funct)(__int64 scene);
		funct fc = (funct)(moduleBase + 0x187DE0);

		__int64 * a = ((__int64*)(moduleBase + 0x141617840 - 0x140000C00));

		if (*a)
		{
			return fc(*a);
		}
		else
		{
			return 0;
		}
	}

};

class ccStageGimmickAnm
{
public:
	static __int64 GetChunkClump(__int64 a1, const char * path, const char * mesh)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, const char * path, const char * mesh);
		funct fc = (funct)(moduleBase + 0x81EA30);
		return fc(a1, path, mesh);
	}
};

class ccTaskBase
{
public:
	static __int64 __fastcall EntryTaskWithAllo4(__int64 obj, const char* functName, unsigned int a3, unsigned int a4, __int64 obj2, __int64 functAddress)
	{
		typedef __int64(__fastcall * funct)(__int64 obj, const char* functName, unsigned int a3, unsigned int a4, __int64 obj2, __int64 a6);
		funct fc = (funct)(moduleBase + 0x44B320);
		return fc(obj, functName, a3, a4, obj2, functAddress);
	}

	static __int64 __fastcall EntryTaskWithAllo11(__int64 a1, const char* functName, unsigned int a3, unsigned int a4, __int64 obj2, __int64 functAddress)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, const char* functName, unsigned int a3, unsigned int a4, __int64 obj2, __int64 a6);
		funct fc = (funct)(moduleBase + 0x393024);
		return fc(a1, functName, a3, a4, obj2, functAddress);
	}

	static __int64 __fastcall DeleteAllTask(ccTaskBase* a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccTaskBase* a1)>(moduleBase + 0xAB34E0)(a1);
	}
};

class ccCpuGroupLiteBase
{
public:
	static __int64 __fastcall SetBehavior_88_2(__int64 obj)
	{
		typedef __int64(__fastcall * funct)(__int64 obj);
		funct fc = (funct)(moduleBase + 0x44B654);
		return fc(obj);
	}
};

class ccChakraBall
{
public:
	static __int64 __fastcall CcChakraBall(__int64 obj)
	{
		typedef __int64(__fastcall * funct)(__int64 obj);
		funct fc = (funct)(moduleBase + 0x74FD44);
		return fc(obj);
	}

	static __int64 __fastcall Initialize(__int64 obj)
	{
		typedef __int64(__fastcall * funct)(__int64 obj);
		funct fc = (funct)(moduleBase + 0x7504F0);
		return fc(obj);
	}
};

class nuccFileLoadList
{
public:
	struct loadStruct
	{
		std::string path;
		nuccFileLoadList * ptr;

		loadStruct(const char* filename, nuccFileLoadList* p)
		{
			path = std::string(filename);
			ptr = p;
		}
	};

	static __int64 __fastcall NuccFileLoadList(__int64 a1)
	{
		typedef __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0xA044E0);
		return fc(a1);
	}

	static __int64 __fastcall Load(__int64 a1, const char* path)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, const char* path);
		funct fc = (funct)(moduleBase + 0xA04870);
		return fc(a1, path);
	}

	static __int64 LoadHelper(__int64 objectList, const char* path, bool altList = false)
	{
		__int64 list = Game::operator_new(0x40, "", 0xB4);

		if (list)
		{
			list = NuccFileLoadList(list);
			std::cout << "Attempting to load file " << path << " at " << std::hex << std::uppercase << list << std::endl;

			// Attempt to load
			__int64 r = Load(list, path);
		}
		else
		{
			std::cout << "Error loading file " << path << std::endl;
		}

		return list;
	}

	static bool CheckIfLoaded(const char* path)
	{
		// Check if loaded
		int timeout = 120;
		int isFileLoaded = -1;
		bool found = false;

		while (timeout > 0 && !found)
		{
			found = (nuccXfbinDocManager::GetXfbinLoadState(path) == 2);
			timeout--;
			Sleep(1);
		}

		return found;
	}

	static __int64 UnloadByIndex(nuccFileLoadList* list, unsigned int index)
	{
		typedef __int64(__fastcall * funct)(nuccFileLoadList* list, unsigned int index);
		funct fc = (funct)(moduleBase + 0xA04B60);
		return fc(list, index);
	}

	static __int64 UnloadByPath(nuccFileLoadList* list, const char* path)
	{
		typedef __int64(__fastcall * funct)(nuccFileLoadList* list, const char* path);
		funct fc = (funct)(moduleBase + 0xA04C10);
		return fc(list, path);
	}
};

class ccFlash
{
public:
	static __int64 __fastcall CcFlash(__int64 a1)
	{
		typedef __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0x6583DC);
		return fc(a1);
	}
};

class ccUiDialog
{
public:
	static __int64 __fastcall AllocateMessageWindow(__int64 flash, const char* scene, int n1, int n2)
	{
		typedef __int64(__fastcall * funct)(__int64 flash, const char* scene, int n1, int n2);
		funct fc = (funct)(moduleBase + 0x658758);
		return fc(flash, scene, n1, n2);
	}

	static __int64 __fastcall OpenMessageWindow(__int64 flash, const char* message, int a3)
	{
		typedef __int64(__fastcall * funct)(__int64 flash, const char* message, int a3);
		funct fc = (funct)(moduleBase + 0x658B80);
		return fc(flash, message, a3);
	}

	static __int64 __fastcall EnableWordWrap(__int64 a1, float a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, float a2);
		funct fc = (funct)(moduleBase + 0x658A58);
		return fc(a1, a2);
	}

	static __int64 __fastcall Open(__int64 a1)
	{
		typedef __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0x6589F4);
		return fc(a1);
	}

	static __int64 __fastcall CloseWindow(__int64 a1)
	{
		typedef __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0x6586F8);
		return fc(a1);
	}

	static __int64 __fastcall SetFixedWindowSize(__int64 a1, float a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, float a2);
		funct fc = (funct)(moduleBase + 0x658AEC);
		return fc(a1, a2);
	}
};

struct NuccChunkFindHelper
{
	int namehash;
	char v11;
	char padding[3];
	const char * v12;
};

class unnamed
{
public:
	static void __fastcall sub_140594A4C(__int64 a1, int edx0)
	{
		reinterpret_cast<void(__fastcall*)(__int64 a1, int edx0)>(moduleBase + 0x593E4C)(a1, edx0);
	}

	static __int64 __fastcall sub_14061BE84(__int64 a1)
	{
		typedef __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0x61B284);
		return fc(a1);
	}

	static void __fastcall openMenuBrtPast(__int64 a1)
	{
		typedef void(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0x61D884);
		fc(a1);
	}

	static __int64 __fastcall sub_1404DA8A8(__int64 objList, const char* path, const char* mesh)
	{
		typedef __int64(__fastcall * funct)(__int64 objList, const char* path, const char* mesh);
		funct fc = (funct)(moduleBase + 0x4D9CA8);
		return fc(objList, path, mesh);
	}

	static __int64 __fastcall sub_1404DAC48(__int64 objList, int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 objList, int a2);
		funct fc = (funct)(moduleBase + 0x4DA048);
		return fc(objList, a2);
	}

	static __int64 __fastcall ccEntryGroupModelTest(float a1, float a2, float a3)
	{
		typedef __int64(__fastcall * funct)(float x, float y, float z);
		funct fc = (funct)(moduleBase + 0x450210);
		return fc(27, 132, 273);
	}

	static __int64 __fastcall ccEntryBoss04Phase01_LiteSmall(int a1, float a2, float a3, float a4)
	{
		typedef __int64(__fastcall * funct)(float a1, float x, float y, float z);
		funct fc = (funct)(moduleBase + 0x44F634);
		return fc(0, a2, a3, a4);
	}

	static __int64 __fastcall modelCreateConst_sub_140A04E80()
	{
		typedef __int64(__fastcall * funct)();
		funct fc = (funct)(moduleBase + 0xA04280);
		return fc();
	}

	static int __fastcall ccLoadFile(const char * file)
	{
		typedef int(__fastcall * funct)(const char* file);
		funct fc = (funct)(moduleBase + 0x534FF4);
		return fc(file);
	}

	static __int64 __fastcall ccCreateFilter(const char * path, const char* tex)
	{
		typedef int(__fastcall * funct)(const char* path, const char* tex);
		funct fc = (funct)(moduleBase + 0x5360D4);
		return fc(path, tex);
	}

	static void __fastcall ccSndBgmCtrl(int snd, __int64 a2)
	{
		typedef void(__fastcall * funct)(int snd, __int64 a2);
		funct fc = (funct)(moduleBase + 0x720528);
		return fc(snd, a2);
	}
	
	static void __fastcall PlaySEHelper(unsigned int snd, int a2, int a3)
	{
		__int64 sndListener = *((__int64*)(moduleBase + 0x141610160 - 0x140000C00));

		typedef void(__fastcall * funct)(__int64 listener, unsigned int snd, int dep1, int dep2, int a2, int a3);
		funct fc = (funct)(moduleBase + 0x73CC60);
		return fc(sndListener, snd, 0, 0, a2, a3);
	}

	static __int64 __fastcall ccAdvPlaySound_2D(int a1)
	{
		// 0x4DC7D0
		typedef __int64(__fastcall * funct)(int a1);
		funct fc = (funct)(moduleBase + 0x4DC7D0);
		return fc(a1);
	}

	void __fastcall ccAdvSelectWindowOpen()
	{
		// 0x4DCBC0
		typedef void(__fastcall * funct)();
		funct fc = (funct)(moduleBase + 0x4DCBC0);
		return fc();
	}

	__int64 sub_14051E4A4()
	{
		typedef __int64(__fastcall * funct)();
		funct fc = (funct)(moduleBase + 0x51D8A4);
		return fc();
	}

	void __fastcall sub_14063C1AC(__int64 a)
	{
		// 0x4DCBC0
		typedef void(__fastcall * funct)(__int64 a);
		funct fc = (funct)(moduleBase + 0x63B5AC);
		return fc(a);
	}

	__int64 __fastcall sub_14066D1B8(__int64 a)
	{
		typedef __int64(__fastcall * funct)(__int64 a);
		funct fc = (funct)(moduleBase + 0x66C5B8);
		return fc(a);
	}

	static __int64 GetLoDemoState()
	{
		typedef __int64(__fastcall * funct)();
		funct fc = (funct)(moduleBase + 0x563414);
		return fc();

	}

	static __int64 GetAdvManager()
	{
		typedef __int64(__fastcall * funct)();
		funct fc = (funct)(moduleBase + 0x51CBCC);
		return fc();
	}

	static __int64 ccClearStage()
	{
		typedef __int64(__fastcall * funct)();
		funct fc = (funct)(moduleBase + 0x5382C4);
		return fc();
	}

	static __int64 ccSetZRange(float a1, float a2)
	{
		// 14161A340
		__int64 a = Game::ObjectList_GetInstanceLightsAndFog();

		typedef __int64(__fastcall * funct)(...);
		funct fc = (funct)(moduleBase + 0x537DA4);
		return fc(a, 0, a1, a2);
	}

	static __int64 ccGetAdvPlayer()
	{
		typedef __int64(__fastcall * funct)();
		funct fc = (funct)(moduleBase + 0x51CC88);
		return fc();
	}

	static __int64 ccEntryGroupBattleChar(const char* charId, bool bool1, bool bool2, float posx, float posy, float posz, int unkint0, int unkint1, const char* _str)
	{
		typedef __int64(__fastcall * funct)(const char* charId, bool bool1, bool bool2, float posx, float posy, float posz, int unkint0, int unkint1, const char* _str, int a);
		funct fc = (funct)(moduleBase + 0x44F818);
		return fc(charId, bool1, bool2, posx, posy, posz, unkint0, unkint1, _str, unkint1);
	}
	
	static int __fastcall ccPlayerPoolSet(const char* id, unsigned int a2)
	{
		typedef int(__fastcall * funct)(const char* id, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x451A60);
		return fc(id, a2);
	}

	static int __fastcall ccRemoveGroupBattleChar(int a1, int a2, const char* id)
	{
		typedef int(__fastcall * funct)(int a1, int a2, const char* id);
		funct fc = (funct)(moduleBase + 0x451A8C);
		return fc(a1, a2, id);
	}

	static void __fastcall ccChangeBossBattleById(const char* battle, bool b)
	{
		typedef void(__fastcall * funct)(const char* battle, bool b);
		funct fc = (funct)(moduleBase + 0x4DD254);
		return fc(battle, b);
	}

	static __int64 __fastcall ccGetNuccChunk(__int64 nuccType, const char* path, __int64 helper)
	{
		// 0xAB2190
		typedef __int64(__fastcall * funct)(__int64 nuccType, const char* path, __int64 helper);
		funct fc = (funct)(moduleBase + 0xAB2190);
		return fc(nuccType, path, helper);
	}
	
	static bool __fastcall ccWorldToScreenAppNew(Vector3 * dest, Vector3 * source)
	{
		typedef bool(__fastcall * funct)(Vector3 * a, Vector3* b);
		funct fc = (funct)(moduleBase + 0x86657C);
		return fc(dest, source);
	}

	static __int64 __fastcall ccSetLightColor(int a, int b)
	{
		__int64 l = GetLoDemoState();
		DWORD old = 0;

		// If no lo demo state, then we do a little fix.
		if (!l) old = Utilities::ChangeProtect(moduleBase + 0x53784D, 1, PAGE_EXECUTE_READWRITE);

		typedef __int64(__fastcall * funct)(int a, int b);
		funct fc = (funct)(moduleBase + 0x537834);
		__int64 ret = fc(a, b);

		// Restore it
		if (!l) Utilities::ChangeProtect(moduleBase + 0x53784D, 1, old);

		return ret;
	}

	static __int64 __fastcall ccCreateValleyStageEffect(__int64 empty, ccStageObjectList * objList_plus168)
	{
		typedef __int64(__fastcall * funct)(__int64 empty, ccStageObjectList* objList_plus168);
		funct fc = (funct)(moduleBase + 0x81AD24);
		return fc(empty, objList_plus168);
	}

	static __int64 __fastcall ccIa_FadeIn(int a1, float a2, float a3, float a4)
	{
		typedef __int64(__fastcall * funct)(int a1, float a2, float a3, float a4);
		funct fc = (funct)(moduleBase + 0x46A250);
		return fc(a1, a2, a3, a4);
	}

	static __int64 __fastcall ccIa_FadeOut(int a1, float a2, float a3, float a4)
	{
		typedef __int64(__fastcall * funct)(int a1, float a2, float a3, float a4);
		funct fc = (funct)(moduleBase + 0x46A320);
		return fc(a1, a2, a3, a4);
	}

	static __int64 ccChangeBattleById(const char* battleId, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(const char* battleId, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x4DD020);
		return fc(battleId, a2);
	}

	static void __fastcall DoFlashFunctionJump_0(__int64 a1, const char* a2, const char *a3, const char *a4)
	{
		typedef void(__fastcall * funct)(__int64 a1, const char* a2, const char *a3, const char *a4);
		funct fc = (funct)(moduleBase + 0x606F5C);
		return fc(a1, a2, a3, a4);
	}

	static void __fastcall DoFlashFunction(__int64 a1, const char* stringParameter, const char *flashrootnut, const char *functionName, __int64 a5)
	{
		typedef void(__fastcall * funct)(__int64 a1, const char* stringParameter, const char *flashrootnut, const char *functionName, __int64 a5);
		funct fc = (funct)(moduleBase + 0x606FA0);
		return fc(a1, stringParameter, flashrootnut, functionName, a5);
	}

	static __int64 __fastcall SetStageInfo(__int64 a1, int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, int a2);
		funct fc = (funct)(moduleBase + 0x68BF00);
		return fc(a1, a2);
	}

	static __int64 __fastcall sub_14085FCA0(__int64 a1, float a2)
	{
		return reinterpret_cast<__int64(__fastcall*)(__int64 a1, float a2)>(moduleBase + 0x85F0A0)(a1, a2);
	}

	static void __fastcall showPurposeMessage(const char* msg)
	{
		reinterpret_cast<void(__fastcall*)(const char*)>(moduleBase + 0x452700)(msg);
	}

	static void sub_14044F5B0(__int64 a1, int a2)
	{
		reinterpret_cast<void(__fastcall*)(__int64, int)>(moduleBase + 0x44E9B0)(a1, a2);
	}

	static __int64 sub_14063F164(__int64 a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(__int64)>(moduleBase + 0x63E564)(a1);
	}

	static void sub_14030F7D8(__int64 a1, __int64 a2, const char* a3, __int64 a4)
	{
		reinterpret_cast<void(__fastcall*)(__int64, __int64, const char*, __int64)>(moduleBase + 0x30EBD8)(a1, a2, a3, a4);
	}

	static void sub_1403E4428(__int64 a1)
	{
		reinterpret_cast<void(__fastcall*)(__int64)>(moduleBase + 0x3E3828)(a1);
	}
};

class ccUiSelectWindow
{
public:
	static ccUiSelectWindow* CcUiSelectWindow(__int64 a1, char *a2, int a3)
	{
		typedef ccUiSelectWindow*(__fastcall * funct)(__int64 a1, char *a2, int a3);
		funct fc = (funct)(moduleBase + 0x6A30C0);
		return fc(a1, a2, a3);
	}

	static __int64 __fastcall SetYesNoSelect(ccUiSelectWindow* flash, const char* msg, int a2)
	{
		typedef __int64(__fastcall * funct)(ccUiSelectWindow* flash, const char* msg, int a2);
		funct fc = (funct)(moduleBase + 0x6A4DFC);
		return fc(flash, msg, a2);
	}

	static __int64 __fastcall sub_1406A4B94(ccUiSelectWindow* a1, unsigned int *a2, const char**a3, unsigned int a4, int a5, unsigned int a6)
	{
		typedef __int64(__fastcall * funct)(ccUiSelectWindow* a1, unsigned int *a2, const char**a3, unsigned int a4, int a5, unsigned int a6);
		funct fc = (funct)(moduleBase + 0x6A3F94);
		return fc(a1, a2, a3, a4, a5, a6);
	}
	
	static void __fastcall sub_140B117F0(ccUiSelectWindow* a1, __int64 a2, int a3, int a4)
	{
		typedef void(__fastcall * funct)(ccUiSelectWindow* a1, __int64 a2, int a3, int a4);
		funct fc = (funct)(moduleBase + 0xB0EAF0);
		return fc(a1, a2, a3, a4);
	}
};

class ccUiSelectList
{
public:
	static void __fastcall SetSelect(ccUiSelectWindow* a1, int a2)
	{
		typedef void(__fastcall * funct)(ccUiSelectWindow* a1, int a2);
		funct fc = (funct)(moduleBase + 0x620C38);
		fc(a1, a2);
	}

	static void __fastcall PushKeyHelp(ccUiSelectWindow* a1)
	{
		typedef void(__fastcall * funct)(ccUiSelectWindow* a1);
		funct fc = (funct)(moduleBase + 0x6A3F5C);
		fc(a1);
	}

	static __int64 __fastcall GetKeyHelp(ccUiSelectWindow* a1)
	{
		typedef __int64(__fastcall * funct)(ccUiSelectWindow* a1);
		funct fc = (funct)(moduleBase + 0x6A3E10);
		return fc(a1);
	}
};

class nuccCOLOR
{
public:
	static __int64 nuccColor(__int64 mem, float r, float g, float b)
	{
		struct color
		{
			float a = 0;
			float rc = 0;
			float gc = 0;
			float bc = 0;
		};

		color c;
		c.rc = r;
		c.gc = g;
		c.bc = b;

		typedef __int64(__fastcall * funct)(...);
		funct fc = (funct)(moduleBase + 0xA13570);
		fc(mem, &(c.a));
		
		return mem;
	}
};

class ccEventChara
{
public:
	static __int64 CcEventChara(__int64 allocation, __int64 objList)
	{
		typedef __int64(__fastcall * funct)(__int64 allocation, __int64 objList);
		funct fc = (funct)(moduleBase + 0x53AE98);
		return fc(allocation, objList);
	}

	static __int64 Create(__int64 objectList, const char * xfbin, const char * meshname)
	{
		typedef __int64(__fastcall * funct)(__int64 objectList, const char * xfbin, const char * meshname);
		funct fc = (funct)(moduleBase + 0x53B654);
		return fc(objectList, xfbin, meshname);
	}
};

class ccStageEffectFilterRain
{
public:
	static __int64 Create(__int64 a1)
	{
		typedef __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0x8216FC);
		return fc(a1);
	}
};

class ccStageEffectRain
{
public:
	static __int64 Create(__int64 a1)
	{
		typedef __int64(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0x821D7C);
		return fc(a1);
	}
};

class ccDuelManager
{
public:
	static __int64 Clear(__int64 objListDuel)
	{
		typedef __int64(__fastcall * funct)(__int64 objListDuel);
		funct fc = (funct)(moduleBase + 0x74D02C);
		return fc(objListDuel);
	}
};

enum nuccChunkTypes
{
	nuccChunkModel,
	nuccChunkTexture,
	nuccChunkClump,
	nuccChunkAnm,
	nuccChunkBinary,
	nuccChunkModelHit
};

class FrameworkHelpers
{
public:
	static ccCmnScreenManager * GetCmnScreenManager()
	{
		ccCmnScreenManager * cmn = nullptr;

		ccCmnScreenManager* cmnScreenManager = Game::GetCmnScreenManager();
		if (cmnScreenManager) cmn = (ccCmnScreenManager*)cmnScreenManager;

		return cmn;
	}

	static ccCmnCameraDirector * GetCameraDirector()
	{
		ccCmnCameraDirector * cd = nullptr;
		ccCmnScreenManager * cmn = GetCmnScreenManager();

		if (cmn)
		{
			cd = (ccCmnCameraDirector*)(ccCmnScreenManager::GetCameraDirector((ccCmnScreenManager*)cmn, 0));
		}

		return cd;
	}

	static ccCmnCamera * GetActiveCamera()
	{
		ccCmnCamera * c = nullptr;
		ccCmnCameraDirector * cd = GetCameraDirector();

		if (cd)
		{
			c = (ccCmnCamera*)(ccCmnCameraDirector::GetActiveCamera(cd));
		}

		return c;
	}

	static __int64 __fastcall UpdateAnmCamNOP(__int64 a1)
	{
		return *(__int64*)(a1 + 432);
	}

	static __int64 __fastcall DisableCameraMovementHook(__int64 a1, Vector3 *a2, Vector3 *a3, Vector3 *a4)
	{
		return 0;
	}

	static void EnableCameraMovement()
	{
		// 48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18
		char restore[15] = { 0x48, 0x8b, 0xc4, 0x48, 0x89, 0x58, 0x08, 0x48, 0x89, 0x70, 0x10, 0x48, 0x89, 0x78, 0x18 };
		char restore2[5] = { 0xF3, 0x0F, 0x11, 0x77, 0x6C };
		__int64 vtable_originalOperatorAnm = moduleBase + 0x8540EC;

		DWORD dwOld = 0;
		VirtualProtect((void*)(moduleBase + 0xAC7990), 15, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(moduleBase + 0xAC7990), &restore[0], 15);
		VirtualProtect((void*)(moduleBase + 0xAC7990), 15, dwOld, &dwOld);

		// NOP FOV
		dwOld = 0;
		VirtualProtect((void*)(moduleBase + 0x743420), 5, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(moduleBase + 0x743420), &restore2[0], 5);
		VirtualProtect((void*)(moduleBase + 0x743420), 5, dwOld, &dwOld);
		
		// Enable Cam Anm Operator
		ReplaceVirtualFunction(0x1410E8B68, (void*)vtable_originalOperatorAnm);
	}

	static void DisableCameraMovement()
	{
		typedef void(__stdcall *HookFunct)(void* toHook, void* ourFunct, int len);
		HookFunct Hook = (HookFunct)hookFunct;

		Hook((void*)(moduleBase + 0xAC7990), DisableCameraMovementHook, 15);

		char nop[5] = { 0x90, 0x90, 0x90, 0x90, 0x90 };

		// NOP FOV
		DWORD dwOld = 0;
		VirtualProtect((void*)(moduleBase + 0x743420), 5, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(moduleBase + 0x743420), &nop[0], 5);
		VirtualProtect((void*)(moduleBase + 0x743420), 5, dwOld, &dwOld);

		// 48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18

		// Disable Cam Anm Operator
		ReplaceVirtualFunction(0x1410E8B68, UpdateAnmCamNOP);
	}

	static void SetFog(float r, float g, float b, float near_, float far_, float clampfar)
	{
		__int64 a = Game::ObjectList_GetPtrLightsAndFog();
		__int64 fogparam = ccGameDrawEnv::GetFogParamPtr(a, 0);

		float fogcolor[4];
		fogcolor[0] = r;
		fogcolor[1] = g;
		fogcolor[2] = b;

		if (fogparam)
		{
			ccGameDrawEnv::SetFogParam(a, 0, (__int64)fogcolor, near_, far_, clampfar);
		}
	}

	static void SetLightColor(int a1, int a2)
	{
		// Patch b8 01 00 00 00 
		char patch[5] = { 0xB8, 0x01, 0x00, 0x00, 0x00 };
		DWORD dwOld = 0;
		VirtualProtect((void*)(moduleBase + 0x537845), 5, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(moduleBase + 0x537845), &patch[0], 5);
		VirtualProtect((void*)(moduleBase + 0x537845), 5, dwOld, &dwOld);

		typedef __int64(__fastcall * funct)(int a, int b);
		funct fc = (funct)(moduleBase + 0x537834);
		fc(a1, a2);

		// Unpatch E8 CA BB 02 00
		char patch2[5] = { 0xE8, 0xCA, 0xBB, 0x02, 0x00 };
		dwOld = 0;
		VirtualProtect((void*)(moduleBase + 0x537845), 5, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(moduleBase + 0x537845), &patch2[0], 5);
		VirtualProtect((void*)(moduleBase + 0x537845), 5, dwOld, &dwOld);
	}

	static __int64 __fastcall WaitVSync(__int64 a1)
	{
		Sleep(1);
		return 0;
	}

	static void ReplaceVirtualFunction(__int64 original_140000000, void * funct)
	{
		__int64 * a = (__int64*)(moduleBase - 0xC00 + original_140000000 - 0x140000000);

		DWORD dwOld = 0;
		VirtualProtect((void*)(a), 8, PAGE_EXECUTE_READWRITE, &dwOld);

		*a = (__int64)funct;
		std::cout << "Replaced vfunct at " << std::hex << (__int64)a << std::endl;

		VirtualProtect((void*)(a), 8, dwOld, &dwOld);
	}

	static ccStageObjectList * GetStageObjectListGlobal()
	{
		ccStageManager* stageManager = ccStageManager::GetInstance();

		if (stageManager)
		{
			ccStageObjectManager* stgObjManager = ccStageObjectManager::GetManager(stageManager);

			if (stgObjManager > 0)
			{
				int num = ccStageObjectManager::GetObjectListNum(stgObjManager);

				ccStageObjectList* objList = ccStageObjectManager::GetObjectList(stgObjManager, 0);
				return objList;
			}
			else
			{
				//std::cout << "No stage obj manager" << std::endl;
			}
		}
		else
		{
			//std::cout << "No stage manager" << std::endl;
		}

		return nullptr;
	}

	static __int64 FindNuccChunk(nuccChunkTypes nuccType, const char* path, const char* name)
	{
		__int64 type = 0;
		switch (nuccType)
		{
		default:
			return 0;
		case nuccChunkTypes::nuccChunkTexture:
			type = (moduleBase + 0x141560A90 - 0x140000C00);
			break;
		case nuccChunkTypes::nuccChunkModel:
			type = (moduleBase + 0x141560AA8 - 0x140000C00);
			break;
		case nuccChunkTypes::nuccChunkModelHit:
			type = (moduleBase + 0x141560AC0 - 0x140000C00);
			break;
		case nuccChunkTypes::nuccChunkAnm:
			type = (moduleBase + 0x141560B08 - 0x140000C00);
			break;
		case nuccChunkTypes::nuccChunkClump:
			type = (moduleBase + 0x141560CD0 - 0x140000C00);
			break;
		}

		NuccChunkFindHelper helper;
		helper.namehash = Nucc::CalcHashFromStr(name);
		helper.v11 = 1;
		helper.v12 = name;
		__int64 result = unnamed::ccGetNuccChunk(type, path, (__int64)(&(helper.namehash)));

		//std::cout << "Result: " << std::hex << result << std::endl;
		return result;
	}

	static void ListChunkType(std::string chunk, const char* file)
	{
		__int64 chunkTypeAddress = 0;
		if (&chunk == nullptr) return;

		if (chunk == "nuccChunkAnm") chunkTypeAddress = moduleBase + 0x141560B08 - 0x140000C00;
		else if (chunk == "nuccChunkModel") chunkTypeAddress = moduleBase + 0x141560AA8 - 0x140000C00;
		else if (chunk == "nuccChunkTexture") chunkTypeAddress = moduleBase + 0x141560A90 - 0x140000C00;
		else if (chunk == "nuccChunkSprite") chunkTypeAddress = moduleBase + 0x141560B50 - 0x140000C00;
		else if (chunk == "nuccChunkClump") chunkTypeAddress = moduleBase + 0x141560CD0 - 0x140000C00;
		else if (chunk == "nuccChunkCoord") chunkTypeAddress = moduleBase + 0x141560B38 - 0x140000C00;
		else return;

		nuccChunkList* data_ = (nuccChunkList*)malloc(128);
		__int64 doc = nuccXfbinDocManager::Search(file);

		if (doc)
		{
			nuccChunkList::NuccChunkList((__int64)data_);
			nuccXfbinDocument::SearchChunkList((nuccXfbinDocument*)doc, (nuccXfbinDocument::ChunkSearchType*)(chunkTypeAddress), (__int64)data_);
			//return;

			int actualChunk = 0;
			if (nuccChunkList::GetSize(data_))
			{
				while (actualChunk < nuccChunkList::GetSize(data_))
				{
					nuccChunk* chunkData = nuccChunkList::GetChunk(data_, actualChunk);
					const char* chunkName = nuccChunk::GetName(chunkData);
					std::cout << chunk << " " << actualChunk << ": " << chunkName << std::endl;

					actualChunk++;
				}
			}
		}
	}
};

class HookHelpers
{
	static signed __int64 GetLoDemoStateByPass()
	{
		return 1;
	}
};

class ColorFilterDirectionalSettings
{
public:
	bool enable = false;
	float alphaBlend = 1;
	float unk00 = 0;
	float unk01 = 0;
	Vector4 colorA = Vector4();
	Vector4 colorB = Vector4();
	Vector4 colorC = Vector4();
	Vector2 direction = Vector2();
	Vector2 scale = Vector2();
	float middlePoint = 0;

	static void SetSettings(__int64 lightsAndFogPtr, ColorFilterDirectionalSettings * settings)
	{
		__int64 ptr = lightsAndFogPtr;

		*(bool*)(ptr + 2048) = settings->enable;
		*(float*)(ptr + 2052) = settings->alphaBlend;
		*(Vector4*)(ptr + 2064) = settings->colorA;
		*(Vector4*)(ptr + 2080) = settings->colorB;
		*(Vector4*)(ptr + 2096) = settings->colorC;
		*(Vector2*)(ptr + 2112) = settings->direction;
		*(Vector2*)(ptr + 2120) = settings->scale;
		*(float*)(ptr + 2128) = settings->middlePoint;
	}
};

class nuccFont2
{
public:
	static nuccFont2 * NuccFont2(nuccFont2 * mem)
	{
		typedef nuccFont2*(__fastcall * funct)(nuccFont2 * mem);
		funct fc = (funct)(moduleBase + 0xA36790);
		return fc(mem);
	}

	static __int64 __fastcall SetColor(float * a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(float * a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0xA38620);
		return fc(a1, a2);
	}

	static __int64 __fastcall SetPosChar(nuccFont2* a1, int a2, int a3)
	{
		typedef __int64(__fastcall * funct)(nuccFont2* a1, int a2, int a3);
		funct fc = (funct)(moduleBase + 0xA38690);
		return fc(a1, a2, a3);
	}

	static __int64 __fastcall Print(nuccFont2 * a1, const char* a2)
	{
		typedef __int64(__fastcall * funct)(nuccFont2 * a1, const char* a2);
		funct fc = (funct)(moduleBase + 0xA382A0);
		return fc(a1, a2);
	}

	static __int64 __fastcall Draw(nuccFont2 * a1)
	{
		typedef __int64(__fastcall * funct)(nuccFont2 * mem);
		funct fc = (funct)(moduleBase + 0xA36EB0);
		return fc(a1);
	}

	static __int64 __fastcall DeleteOperator(nuccFont2 * a1)
	{
		typedef __int64(__fastcall * funct)(nuccFont2 * mem);
		funct fc = (funct)(moduleBase + 0xA36900);
		return fc(a1);
	}
};

class nuccFont2ParamManager
{
public:
	static void __fastcall Initialize(unsigned int a1)
	{
		// 0xA8CF40
		reinterpret_cast<void(__fastcall*)(unsigned int a1)>(moduleBase + 0xA8CF40)(a1);
	}
};

class GameLua
{
public:
	static void __fastcall ccSetGroupBattleCharPos(int side, const char* charid, float posx, float posy, float posz, int a1, int a2, int a3)
	{
		typedef void(__fastcall * funct)(int side, const char* charid, float posx, float posy, float posz, int a1, int a2, int a3);
		funct fc = (funct)(moduleBase + 0x4521F0);
		return fc(side, charid, posx, posy, posz, a1, a2, a3);
	}

	static __int64 __fastcall ccEntryGroupBattleChar(const char* charid, bool a1, bool a2, float posx, float posy, float posz, int a3, int a4, const char* str2, double a5)
	{
		// ccEntryGroupBattleChar
		typedef __int64(__fastcall * funct)(const char* charid, bool a1, bool a2, float posx, float posy, float posz, int a3, int a4, const char* str2, double a5);
		funct fc = (funct)(moduleBase + 0x44F818);
		return fc(charid, a1, a2, posx, posy, posz, a3, a4, str2, a5);
	}

	static __int64 __fastcall ccPlayerPoolSet(const char* charid, int count)
	{
		typedef __int64(__fastcall * funct)(const char* charid, int count);
		funct fc = (funct)(moduleBase + 0x451A60);
		return fc(charid, count);
	}

	static int __fastcall ccEntryReSpawnID(const char* charid, int count, double a1)
	{
		typedef int(__fastcall * funct)(const char* charid, int count, double a1);
		funct fc = (funct)(moduleBase + 0x450310);
		return fc(charid, count, a1);
	}

	static int __fastcall ccOpenPurpose(const char* text)
	{
		return reinterpret_cast<int(__fastcall*)(const char*)>(moduleBase + 0x4519CC)(text);
	}

	static __int64 __fastcall ccClosePurpose()
	{
		return reinterpret_cast<__int64(__fastcall*)()>(moduleBase + 0x44F3A4)();
	}
};

class ccPlayerAnmIdManager
{
public:
	static const char* __fastcall GetName(int a1)
	{
		typedef const char*(__fastcall * funct)(int a1);
		funct fc = (funct)(moduleBase + 0x529884);
		return fc(a1);
	}
};

class ccScene
{
public:
	static __int64 Constructor(ccScene* a1)
	{
		typedef __int64(__fastcall * funct)(ccScene* a1);
		funct fc = (funct)(moduleBase + 0xAB3760);
		return fc(a1);
	}

	static __int64 __fastcall SetSceneName(ccScene* a1, const char * a2)
	{
		typedef __int64(__fastcall * funct)(ccScene* a1, const char * a2);
		funct fc = (funct)(moduleBase + 0xAB3950);
		return fc(a1, a2);
	}

	static bool AuthorizeGameProperty(__int64 a1)
	{
		return reinterpret_cast<bool(__fastcall*)(__int64)>(moduleBase + 0xAB39B0)(a1);
	}
};

class ccUiKeyHelp
{
public:
	static __int64 GetInstance()
	{
		return *((__int64*)(moduleBase + 0x14161C8E8 - 0x140000C00));
	}

	static void __fastcall AddHelp(__int64 a1, int a2)
	{
		typedef void(__fastcall * funct)(__int64 a1, int a2);
		funct fc = (funct)(moduleBase + 0x669EEC);
		return fc(a1, a2);
	}

	static __int64 __fastcall PushKeyHelp(__int64 a1, unsigned int a2)
	{
		typedef __int64(__fastcall * funct)(__int64 a1, unsigned int a2);
		funct fc = (funct)(moduleBase + 0x66A294);
		return fc(a1, a2);
	}

	static __int64 __fastcall CcUiKeyHelp(ccUiKeyHelp * a1, const char* ctrlTask, int a3, int a4, const char* drawTask, int a6, int a7)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccUiKeyHelp * a1, const char* ctrlTask, int a3, int a4, const char* drawTask, int a6, int a7)>(moduleBase + 0xB1C5A0)(a1, ctrlTask, a3, a4, drawTask, a6, a7);
	}

	static __int64 __fastcall CcUiKeyHelp(ccUiKeyHelp * a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccUiKeyHelp * a1)>(moduleBase + 0xB1C4B0)(a1);
	}

	static __int64 __fastcall Initialize(ccUiKeyHelp * a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccUiKeyHelp * a1)>(moduleBase + 0xB1C730)(a1);
	}
};

class ccCmnFade
{
public:
	static __int64 GetInstance()
	{
		return *((__int64*)(moduleBase + 0x14161C8D0 - 0x140000C00));
	}

	static void __fastcall AddHelp(__int64 a1, float* a2)
	{
		return reinterpret_cast<void(__fastcall*)(__int64 a1, float* a2)>(moduleBase + 0x65F674)(a1, a2);
	}

	static __int64 __fastcall StartFadeIn(__int64 a1, int a2)
	{
		return reinterpret_cast<__int64(__fastcall*)(__int64 a1, int a2)>(moduleBase + 0x65F6B4)(a1, a2);
	}

	static __int64 __fastcall StartFadeOut(__int64 a1, int a2)
	{
		return reinterpret_cast<__int64(__fastcall*)(__int64 a1, int a2)>(moduleBase + 0x65F838)(a1, a2);
	}
};

class ccFileLoadListForUi
{
public:
	static ccFileLoadListForUi * Instantiate()
	{
		__int64 mem = Game::operator_new(0x30, "", 0xF7);
		ccFileLoadListForUi * list = Create(mem);
		return list;
	}

	static ccFileLoadListForUi * Create(__int64 a1) // ccFileLoadListForUi::ccFileLoadListForUi
	{
		typedef ccFileLoadListForUi*(__fastcall * funct)(__int64 a1);
		funct fc = (funct)(moduleBase + 0xABDE10);
		return fc(a1);
	}

	static __int64 __fastcall LoadTh(ccFileLoadListForUi* a1, const char* a2)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccFileLoadListForUi* a1, const char* a2)>(moduleBase + 0xABE020)(a1, a2);
	}
};

class ccUiSimpleDraw
{
public:
	static void __fastcall CreateUiObjBootLogo(__int64 a1, const char* name)
	{
		return reinterpret_cast<void(__fastcall*)(__int64 a1, const char* name)>(moduleBase + 0x862820)(a1, name);
	}

	static void __fastcall DeleteUiObjBootLogo(__int64 a1)
	{
		return reinterpret_cast<void(__fastcall*)(__int64 a1)>(moduleBase + 0x8629D8)(a1);
	}

	static __int64 __cdecl ccCreateSimpleDrawUi(const char* a)
	{
		return reinterpret_cast<__int64(__cdecl*)(const char* a)>(moduleBase + 0x823E3C)(a);
	}

	static __int64 __fastcall CreateUiObj(__int64 a1, const char* path, const char* name, int a4)
	{
		return reinterpret_cast<__int64(__fastcall*)(__int64 a1, const char* path, const char* name, int a4)>(moduleBase + 0x823CD4)(a1, path, name, a4);
	}

	static void SetPosSimple(__int64 a1, float a2, float a3)
	{
		__int64 * ptr = (__int64*)(a1 + 56);
		float * x = (float*)((*ptr) + 252);
		float * y = (float*)((*ptr) + 256);

		*x = a2;
		*y = a3;
	}
};

class ccUiTaskBase
{
public:
	static __int64 __fastcall SetEnableTask(__int64 a1, unsigned int a2)
	{
		return reinterpret_cast<__int64(__fastcall*)(__int64 a1, unsigned int a2)>(moduleBase + 0xAD04B0)(a1, a2);
	}
};

class ccSceneReliveStorySelect
{
public:
	static __int64 DoWindowMalloc(__int64 a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(moduleBase + 0x68C57C)(a1);
	}

	static __int64 CreateWindowFlash(__int64 a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(moduleBase + 0x68DB78)(a1);
	}
};

class ccUiWindow4
{
public:
	static __int64 Create(__int64 a1) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(moduleBase + 0x65929C)(a1); }
};

class ccUiWindow1
{
public:
	static __int64 AllocateMessageWindow(__int64 a1, const char* a2) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1, const char* a2)>(moduleBase + 0x6594CC)(a1, a2); }
	static __int64 SetTitleText(__int64 a1, const char* a2, int a3) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1, const char* a2, int a3)>(moduleBase + 0x6598C0)(a1, a2, a3); }
	static __int64 SetMenuTextWordWrap(__int64 a1) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(moduleBase + 0x659848)(a1); }
	static __int64 SetMenuText(__int64 a1, const char* a2, int a3) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1, const char* a2, int a3)>(moduleBase + 0x6596AC)(a1, a2, a3); }
	static __int64 SetMenuTextColor(__int64 a1, int a2) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1, int a2)>(moduleBase + 0x6597D0)(a1, a2); }
	static void Open(__int64 a1) { return reinterpret_cast<void(__fastcall*)(__int64 a1)>(moduleBase + 0x659690)(a1); }
	static void Close(__int64 a1) { return reinterpret_cast<void(__fastcall*)(__int64 a1)>(moduleBase + 0x659488)(a1); }
	static __int64 SetWindowSize(__int64 a1, int a2, int a3) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1, int a2, int a3)>(moduleBase + 0x6599E4)(a1, a2, a3); }
};

class ccUiFont
{
public:
	static __int64 __fastcall CcUiFont(ccUiFont* a1, unsigned int a2) {return reinterpret_cast<__int64(__fastcall*)(ccUiFont* a1, unsigned int a2)>(moduleBase + 0xAF8640)(a1, a2); }
	static __int64 __fastcall Initialize(ccUiFont* a1, const char* a2, const char* a3) { return reinterpret_cast<__int64(__fastcall*)(ccUiFont* a1, const char* a2, const char* a3)>(moduleBase + 0xAF8A10)(a1, a2, a3); }
	static void __fastcall SetScale(ccUiFont* a1, float a2, float a3) { reinterpret_cast<void(__fastcall*)(ccUiFont* a1, float a2, float a3)>(moduleBase + 0xAF90B0)(a1, a2, a3); }
	static __int64 __fastcall SetPivot(ccUiFont* a1, int a2) { return reinterpret_cast<__int64(__fastcall*)(ccUiFont* a1, int a2)>(moduleBase + 0xAF92A0)(a1, a2); }
	static __int64 __fastcall SetColor(ccUiFont* a1, int a2, int a3) { return reinterpret_cast<__int64(__fastcall*)(ccUiFont* a1, int a2, int a3)>(moduleBase + 0xAF9350)(a1, a2, a3); }
	static __int64 __fastcall SetPos(ccUiFont* a1, float a2, float a3) { return reinterpret_cast<__int64(__fastcall*)(ccUiFont* a1, float a2, float a3)>(moduleBase + 0xAF8E50)(a1, a2, a3); }
	static __int64 __fastcall SetRubyEnable(ccUiFont* a1, int a2) { return reinterpret_cast<__int64(__fastcall*)(ccUiFont* a1, int a2)>(moduleBase + 0xAFA4F0)(a1, a2); }
	static __int64 __fastcall SetText(ccUiFont* a1, const char* a2) { return reinterpret_cast<__int64(__fastcall*)(ccUiFont* a1, const char* a2)>(moduleBase + 0xAFAC90)(a1, a2); }
	static __int64 __fastcall DrawInternal(ccUiFont* a1) { return reinterpret_cast<__int64(__fastcall*)(ccUiFont* a1)>(moduleBase + 0xAFB240)(a1); }
	static void __fastcall CtrlInternal(ccUiFont* a1) { reinterpret_cast<void(__fastcall*)(ccUiFont* a1)>(moduleBase + 0xAFB3C0)(a1); }
};

class ccXfbinDocManagerForUi
{
public:
	static ccXfbinDocManagerForUi * GetInstance() { return *(ccXfbinDocManagerForUi**)((__int64*)(moduleBase + 0x1416BDA70 - 0x140000C00)); }
	static __int64 __fastcall IsLoaded(ccXfbinDocManagerForUi * a1, const char* a2) { return reinterpret_cast<__int64(__fastcall*)(ccXfbinDocManagerForUi * a1, const char* a2)>(moduleBase + 0xADA220)(a1, a2); }
};

class nuccSys
{
public:
	static int __fastcall BeginScene(__int64 _nuccSys, __int64 a2)
	{
		return reinterpret_cast<int(__fastcall*)(__int64 nuccSys, __int64 a2)>(moduleBase + 0xA089B0)(_nuccSys, a2);
	}

	static __int64 __fastcall EndScene()
	{
		return reinterpret_cast<__int64(__fastcall*)()>(moduleBase + 0xA090E0)();
	}

	static __int64 nummSysBeginScene()
	{
		return reinterpret_cast<__int64(__fastcall*)()>(moduleBase + 0x9E1470)();
	}

	static __int64 nummSysSetClearColor(float a1, float a2, float a3, float a4)
	{
		return reinterpret_cast<__int64(__fastcall*)(float a1, float a2, float a3, float a4)>(moduleBase + 0x9E16E0)(a1, a2, a3, a4);
	}

	static __int64 nummSysClear(unsigned int a1)
	{
		return reinterpret_cast<__int64(__fastcall*)(unsigned int a1)>(moduleBase + 0x9E1480)(a1);
	}

	static void nummSysEndScene()
	{
		reinterpret_cast<void(__fastcall*)()>(moduleBase + 0x9E1560)();
	}
};

class ccUiWindowNative
{
public:
	static ccUiWindowNative * Instantiate()
	{
		__int64 mem = Game::operator_new(0x230, "", 0x3B0);
		ccUiWindowNative* wnd = (ccUiWindowNative*)mem;
		ccUiWindowNative::ccUiWindow(wnd);
		ccUiWindowNative::Initialize(wnd);

		return wnd;
	}

	static ccUiWindowNative * Instantiate(const char* a2, int a3, int a4, const char* a5, int a6, int a7)
	{
		__int64 mem = Game::operator_new(0x230, "", 0x4CE);
		ccUiWindowNative* wnd = (ccUiWindowNative*)mem;
		ccUiWindowNative::ccUiWindow(wnd, a2, a3, a4, a5, a6, a7);
		ccUiWindowNative::Initialize(wnd);

		return wnd;
	}

	static ccUiWindowNative * ccUiWindow(ccUiWindowNative* wnd)
	{
		return reinterpret_cast<ccUiWindowNative*(__fastcall*)(ccUiWindowNative* wnd)>(moduleBase + 0xAF52F0)(wnd);
	}

	static ccUiWindowNative * ccUiWindow(ccUiWindowNative* wnd, const char *a2, int a3, int a4, const char *a5, int a6, int a7)
	{
		return reinterpret_cast<ccUiWindowNative*(__fastcall*)(ccUiWindowNative* wnd, const char *a2, int a3, int a4, const char *a5, int a6, int a7)>(moduleBase + 0xAF5190)(wnd, a2, a3, a4, a5, a6, a7);
	}

	static ccUiWindowNative* Initialize(ccUiWindowNative* wnd)
	{
		return reinterpret_cast<ccUiWindowNative*(__fastcall*)(ccUiWindowNative* wnd)>(moduleBase + 0xAF55D0)(wnd);
	}

	static __int64 Ctrl(ccUiWindowNative* wnd)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccUiWindowNative* wnd)>(moduleBase + 0xAF5EA0)(wnd);
	}

	static __int64 Draw(ccUiWindowNative* wnd)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccUiWindowNative* wnd)>(moduleBase + 0xAF5FF0)(wnd);
	}

	static void SetPos(ccUiWindowNative* wnd, float a2, float a3, float a4)
	{
		reinterpret_cast<void(__fastcall*)(ccUiWindowNative* wnd, float a2, float a3, float a4)>(moduleBase + 0xAF6080)(wnd, a2, a3, a4);
	}

	static void SetSize(ccUiWindowNative* wnd, float a2, float a3)
	{
		reinterpret_cast<void(__fastcall*)(ccUiWindowNative* wnd, float a2, float a3)>(moduleBase + 0xAF6110)(wnd, a2, a3);
	}

	static __int64 OpenMessageWindow(ccUiWindowNative* wnd, const char* a2, int a3)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccUiWindowNative* wnd, const char* a2, int a3)>(moduleBase + 0xAEFD60)(wnd, a2, a3);
	}

	static void SetModeUnderstand(ccUiWindowNative* wnd)
	{
		reinterpret_cast<void(__fastcall*)(ccUiWindowNative* wnd)>(moduleBase + 0xAEFD00)(wnd);
	}
};

class ccUiObjectContainer
{
public:
	static __int64 __fastcall Add(ccUiObjectContainer* a1, __int64 a2)
	{
		return reinterpret_cast<__int64(__fastcall*)(ccUiObjectContainer* a1, __int64 a2)>(moduleBase + 0xB08970)(a1, a2);
	}
};

// Template to call internal functions
//__int64 a = reinterpret_cast<int32_t(__thiscall*)(uintptr_t a, int b)>(0x500)(5, 5);