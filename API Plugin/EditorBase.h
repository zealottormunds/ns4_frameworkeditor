#pragma once
#include <vector>
#include "Common.h"
#include "Commands.h"

#include "Component.h"
#include "Animation.h"
#include "DebugMsg.h"
#include "ScriptedObject.h"

#include <cstdlib>
#include <ctime>

#include "ccStageClump.h"
#include "ccStageAnm.h"

namespace Editor
{
	class EditorObject
	{
	public:
		std::string name = "new EditorObject";

		std::string path = "";
		std::string mesh = "";
		ccStageClump * clump = nullptr;
		ccStageAnm * anmclump = nullptr;
		Vector3 position;
		Vector3 scale;
		bool global = false;

		std::vector<Component*> components;

		EditorObject(std::string n, ccStageClump * objPtr, const char * path_, const char* mesh_)
		{
			name = n + "_" + std::to_string((__int64)objPtr);
			clump = objPtr;
			path = path_;
			mesh = mesh_;

			//obj = objPtr;
			//clump = *((__int64*)(obj + 152));
		}

		Component * AddComponent(Component * c)
		{
			components.push_back(c);
			
			c->Start((__int64)this);

			return c;
		}

		Component * RemoveComponent(Component * c)
		{
			int index = GetComponentIndex(c);

			if (index != -1)
			{
				c->OnRemove();
				components[index] = 0;
			}
			else
			{
				std::cout << "Could not remove component at " << std::hex << std::uppercase << c << std::endl;
			}

			return c;
		}

		Component * GetComponent(int index)
		{
			if (index >= components.size()) return 0;
			
			return components[index];
		}

		std::vector<Component*> GetComponentsOfType(Component::Types type)
		{
			std::vector<Component*> foundComponents;

			int compCount = components.size();
			for (int x = 0; x < compCount; x++)
			{
				Component * a = components[x];

				if (a->componentType == type)
				{
					foundComponents.push_back(a);
				}
			}

			return foundComponents;
		}

		int GetComponentIndex(Component * c)
		{
			int compCount = components.size();
			int ret = -1;

			for (int x = 0; x < compCount; x++)
			{
				Component * a = components[x];

				if ((__int64)a == (__int64)c)
				{
					ret = x;
					x = compCount;
				}
			}

			return ret;
		}

		void Start()
		{

		}

		void Update()
		{
			int compCount = components.size();
			for (int x = 0; x < compCount; x++)
			{
				Component * c = components[x];

				if (c)
				{
					c->UpdateComponent();
				}
				else
				{
					components.erase(components.begin() + x);
					x = x - 1;
					std::cout << "Found component pointing at 0, deleting..." << std::endl;
				}
			}

			if (anmclump != nullptr)
			{
				nuccAnimParams* anm = (nuccAnimParams*)anmclump;

				if (anm->GetPosition() != position)
				{
					anm->SetPosition(position);
				}

				if (anm->GetScale() != scale)
				{
					anm->SetScale(scale);
				}

				anm->Update();
			}

			//bool freeCam = GetFreeCamState();
		}
	};

	class EditorBase
	{
	public:
		bool isInit = false;
		bool editorOpen = false;
		int selectedObjectIndex = 0;
		__int64 selectedObjectAddress = 0;

		std::vector<EditorObject*> gizmoList;
		std::vector<EditorObject*> editorObjectList;

		static EditorBase* GetInstance()
		{
			return (EditorBase*)g_editorPtr;
		}

		void Start()
		{
			isInit = true;
		}

		void Update()
		{
			if (!isInit) return;

			// Update gizmos
			int gizmoCount = gizmoList.size();
			for (int x = 0; x < gizmoCount; x++)
			{
				EditorObject * eObj = gizmoList[x];
				eObj->Update();
			}

			// Update objects
			int editorObjectCount = editorObjectList.size();
			for (int x = 0; x < editorObjectCount; x++)
			{
				EditorObject * eObj = editorObjectList[x];

				if (eObj != nullptr)
				{
					eObj->Update();
				}
				else
				{
					editorObjectList.erase(editorObjectList.begin() + x);
				}
			}
		}

		void SelectObject(int index)
		{
			selectedObjectIndex = index;
		}
	};

	class EditorCommands
	{
	public:
	};
}