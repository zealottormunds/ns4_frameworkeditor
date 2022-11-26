#pragma once
extern __int64 moduleBase;
extern __int64 g_editorPtr;
extern __int64 moduleLength;
extern __int64 hwndGlobal;

// Editor
extern __int64 hookFunct;

typedef void(__stdcall *HookFunct)(void* toHook, void* ourFunct, int len);

extern char testVar[36];