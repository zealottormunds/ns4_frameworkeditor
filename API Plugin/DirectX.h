#pragma once

class DirectX
{
public:
	static __int64 dxgiAddress;
	static __int64 dxtPtr;
	static char UnhookDxgi[19];
	static __int64 DxgiHook(__int64 ppSwapChain, int a2, int a3);
	static __int64 theWindow;

	static void UnhookVtable(__int64 ppSwapChain);
	static void HookVtable(__int64 ppSwapChain);
	static __int64 ApplyGraphicSettings();
};