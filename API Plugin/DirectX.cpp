#include "DirectX.h"
#include <Shlwapi.h>

#include <wrl.h>
#include <d3d11.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <dxgi.h>
#include <dxgiformat.h>
#include <iostream>

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGUI/imgui_impl_win32.h"

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "D3Dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")

#include "EditorGUI.h"
#include "Common.h"

// Main D3D11 Objects
ID3D11DeviceContext *pContext = NULL;
ID3D11Device *pDevice = NULL;
ID3D11RenderTargetView *mainRenderTargetView;
static IDXGISwapChain*  pSwapChain = NULL;
HWND window = nullptr;
BOOL g_bInitialised = false;

__int64 DirectX::dxgiAddress = 0;
char DirectX::UnhookDxgi[19];

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (pDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = NULL; }

			pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);

			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

__int64 test = 0;
__int64 DirectX::theWindow = 0;

__int64 DirectX::DxgiHook(__int64 ppSwapChain, int a2, int a3)
{
	// 0x1FE0
	//std::cout << "Present..." << std::endl;

	if (g_bInitialised == false)
	{
		g_bInitialised = true;

		// Do all the garbage:
		pSwapChain = (IDXGISwapChain*)ppSwapChain;

		// change vtable present to my funct:
		HookVtable((__int64)pSwapChain);

		// unhook
		DWORD dwOld = 0;
		VirtualProtect((void*)(dxgiAddress + 0x1FE0), 19, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(dxgiAddress + 0x1FE0), &UnhookDxgi[0], 19);
		VirtualProtect((void*)(dxgiAddress + 0x1FE0), 19, dwOld, &dwOld);

		std::cout << "SwapChain: " << std::hex << (__int64)pSwapChain << std::endl;

		pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)(&pDevice));
		std::cout << "Device: " << std::hex << (__int64)pDevice << std::endl;

		pDevice->GetImmediateContext((&pContext));
		std::cout << "Context: " << std::hex << (__int64)pContext << std::endl;

		ID3D11Texture2D* pBackBuffer;
		pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
		pBackBuffer->Release();

		// IMGUI SPECIFIC
		DXGI_SWAP_CHAIN_DESC desc;
		pSwapChain->GetDesc(&desc);
		theWindow = (__int64)(desc.OutputWindow);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init((HWND)theWindow);
		ImGui_ImplDX11_Init(pDevice, pContext);

		test = GetWindowLongPtr((HWND)theWindow, GWLP_WNDPROC);

		bool show_demo_window = true;
		bool show_another_window = true;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		EditorGUI::InitGUI();
	}

	/*ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
	pBackBuffer->Release();*/

	if (GetAsyncKeyState(VK_F10) & 0x01)
	{
		EditorGUI::Show = !EditorGUI::Show;

		if (EditorGUI::Show == true)
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.WantCaptureMouse = true;
			SetWindowLongPtr((HWND)theWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
		}
		else
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.WantCaptureMouse = false;
			SetWindowLongPtr((HWND)theWindow, GWLP_WNDPROC, (LONG_PTR)test);
		}
	}

	ShowCursor(true);

	MSG msg;
	while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	EditorGUI::LoopGUI();

	typedef __int64(__fastcall * fc)(__int64 ppSwapChain, int a2, int a3);
	fc f = (fc)(dxgiAddress + 0x1FE0);
	__int64 result = f(ppSwapChain, a2, a3);

	ImGui_ImplDX11_InvalidateDeviceObjects();
	ImGui_ImplDX11_CreateDeviceObjects();

	return result;
}

void DirectX::UnhookVtable(__int64 ppSwapChain)
{
	__int64 present = *((__int64*)pSwapChain) + 8 * 8;

	DWORD dwOld = 0;
	VirtualProtect((void*)(present), 8, PAGE_EXECUTE_READWRITE, &dwOld);
	*(__int64*)(present) = (__int64)(dxgiAddress + 0x1FE0);
	VirtualProtect((void*)(present), 8, dwOld, &dwOld);
}

void DirectX::HookVtable(__int64 ppSwapChain)
{
	__int64 present = *((__int64*)pSwapChain) + 8 * 8;

	DWORD dwOld = 0;
	VirtualProtect((void*)(present), 8, PAGE_EXECUTE_READWRITE, &dwOld);
	*(__int64*)(present) = (__int64)(DirectX::DxgiHook);
	VirtualProtect((void*)(present), 8, dwOld, &dwOld);
}

__int64 DirectX::ApplyGraphicSettings()
{
	char oldCode[15] = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x6C, 0x24, 0x10, 0x48, 0x89, 0x74, 0x24, 0x18 };

	// put old code back
	DWORD dwOld = 0;
	VirtualProtect((void*)(moduleBase + 0x52F574), 15, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(moduleBase + 0x52F574), oldCode, 15);
	VirtualProtect((void*)(moduleBase + 0x52F574), 15, dwOld, &dwOld);

	UnhookVtable((__int64)pSwapChain);

	std::cout << "Changed graphic settings" << std::endl;
	typedef __int64(__fastcall * funct)();
	funct fc = (funct)(moduleBase + 0x52F574);
	__int64 ret = fc();

	HookVtable((__int64)pSwapChain);

	// Hook again
	typedef void(__stdcall *HookFunct)(void* toHook, void* ourFunct, int len);
	HookFunct Hook = (HookFunct)hookFunct;
	Hook((void*)(moduleBase + 0x52F574), DirectX::ApplyGraphicSettings, 15);

	return ret;
}