#ifndef PLUGIN_H
#define PLUGIN_H
#pragma once

#include <vector>
#include "EditorBase.h"

class Main
{
public:
	static __int64 moduleBase;
	static std::vector<__int64> API_FunctionList;
	static bool isDebug;
	static Editor::EditorBase editor;
	static bool initGUI;
};

extern "C"
{
	__declspec(dllexport) void __stdcall InitializePlugin(__int64 a, std::vector<__int64> b);
	__declspec(dllexport) void __stdcall InitializeCommands(__int64 a, __int64 addCommandFunctionAddress);
	__declspec(dllexport) void __stdcall InitializeHooks(__int64 a, __int64 hookFunctionAddress);
	__declspec(dllexport) void __stdcall InitializeLuaCommands(__int64 a, __int64 addCommandFunction);
	__declspec(dllexport) void __stdcall Unload();
	__declspec(dllexport) void __stdcall PostBoot();

	__declspec(dllexport) std::vector<std::string> * __stdcall ExtensionList();
	__declspec(dllexport) bool __stdcall ParseApiFiles(__int64 a, std::string filePath, std::vector<char> fileBytes);
	__declspec(dllexport) void __stdcall GameLoop(__int64 a);

	__declspec(dllexport) void __stdcall PreRender();
	__declspec(dllexport) void __stdcall PostRender();
	__declspec(dllexport) void __stdcall OnGUI(bool frameworkShow, __int64 hwnd, __int64 imguiContext);

	__int64 __fastcall testhook(const char* a1);
}

#endif