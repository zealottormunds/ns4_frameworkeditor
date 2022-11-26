#pragma once
#include "Utilities.h"
#include "nuccAnm.h"
#include "nuccClump.h"

class ccEntryModelTest
{
public:
	//ccEntryModelTestFunctions * Functions;
	virtual __int64 __fastcall Function_00() = 0;
	virtual __int64 __fastcall Function_08() = 0;
	virtual __int64 __fastcall Function_16() = 0;
	virtual __int64 __fastcall Function_24() = 0;
	virtual __int64 __fastcall Function_32() = 0;
	virtual __int64 __fastcall Function_40() = 0;
	virtual __int64 __fastcall Function_48() = 0;
	virtual __int64 __fastcall Function_56() = 0;
	virtual __int64 __fastcall Function_64(__int64 obj) = 0;
	virtual __int64 __fastcall Function_72() = 0;
	virtual __int64 __fastcall Function_80() = 0;
	virtual __int64 __fastcall Function_88(...) = 0;
	virtual __int64 __fastcall Function_96() = 0;
	virtual __int64 __fastcall Function_104() = 0;
	virtual __int64 __fastcall Function_112() = 0;
	virtual __int64 __fastcall Function_120() = 0;

	static __int64 InitObject(__int64 obj, __int64 objectList)
	{
		typedef __int64(__fastcall * funct)(__int64 obj, __int64 objectList);
		funct fc = (funct)(moduleBase + 0x44C160);
		return fc(obj, objectList);
	}

	static __int64 SetModelGfsa(__int64 obj)
	{
		typedef __int64(__fastcall * funct)(__int64 obj);
		funct fc = (funct)(moduleBase + 0x44C1C4);
		return fc(obj);
	}

	static __int64 SetModelCustom(__int64 obj, const char * path, const char * mesh, const char * anmpath = 0, const char * anmname = 0)
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

		const char * meshPath = path;
		const char * meshBod = mesh;

		result = nuccXfbinDocManager::GetXfbinLoadState(meshPath);

		if (result == 2)
		{
			std::cout << "Xfbin loaded correctly" << std::endl;
			
			if (result == 2)
			{
				v3 = nuccXfbinDocManager::Search(meshPath);

				if (v3)
				{
					std::cout << "Mesh found" << std::endl;

					v5 = ccStageGimmickAnm::GetChunkClump(0, path, mesh);

					if (v5 > 0)
					{
						v7 = Game::operator_new(0x340, "bod1", 0x56);

						if (v7)
						{
							NuccClump::nuccClump(v7, v5, 0, 1, 0);
							std::cout << "NuccClump : " << std::hex << std::uppercase << v7 << std::endl;
						}

						*((__int64*)(obj + 0x98)) = v7; // 0x98 = clump

						bool hasAnm = anmpath && anmname;

						if (v7) // if no anm
						{
							*((int*)(v7 + 824)) = 0;
						}

						return obj;


						/*if (v7) ???????????????
						{
							*((int*)(v7 + 824)) = 0;
						}*/


						//anm->Function_96(v8, v6);
						//std::cout << "Function 96" << std::endl;

						std::cout << "Finished model" << std::endl;

						/*result = obj;

						std::cout << "obj + 0x98 = v7 = " << std::hex << std::uppercase << *((__int64*)(obj + 0x98)) << std::endl;

						v8 = Game::operator_new(0x1C0, "bod3", 0x5C);
						
						if (v8)
						{
							std::cout << "Alloc anm in v8 = " << std::hex << std::uppercase << v8 << std::endl;

							v8 = NuccAnm::nuccAnm(v8);
							std::cout << "NuccAnm::nuccAnm(v8)" << std::endl;
						}
						else
						{
							std::cout << "Error operator_new bod3" << std::endl;
						}

						v9 = *((__int64*)(obj + 0x98));
						std::cout << "v9 = obj + 0x98 = " << std::hex << std::uppercase << v9 << std::endl;

						*((__int64*)(obj + 0xA0)) = v8;
						std::cout << "obj + 0xA0 = v8 = " << std::hex << std::uppercase << *((__int64*)(obj + 0xA0)) << std::endl;

						NuccAnm::ApplyClump(v8, v9);
						std::cout << "NuccAnm::ApplyClump(v8, v9)" << std::endl;

						*(int *)(*(__int64 *)(obj + 0xA0) + 68i64) = 0; // nopping a function???
						std::cout << "nopped funct" << std::endl;

						NuccAnm * anm = (NuccAnm*)(v8);

						anm->Function_96(v8, v6);
						std::cout << "Function 96" << std::endl;



						__int64 gameInfo_1416663C8 = *((__int64*)(moduleBase + 0x1416663C8 - 0x140000C00));
						gameInfo_1416663C8 = gameInfo_1416663C8 + 0x942;
						unsigned __int8 gInfoOperator = *((__int8*)(gameInfo_1416663C8));
						std::cout << "gameInfo math = " << std::hex << std::uppercase << gInfoOperator << std::endl;

						anm->Function_48(v8, 0xBB8 / gInfoOperator);
						std::cout << "Function 48" << std::endl;



						v10 = unnamed::modelCreateConst_sub_140A04E80();
						std::cout << "v10 = modelCreateConst_sub_140A04E80();" << std::endl;

						result = 0xB60B60B7 * v10;
						std::cout << "result = 0xB60B60B7 * v10;" << std::endl;

						float var = (float)v10;
						var = var / 360.0;
						var = var * 3.1415927;
						var = var * 0.0055555557;
						*((float*)(obj + 0x220)) = var;
						std::cout << "Pi math" << std::endl;*/

						result = obj;
					}
					else
					{
						std::cout << "Chunk of mesh not found" << std::endl;
						return 0;
					}
				}
				else
				{
					std::cout << "Mesh not found" << std::endl;
					return 0;
				}
			}
			else
			{
				std::cout << "Mesh not loaded" << std::endl;
				return 0;
			}
		}
		else
		{
			std::cout << "File not loaded" << std::endl;
			return 0;
		}

