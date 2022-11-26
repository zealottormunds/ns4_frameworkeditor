#include "LuaMachine.h"
#include "EditorBase.h"
#include "Utilities.h"

bool LuaMachine::isInit = false;
lua_State * LuaMachine::l;

using namespace Editor;

int LuaMachine::DistanceToPlayer(lua_State * l)
{
	const char* objName = luaL_checkstring(l, 1);
	std::string objStr = std::string(objName);

	EditorBase * e = EditorBase::GetInstance();
	int objIndex = -1;
	int objCount = e->editorObjectList.size();
	for (int x = 0; x < objCount; x++)
	{
		EditorObject* eObj = e->editorObjectList[x];
		std::string currentObj = eObj->name;

		if (currentObj == objStr)
		{
			objIndex = x;
			x = objCount;
		}
	}

	if (objIndex == -1) return 0; // if no object

	ccPlayerMain * pl = BattleUtils::ccGame_GetPlayerLeader(0);

	if (!pl) return 0; // if no player

	EditorObject* eObj = e->editorObjectList[objIndex];
	Vector3 objPos = eObj->position;
	Vector3 * plPos = (Vector3*)((__int64)(pl) + 0x70);

	float dist = Vector3::Distance(*plPos, objPos);
	lua_pushnumber(l, dist);

	return 1;
}

int LuaMachine::LoadLevelByName(lua_State * l)
{
	const char* path = luaL_checkstring(l, 1);

	if (FileParser::FileExists(path))
	{
		EditorGUI::LoadStage(path);
		lua_pushboolean(l, 1);
		return 1;
	}
	else
	{
		lua_pushboolean(l, 0);
		return 1;
	}
}

int LuaMachine::SetPlayerPosition(lua_State * l)
{
	Vector3 newPos = Vector3(luaL_checknumber(l, 1), luaL_checknumber(l, 2), luaL_checknumber(l, 3));

	ccPlayerMain * pl = BattleUtils::ccGame_GetPlayerLeader(0);

	if (pl)
	{
		Vector3* pospl = (Vector3*)((__int64)(pl) + 0x70);
		*pospl = newPos;
	}

	return 0;
}

int LuaMachine::WaitFrames(lua_State * state)
{
	return 0;
}

int LuaMachine::SetCameraControl(lua_State * state)
{
	int controlType = luaL_checknumber(l, 1);

	switch (controlType)
	{
	default:
		FrameworkHelpers::EnableCameraMovement();
		break;
	case 0:
		FrameworkHelpers::DisableCameraMovement();
		EditorGUI::editor_cameraWindowMode = 0;
		break;
	case 1:
		FrameworkHelpers::DisableCameraMovement();
		EditorGUI::editor_cameraWindowMode = 1;
		break;
	case 2:
		FrameworkHelpers::DisableCameraMovement();
		EditorGUI::editor_cameraWindowMode = 2;
		break;
	}

	return 0;
}

int LuaMachine::SetCameraPosition(lua_State * state)
{
	float x = luaL_checknumber(l, 1);
	float y = luaL_checknumber(l, 2);
	float z = luaL_checknumber(l, 3);
	Vector3 pos = Vector3(x, y, z);

	EditorGUI::editor_cameraWindowPos[0] = x;
	EditorGUI::editor_cameraWindowPos[1] = y;
	EditorGUI::editor_cameraWindowPos[2] = z;

	return 0;
}

int LuaMachine::SetCameraLook(lua_State * state)
{
	float x = luaL_checknumber(l, 1);
	float y = luaL_checknumber(l, 2);
	float z = luaL_checknumber(l, 3);
	Vector3 pos = Vector3(x, y, z);

	EditorGUI::editor_cameraWindowLook[0] = x;
	EditorGUI::editor_cameraWindowLook[1] = y;
	EditorGUI::editor_cameraWindowLook[2] = z;

	return 0;
}

int LuaMachine::FadeIn(lua_State * state)
{
	int a1 = luaL_checknumber(l, 1);
	float a2 = luaL_checknumber(l, 2);
	float a3 = luaL_checknumber(l, 3);
	float a4 = luaL_checknumber(l, 4);

	unnamed::ccIa_FadeIn(a1, a2, a3, a4);

	return 0;
}

