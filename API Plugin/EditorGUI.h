#pragma once
#include <string>
#include "FileParser.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGUI/imgui_impl_win32.h"
#include "Utilities.h"
#include "Vector3.h"

class EditorGUI
{
public:
	static bool WindowList[100];
	static float editor_cameraWindowPos[3];
	static float editor_cameraWindowLook[3];
	static bool editor_cameraWindowEnableCam;
	static int editor_cameraWindowMode;

	static Vector3 editor_renderEditorColor;
	static Vector3 editor_renderEditorParams;

	static ColorFilterDirectionalSettings editor_colorFilterDir;

	static __int64 frameCounter;

	static void InitGUI();
	static void LoopGUI(bool Show, __int64 hwnd);
	static __int64 LoadHelperEditor(const char* path, bool isGizmo = false);
	static __int64 IsLoaded(const char* path);
	static void DeleteObject(int index);

	static void CreateGizmo();

	static void ClearStage(bool deleteGlobals);
	static void SaveStage();
	static void LoadStage(std::string path);
	static void LoadStage00(std::vector<BYTE> actual);
	static void LoadStage01(std::vector<BYTE> actual);
};