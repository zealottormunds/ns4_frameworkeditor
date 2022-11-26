#pragma once
#include <iostream>

namespace Editor
{
	class Component
	{
	public:
		__int64 editorObject;
		bool enabled = true;

		enum Types
		{
			Null,
			Animation,
			DebugMsg,
			ScriptedObject,
		};

		Types componentType = Null;

		virtual void Start(__int64 obj)
		{

		}

		virtual void UpdateComponent()
		{
			if (!enabled) return;
			Update();
		}

		virtual void Update()
		{

		}

		virtual void OnRemove()
		{

		}
	};
}