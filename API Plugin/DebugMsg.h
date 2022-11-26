#pragma once
#include <iostream>
#include "Component.h"

namespace Editor
{
	class DebugMsg : public Component
	{
	public:
		void Start(__int64 obj)
		{
			Component::Types componentType = Component::Types::DebugMsg;
			editorObject = obj;
			std::cout << "AddComponent<DebugMsg>() to " << editorObject << std::endl;
		}

		void Update()
		{
			std::cout << "Debug Message..." << std::endl;
		}
	};
}