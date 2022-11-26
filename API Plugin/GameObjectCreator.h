#pragma once
#include "Utilities.h"
#include "EditorBase.h"

#include "ccStageClump.h"
#include "ccStageObjectList.h"

class GameObjectCreator
{
public:
	static ccStageClump* CreateStaticModel(ccStageObjectList* objectList, const char* path, const char * mesh, const char* anmpath = 0, const char* anmname = 0)
	{
		if (!objectList) return nullptr;

		ccStageClump * clump = ccStageObjectList::AddClump(objectList, path, mesh);
		return clump;
	}

	static ccStageClump* CreateStaticModel_Global(ccStageObjectList* objectList_, const char* path, const char * mesh, const char* anmpath = 0, const char* anmname = 0)
	{
		//Nucc::matrix44_MathGeo * v7 = new Nucc::matrix44_MathGeo();
		//Nucc::matrix44_MathGeo * v8 = new Nucc::matrix44_MathGeo();

		__int64 obj;
		__int64 objectList;
		__int64 v5_;
		__int64 v6;

		char v7[64];
		char v8[112];

		/*__int64 v7 = (__int64)malloc(200);
		__int64 v8 = (__int64)malloc(200);
		memset((void*)v7, 0, 200);
		memset((void*)v8, 0, 200);*/

		Vector3 * position = new Vector3(0, 0, 0);

		objectList = (__int64)objectList_;
		if (!objectList) return nullptr;

		std::cout << "equisde??" << std::endl;
 		Nucc::matrix44_MathGeo::Matrix44_MathGeo((Nucc::matrix44_MathGeo*)v7);
		Nucc::matrix44_MathGeo::identity();

		std::cout << "equisde 2" << std::endl;
		obj = Nucc::matrix44_MathGeo::SetTranslatePart((Nucc::matrix44_MathGeo*)v7);
		std::cout << "equisde 3" << std::endl;

		if (objectList)
		{
			obj = Game::operator_new(0x228, "", 0xBF7);
			obj = ccEntryModelTest::InitObject(obj, objectList);

			std::cout << "Init object" << std::endl;

			if (anmpath != 0) std::cout << "has anm" << std::endl;

			ccEntryModelTest * object = (ccEntryModelTest*)obj;
			__int64 isCorrect = ccEntryModelTest::SetModelCustom(obj, path, mesh, anmpath, anmname);
			std::cout << "SetModel" << std::endl;

			if (isCorrect == obj)
			{
				object->Function_88(obj);
				std::cout << "function 88" << std::endl;

				v6 = Nucc::matrix44_MathGeo::Matrix44_MathGeo((Nucc::matrix44_MathGeo*)v8, (Nucc::matrix44_MathGeo*)v7);
				std::cout << "function m44" << std::endl;
				__int64 anm = *(__int64*)(obj + 160);
				//Nucc::matrix44_MathGeo::SetTranslatePart((Nucc::matrix44_MathGeo*)anm, (__int64)position);

				ccEntryModelTest::AssignMatrix(obj, v6);
				std::cout << "assign matrix" << std::endl;

				ccEntryModelTest::SetVector3(obj, 123, 234, 345);
				std::cout << "set v3" << std::endl;

				ccGameObject::Init(objectList, obj);
				std::cout << "init" << std::endl;
			}
			else
			{
				std::cout << "Error creating model" << std::endl;
				return nullptr;
			}
		}
		else
		{
			std::cout << "Invalid object list" << std::endl;
		}

		__int64 clump = *((__int64*)(obj + 0x98));

		return (ccStageClump*)obj;
	}

	static Editor::EditorObject * CreateObjectWithMesh(ccStageObjectList* objList, const char * path, const char* mesh, bool hasAnm, bool isGizmo = false)
	{
		if (!objList)
		{
			std::cout << "Invalid Object List" << std::endl;
			return nullptr;
		}

		std::cout << "Attempting to create " << path << " :: " << mesh << std::endl;
		__int64 obj = 0;

		if (hasAnm)
		{
			obj = (__int64)(ccStageObjectList::AddAnm(objList, path, mesh));
		}
		else
		{
			obj = (__int64)(CreateStaticModel(objList, path, mesh));
		}

		if (!obj)
		{
			std::cout << "Error creating object" << std::endl;
			return nullptr;
		}

		std::cout << "Created" << std::endl;
		Editor::EditorObject * eObj = new Editor::EditorObject("new EditorObject", (ccStageClump*)obj, path, mesh);
		eObj->name = mesh;

		Editor::EditorBase * e = (Editor::EditorBase*)g_editorPtr;
		if(isGizmo == false) e->editorObjectList.push_back(eObj);
		else e->gizmoList.push_back(eObj);
		eObj->Start();

		return eObj;
	}

	static Editor::Animation * AddAnimator(Editor::EditorObject * eObj)
	{
		bool debugMsg = false;

		Editor::Animation * comp = new Editor::Animation();
		eObj->AddComponent(comp);

		if (debugMsg) std::cout << "Anim init" << std::endl;

		comp->lerpSpeed = 0;
	}

	static Editor::Animation * SetAnimatorPrefab(Editor::EditorObject * eObj, Editor::Animation * comp, std::string anm)
	{
		bool debugMsg = false;

		if (anm == "random")
		{
			srand((unsigned int)time(NULL));
			float a = 5.0;
			float b[8];

			for (int x = 0; x < 7; x++)
			{
				b[x] = (float(rand()) / float((RAND_MAX)) * a);
			}

			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(100 * b[0], 100 * b[4], 0)));
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(100 * b[1], 100 * b[5], 0)));
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(100 * b[2], 100 * b[6], 0)));
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(100 * b[3], 100 * b[7], 0)));
		}
		else if (anm == "round")
		{
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(200, 200, 0)));
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(-200, 200, 0)));
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(-200, -200, 0)));
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(200, -200, 0)));
		}
		else if (anm == "randomround")
		{
			srand((unsigned int)time(NULL));
			float a = 5.0;
			float b = (float(rand()) / float((RAND_MAX)) * a);
			float c = (float(rand()) / float((RAND_MAX)) * a);
			float d = (float(rand()) / float((RAND_MAX)) * a);
			float e = (float(rand()) / float((RAND_MAX)) * a);
			float f = (float(rand()) / float((RAND_MAX)) * a);

			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(200 * b, 200 * c, 0)));
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(-200 * d, 200 * e, 0)));
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(-200 * f, -200 * e, 0)));
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(200 * d, -200 * c, 0)));

			comp->lerpSpeed *= b;
		}
		else if (anm == "none")
		{
			comp->lerpSpeed = 0;
		}
		else
		{
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(0, 0, 0)));
			comp->AddAnimationPoint(Editor::AnimationPoint(Vector3(0, 0, 0)));
			comp->lerpSpeed *= 1;
		}

		comp->SetClump(eObj->clump);

		if (comp->lerpSpeed != 0)
		{
			comp->SetAnimationNextFrame();
		}

		if (debugMsg) std::cout << "Set anim next frame" << std::endl;
	}

	static __int64 ccEventChara(__int64 objList, const char * charId, const char * xfbin, const char * meshname)
	{
		__int64 gameObject = Game::operator_new(0xD50, "", 0x26);

		if (gameObject)
		{
			gameObject = ccEventChara::CcEventChara(gameObject, objList);
			std::cout << "Alloc ccEventChara" << std::endl;
		}

		ccGameObject::Init(objList, gameObject);
		std::cout << "Init" << std::endl;

		ccEventChara::Create(objList, xfbin, meshname);
		std::cout << "Created ccEventChara" << std::endl;

		return gameObject;
	}
};