int LuaMachine::FadeOut(lua_State * state)
{
	int a1 = luaL_checknumber(l, 1);
	float a2 = luaL_checknumber(l, 2);
	float a3 = luaL_checknumber(l, 3);
	float a4 = luaL_checknumber(l, 4);

	unnamed::ccIa_FadeOut(a1, a2, a3, a4);
	return 0;
}

int LuaMachine::FrameCounter(lua_State * state)
{
	lua_pushnumber(state, EditorGUI::frameCounter);

	return 1;
}

int LuaMachine::SetColorFilterState(lua_State * state)
{
	bool enable = luaL_checknumber(l, 1);
	EditorGUI::editor_colorFilterDir.enable = true;
	return 0;
}

int LuaMachine::SetColorFilterColor(lua_State * state)
{
	float r = luaL_checknumber(l, 1);
	float g = luaL_checknumber(l, 2);
	float b = luaL_checknumber(l, 3);
	float a = luaL_checknumber(l, 4);

	EditorGUI::editor_colorFilterDir.colorA = Vector4(r, g, b, a);

	return 0;
}

int LuaMachine::SetFogColor(lua_State * state)
{
	float r = luaL_checknumber(l, 1);
	float g = luaL_checknumber(l, 2);
	float b = luaL_checknumber(l, 3);

	EditorGUI::editor_renderEditorColor = Vector3(r, g, b);

	return 0;
}

int LuaMachine::SetFogParams(lua_State * state)
{
	float near_ = luaL_checknumber(l, 1);
	float far_ = luaL_checknumber(l, 2);
	float amount = luaL_checknumber(l, 3);

	EditorGUI::editor_renderEditorParams = Vector3(near_, far_, amount);

	return 0;
}

int LuaMachine::ClearStage(lua_State * state)
{
	EditorGUI::ClearStage(true);

	return 0;
}

int LuaMachine::SetObjectPosition(lua_State * state)
{
	const char* objName = luaL_checkstring(l, 1);
	float x = luaL_checknumber(l, 2);
	float y = luaL_checknumber(l, 3);
	float z = luaL_checknumber(l, 4);

	std::string objStr = std::string(objName);

	EditorBase * e = EditorBase::GetInstance();
	int objIndex = -1;
	int objCount = e->editorObjectList.size();
	for (int x = 0; x < objCount; x++)
	{
		EditorObject* eObj = e->editorObjectList[x];
		std::string currentObj = eObj->name;

		if (currentObj == objStr)
		{
			objIndex = x;
			x = objCount;
		}
	}

	if (objIndex == -1) return 0; // if no object

	EditorObject* eObj = e->editorObjectList[objIndex];
	if (eObj->anmclump == nullptr)
	{
		ccStageClump * clump = eObj->clump;
		ccStageClump::SetPosition(clump, &Vector3(x, y, z));
	}
	else
	{
		nuccAnimParams * anm = (nuccAnimParams*)(eObj->anmclump);
		anm->SetPosition(Vector3(x, y, z));
	}

	eObj->position = Vector3(x, y, z);

	return 0;
}

int LuaMachine::SetObjectScale(lua_State * state)
{
	const char* objName = luaL_checkstring(l, 1);
	float x = luaL_checknumber(l, 2);
	float y = luaL_checknumber(l, 3);
	float z = luaL_checknumber(l, 4);

	std::string objStr = std::string(objName);

	EditorBase * e = EditorBase::GetInstance();
	int objIndex = -1;
	int objCount = e->editorObjectList.size();
	for (int x = 0; x < objCount; x++)
	{
		EditorObject* eObj = e->editorObjectList[x];
		std::string currentObj = eObj->name;

		if (currentObj == objStr)
		{
			objIndex = x;
			x = objCount;
		}
	}

	if (objIndex == -1) return 0; // if no object

	EditorObject* eObj = e->editorObjectList[objIndex];
	if (eObj->anmclump == nullptr)
	{
		ccStageClump * clump = eObj->clump;
		ccStageClump::SetScale(clump, &Vector3(x, y, z));
	}
	else
	{
		nuccAnimParams * anm = (nuccAnimParams*)(eObj->anmclump);
		anm->SetScale(Vector3(x, y, z));
		anm->Update();
	}

	eObj->scale = Vector3(x, y, z);

	return 0;
}
