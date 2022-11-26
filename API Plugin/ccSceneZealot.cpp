#include "ccSceneZealot.h"
#include "ccSceneManager.h"
#include "ccGameDrawEnv.h"

ccSceneZealot::ccSceneZealotParams * ccSceneZealot::mp;

void __fastcall ccSceneZealot::Execute(__int64 mem)
{
	if (!mp)
	{
		std::cout << "mp is null" << std::endl;
		return;
	}

	float resx = Game::GetResX();
	float resy = Game::GetResY();

	if (mp->m_mouseLook == nullptr) mp->m_mouseLook = new Editor::MouseLook();
	mp->m_mouseLook->Update((HWND)(hwndGlobal));

	// Camera
	ccCmnCameraDirector* camDir = ccCmnScreenManager::GetCameraDirector(Game::GetCmnScreenManager(), 0);
	if (camDir)
	{
		//std::cout << "Camera director: " << std::hex << std::uppercase << camDir << std::endl;

		ccCmnCamera* activeCamera = (ccCmnCamera*)(ccCmnCameraDirector::GetActiveCamera(camDir));
		//std::cout << "active camera: " << std::hex << activeCamera << std::endl;

		ccCmnCamera* camPtr = activeCamera;
		if (activeCamera)
		{
			Vector3 forward = mp->m_mouseLook->CalculateLookPoint();
			Vector3 right = Vector3(forward.y, forward.x, forward.z);

			float camSpeed = 8;
			if (GetAsyncKeyState(VK_SHIFT)) camSpeed = 16;

			if (GetAsyncKeyState('W')) *(mp->m_camPos) = *(mp->m_camPos) + (forward.Normalize() * camSpeed);
			if (GetAsyncKeyState('S')) *(mp->m_camPos) = *(mp->m_camPos) - (forward.Normalize() * camSpeed);

			if (camPtr)
			{
				//Vector3 * look = (Vector3*)((__int64)(camPtr)+124);
				//*look = *(mp->m_camPos) + (forward * 5);

				ccCmnCamera::SetCameraPosNew(camPtr, mp->m_camPos);
				Vector3 * look = &(camPtr->m_look);
				*look = *(mp->m_camPos) + (forward * 5);

				//float * fov = (float*)((__int64)(camPtr)+44);
				//*fov = 75;

				camPtr->m_fov = 75;
				camPtr->m_tilt.x = 0;
				camPtr->m_tilt.y = 1;
				camPtr->m_tilt.z = 0.01;

				ccCmnCamera::Update((ccCmnCamera*)camPtr);
			}

			Vector3 camPosA = camPtr->m_position;
			mp->m_txt_campos.size = mp->defaultFontSize;
			mp->m_txt_campos.SetText(std::to_string(camPosA.x) + ", " + std::to_string(camPosA.y) + ", " + std::to_string(camPosA.z), resx * 0.02, resy * 0.94);
		}
		else
		{
			if (ccCmnCameraDirector::GetCameraOperator((ccCmnCameraDirector*)camDir, 0xB))
			{
				ccCmnCameraDirector::ClearAllCameraOperator(camDir);
			}

			ccCmnCameraDirector::ChangeCameraImmediate(camDir, 1, 0xB);
		}
	}

	// Stage
	ccStageManager * objectList = ccStageManager::GetInstance(); //FrameworkHelpers::GetStageObjectListGlobal();
	if (!mp->m_stageObjectManager)
	{
		ccStageManager::CreateInstance();
		//std::cout << "Created stage manager: " << std::hex << std::uppercase << ccStageManager::GetInstance() << std::endl;

		int stageHash = Nucc::CalcHashFromStr("STAGE_TITLE_STAGE");
		//std::cout << "stage hash" << std::endl;

		ccStageInfoManager* v4 = (ccStageInfoManager*)(*(__int64*)(ccGameRootStateMachine::GetInstance() + 280));
		mp->m_stageObjectManager = (ccStageObjectManager*)(Game::operator_new(0x90, "", 0x34));
		ccStageObjectManager::CcStageObjectManager(mp->m_stageObjectManager, 7);
		//std::cout << "ccstageobjectmanager" << std::endl;

		__int64 stageInfoData = ccStageInfoManager::GetStageInfoData(v4, stageHash);
		//std::cout << "got stageinfo data" << std::endl;

		ccStageObjectManager::Create(mp->m_stageObjectManager, 0, stageInfoData);
		//std::cout << "created objectmanager" << std::endl;

		*(int*)((__int64)(mp->m_stageObjectManager) + 112) = 1;

		ccStageManager::SetStageObject(ccStageManager::GetInstance(), stageHash, (__int64)(mp->m_stageObjectManager));
		//std::cout << "Set stage object" << std::endl;

		ccStageObjectList* objList = ccStageObjectManager::GetObjectList(mp->m_stageObjectManager, 0);
		//std::cout << "AAA Object list: " << std::hex << objList << std::endl;

		//ccStageClump* cmnbod = ccStageObjectList::AddClump(objList, "data/stage/si42a.xfbin", "si42a_sky");
		//std::cout << "ccSceneZealot :: Created mesh at " << std::hex << cmnbod << std::endl;

		//ccStageObjectList::AddClump(objList, "data/spc/1cmnbod1.xfbin", "1cmnbod1");

		//GameObjectCreator::CreateStaticModel_Global((ccStageObjectList*)(Game::ObjectList_GetInstanceGlobal()), "data/stage/si42a.xfbin", "si42a_sky", "", "");

		__int64 v5 = Game::operator_new(0x30, "", 0x108);
		ccTaskBase::EntryTaskWithAllo11(v5, "CtrlZealot", 21, 0, (__int64)(mp->m_stageObjectManager), (__int64)(void*)(ccStageObjectManager::Ctrl));

		__int64 v5a = Game::operator_new(0x30, "", 0x109);
		ccTaskBase::EntryTaskWithAllo11(v5a, "DrawZealot", 87, 0, (__int64)(mp->m_stageObjectManager), (__int64)(void*)(ccStageObjectManager::Draw));
	}
	else
	{
		//std::cout << "BBB Object List: " << ccStageManager::GetInstance() << std::endl;
	}

	// Ui
	if (!mp->fade)
	{
		mp->fade = true;
		ccCmnFade::StartFadeIn(ccCmnFade::GetInstance(), 3000);

		ccGameDrawEnv* cgd = (ccGameDrawEnv*)(Game::ObjectList_GetPtrLightsAndFog());
		for (int x = 0; x < 6; x++)
		{
			ccGameDrawEnv::ResetCelShadeParam(cgd, x);
			ccGameDrawEnv::ResetFogParam(cgd, x);
			ccGameDrawEnv::ResetShadowParam(cgd, x);
			ccGameDrawEnv::ResetGlareParam(cgd, x);
			ccGameDrawEnv::ResetSoftfocusParam(cgd, x);
			ccGameDrawEnv::ResetColorConvParam(cgd, x);
			ccGameDrawEnv::SetColorConvEnable(cgd, x);
			ccGameDrawEnv::sub_14085D0C8(cgd, x);
			ccGameDrawEnv::sub_14085EB70(cgd, x);
		}
		ccGameDrawEnv::sub_14085FE78(cgd, 0, 0);
	}

	if (GetAsyncKeyState(VK_F5))
	{
		switch (mp->m_actualOption)
		{
		default:
			ccSceneManager::Pop(ccSceneManager::GetInstance());
			break;
		}
	}

	/*Vector3 basePos = Vector3(mp->m_txt_marker.position->x, 0, 0);
	float actual_y = 0;
	if (mp->m_txt_options.size() > 0)
	{
		actual_y = mp->m_txt_options[0]->position->y;
	}
	basePos.y = actual_y + (mp->defaultSpacing * mp->m_actualOption);
	mp->m_txt_marker.SetPosition(basePos.x, basePos.y);*/

	return;
}