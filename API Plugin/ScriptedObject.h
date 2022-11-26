#pragma once
#include "Component.h"
#include <string>
#include <vector>

#include "LuaMachine.h"

namespace Editor
{
	class ScriptedObject : public Component
	{
	public:
		std::string script = "";
		lua_State * l;
		void Start(__int64 obj) override
		{
			componentType = Component::Types::ScriptedObject;
			editorObject = obj;
			std::cout << "AddComponent<ScriptedObject>() to " << editorObject << std::endl;

			if (!LuaMachine::isInit)
			{
				LuaMachine::InitializeLua();
			}

			l = LuaMachine::l;
		}

		void Update() override
		{
			if (!l) return;

			luaL_dostring(l, script.c_str());
		}
	};
}