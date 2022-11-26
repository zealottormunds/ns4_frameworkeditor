#pragma once
#include "BaseGUI.h"
#include "EditorBase.h"
#include "ImGUI/imgui_stdlib.h"

namespace Editor
{
	class ComponentGUI : public BaseGUI
	{
	public:
		EditorObject * eObj;
		bool show = true;
		int selected = -1;

		ComponentGUI(EditorObject * ptr)
		{
			eObj = ptr;
		}

		std::string GetComponentName(Component * c)
		{
			switch (c->componentType)
			{
			case Component::Types::Animation:
				return "Animation";
			case Component::Types::ScriptedObject:
				return "ScriptedObject";
			}

			return "null";
		}

		void Update() override
		{
			ImGui::Begin("GameObject Properties", &show);

			ImGui::InputText("ID", &(eObj->name));

			if (ImGui::ListBoxHeader("Object Components"))
			{
				for (int x = 0; x < eObj->components.size(); x++)
				{
					Component * c = eObj->components[x];
					std::string compName = GetComponentName(c);

					if (ImGui::Selectable(compName.c_str(), selected == x))
					{
						readScript = false;
						selected = x;
					}
				}
				ImGui::ListBoxFooter();
			}

			if (ImGui::Button("Add Script"))
			{
				bool hasScript = false;
				for (int x = 0; x < eObj->components.size(); x++)
				{
					if (eObj->components[x]->componentType == Component::Types::ScriptedObject)
					{
						hasScript = true;
						x = eObj->components.size();
					}
				}

				if (hasScript == false)
				{
					ScriptedObject * s = new ScriptedObject();
					eObj->AddComponent(s);
				}
				else
				{
					std::cout << "Object already has ScriptedObject" << std::endl;
				}
			}
			if (ImGui::Button("Add EditorAnimation"))
			{
				bool hasAnm = false;
				for (int x = 0; x < eObj->components.size(); x++)
				{
					if (eObj->components[x]->componentType == Component::Types::Animation)
					{
						hasAnm = true;
						x = eObj->components.size();
					}
				}

				if (hasAnm == false)
				{
					Animation * a = new Animation();
					eObj->AddComponent(a);
				}
				else
				{
					std::cout << "Object already has EditorAnimation" << std::endl;
				}
			}

			// Spawn the proper window
			if (selected != -1)
			{
				switch (eObj->components[selected]->componentType)
				{
				case Component::Types::Animation:
					AnimationEditor(eObj->components[selected]);
				case Component::Types::ScriptedObject:
					ScriptEditor(eObj->components[selected]);
				}
			}

			ImGui::End();
		}

		void AnimationEditor(Component * c)
		{
			ImGui::Text("[Not implemented]");
		}

		std::string tempScript = "";
		bool readScript = false;
		void ScriptEditor(Component * c)
		{
			ScriptedObject * s = (ScriptedObject*)c;

			if (readScript == false)
			{
				tempScript = s->script;
				readScript = true;
			}

			ImGui::InputTextMultiline("Script", &tempScript, ImVec2(300, 200));
			if (ImGui::Button("Save Script"))
			{
				s->script = tempScript;
			}
			if (ImGui::Button("Reload Script"))
			{
				readScript = false;
			}
		}
	};
}