		return result;
	}

	static __int64 SetBehaviorCustom(__int64 obj)
	{
		ccTaskBase::EntryTaskWithAllo4(obj, "ccCpuGroupLiteBase::Ctrl", 0x15, 0xFFFDFFFD, obj, (moduleBase + 0x2FD9B4)); // ccAdvBaseAnm::Ctrl
		ccTaskBase::EntryTaskWithAllo4(obj, "ccCpuGroupLiteBase::Draw", 0x15, 0xFFFDFFFD, obj, (moduleBase + 0x3285C0)); // ccUi3DCharacterModel::Draw
	}

	static __int64 __fastcall AssignMatrix(__int64 obj, __int64 matrix)
	{
		typedef __int64(__fastcall * funct)(__int64 obj, __int64 matrix);
		funct fc = (funct)(moduleBase + 0x44B984);
		return fc(obj, matrix);
	}

	static void __fastcall SetVector3(__int64 obj, float x, float z, float y)
	{
		typedef void(__fastcall * funct)(__int64 obj, float x, float z, float y);
		funct fc = (funct)(moduleBase + 0x44B978);
		return fc(obj, x, z, y);
	}

	static void SetPosition(__int64 obj, float x, float y, float z)
	{
		float * xpos = (float*)(obj + 72);
		float * ypos = (float*)(obj + 88);
		float * zpos = (float*)(obj + 104);

		*xpos = x;
		*ypos = y;
		*zpos = z;
	}

	static Vector3 GetPosition(__int64 obj)
	{
		float * xpos = (float*)(obj + 72);
		float * ypos = (float*)(obj + 88);
		float * zpos = (float*)(obj + 104);

		return Vector3(*xpos, *ypos, *zpos);
	}

	static void SetScale(__int64 obj, float x, float y, float z)
	{
		float * xscale = (float*)(obj + 60);
		float * yscale = (float*)(obj + 80);
		float * zscale = (float*)(obj + 100);

		*xscale = x;
		*yscale = y;
		*zscale = z;
	}

	static Vector3 GetScale(__int64 obj)
	{
		float * xscale = (float*)(obj + 60);
		float * yscale = (float*)(obj + 80);
		float * zscale = (float*)(obj + 100);

		return Vector3(*xscale, *yscale, *zscale);
	}
};