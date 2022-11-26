#pragma once

extern "C"
{
	#include "Lua/include/lua.h"
	#include "Lua/include/lauxlib.h"
	#include "Lua/include/lualib.h"
}

#include <iostream>
#include "FileParser.h"
#include "EditorGUI.h"

class LuaMachine
{
public:
	static bool isInit;
	static lua_State * l;

	static int DistanceToPlayer(lua_State * state);
	static int LoadLevelByName(lua_State * state);
	static int SetPlayerPosition(lua_State * state);

	static int WaitFrames(lua_State * state);
	static int SetCameraControl(lua_State * state);
	static int SetCameraPosition(lua_State * state);
	static int SetCameraLook(lua_State * state);
	static int FadeIn(lua_State * state);
	static int FadeOut(lua_State * state);
	static int FrameCounter(lua_State * state);
	static int SetColorFilterState(lua_State * state);
	static int SetColorFilterColor(lua_State * state);
	static int SetFogColor(lua_State * state);
	static int SetFogParams(lua_State * state);

	static int ClearStage(lua_State * state);
	static int SetObjectPosition(lua_State * state);
	static int SetObjectScale(lua_State * state);

	static void InitializeLua()
	{
		if (isInit == false)
		{
			isInit = true;
			l = luaL_newstate();

			if (l == NULL) std::cout << "Error initializing lua" << std::endl;
			else std::cout << "Initialized lua" << std::endl;

			luaL_openlibs(l);

			// Register functions
			lua_pushcfunction(l, DistanceToPlayer);
			lua_setglobal(l, "DistanceToPlayer");

			lua_pushcfunction(l, LoadLevelByName);
			lua_setglobal(l, "LoadLevelByName");

			lua_pushcfunction(l, SetPlayerPosition);
			lua_setglobal(l, "SetPlayerPosition");

			lua_pushcfunction(l, WaitFrames);
			lua_setglobal(l, "WaitFrames");

			lua_pushcfunction(l, SetCameraControl);
			lua_setglobal(l, "SetCameraControl");

			lua_pushcfunction(l, SetCameraLook);
			lua_setglobal(l, "SetCameraLook");

			lua_pushcfunction(l, FadeIn);
			lua_setglobal(l, "FadeIn");

			lua_pushcfunction(l, FadeOut);
			lua_setglobal(l, "FadeOut");

			lua_pushcfunction(l, FrameCounter);
			lua_setglobal(l, "FrameCounter");

			lua_pushcfunction(l, SetColorFilterState);
			lua_setglobal(l, "SetColorFilterState");

			lua_pushcfunction(l, SetColorFilterColor);
			lua_setglobal(l, "SetColorFilterColor");

			lua_pushcfunction(l, SetFogColor);
			lua_setglobal(l, "SetFogColor");

			lua_pushcfunction(l, SetFogParams);
			lua_setglobal(l, "SetFogParams");

			lua_pushcfunction(l, SetObjectPosition);
			lua_setglobal(l, "SetObjectPosition");

			lua_pushcfunction(l, SetObjectScale);
			lua_setglobal(l, "SetObjectScale");
		}
	}
};