#pragma once
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGUI/imgui_impl_win32.h"

namespace Editor
{
	class BaseGUI
	{
	public:
		virtual void Update()
		{

		}

		void Close()
		{
			delete this;
		}
	};
}