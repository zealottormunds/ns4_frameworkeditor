#include "ccSceneBoss12_Phase01.h"
#include "Utilities.h"
#include "ccDuelTeam.h"
#include "ccBossBattleLoader.h"
#include "ccGameRootStateMachine.h"

void ccSceneBoss12_Phase01::ReplaceVirtuals()
{
	FrameworkHelpers::ReplaceVirtualFunction(0x140FD2F60, ccSceneBoss12_Phase01::Initialize);
	FrameworkHelpers::ReplaceVirtualFunction(0x140FD2F68, ccSceneBoss12_Phase01::Execute);
}

__int64 __fastcall ccSceneBoss12_Phase01::Initialize(ccSceneBoss12_Phase01 * a1)
{
	reinterpret_cast<void(__fastcall*)(ccSceneBoss12_Phase01*)>(Utilities::GetVirtualFunction((__int64)a1, 1))(a1);

	ccGameProperty* prop = ccGameProperty::GetPropertyHelper(0x1416BDA20, "bossBattle_Phase_INDEX");
	__int64 v3 = prop->m_valueB;
	__int64 v4 = 0;

	if (v3 && (moduleBase + 0x1415C23E8 - 0x140000C00) == reinterpret_cast<__int64(__fastcall*)(__int64)>(Utilities::GetVirtualFunction(v3, 1))(v3))
	{
		v4 = *(__int64*)(prop->m_valueB + 16);
	}
	else v4 = 0;

	*(int*)(v4) = 36;

	ccSceneBoss12StateMachine * oldStateMachine = a1->m_stateMachine;
	if (oldStateMachine)
	{
		__int64 fc = Utilities::GetVirtualFunction((__int64)oldStateMachine, 0);
		reinterpret_cast<void(__fastcall*)(ccSceneBoss12StateMachine*, unsigned int)>(fc)(oldStateMachine, 1);

		a1->m_stateMachine = 0;
	}

	ccSceneBoss12StateMachine * stateMachine = (ccSceneBoss12StateMachine*)(Game::operator_new(0xC0, "", 0x330));
	if (stateMachine) stateMachine = ccSceneBoss12StateMachine::Create(stateMachine);

	a1->m_stateMachine = stateMachine;

	if (stateMachine)
	{
		stateMachine->m_dword02_A8 = 0;
		stateMachine->m_qword00_68 = 0;
		stateMachine->m_qword07_a0 = 0;
		stateMachine->m_qword01_70 = 0;
		stateMachine->m_qword02_78 = 0;
		stateMachine->m_qword03_80 = 0;
		stateMachine->m_qword04_88 = 0;
		stateMachine->m_qword05_90 = 0;
		stateMachine->m_qword06_98 = 0;
		stateMachine->m_dword00_54 = 0;
		stateMachine->m_dword01_60 = 1;
	}

	// Original stuff
	std::cout << "Actual: " << std::hex << a1->m_unkptr00 << std::endl;

	a1->m_customParam = new params();
	a1->m_customParam->m_flash = (ccUiFlash*)ccUiFlash::Create("");
	for (int x = 0; x < 50; x++) a1->m_customParam->m_booleans[x] = false;

	a1->m_customParam->m_flash->LoadFileMaybe(a1->m_customParam->m_flash, "data/ui/flash/FLASH_PLAT/info_mision/info_mision.swf", 0);

	__int64 gameRootStateMachine = *(__int64*)(ccGameRootStateMachine::GetInstance());
	gameRootStateMachine += 392;
	gameRootStateMachine = *(__int64*)(gameRootStateMachine);
	gameRootStateMachine += 96;

	ccBossBattleLoader::LoadFlashTable(gameRootStateMachine, "BOSS_BATTLE_CMN_FLASH", moduleBase + 0x141442BD0 - 0x140000C00);
	Sleep(1000);

	a1->m_customParam->m_mision = info_mision::AllocateAndCreate();
	info_mision::Initialize(a1->m_customParam->m_mision);

	ccScene::AuthorizeGameProperty((__int64)a1);
	return reinterpret_cast<__int64(__fastcall*)(ccSceneBoss12_Phase01*)>(Utilities::GetVirtualFunction((__int64)a1, 2))(a1);;
}

void __fastcall ccSceneBoss12_Phase01::Execute(ccSceneBoss12_Phase01 * a1)
{
	ccSceneBoss12StateMachine * stateMachine = a1->m_stateMachine;
	__int64 v3 = 0;
	if (stateMachine)
	{
		ccStateMachine::Update((ccStateMachine*)stateMachine);

		if (*(int*)((__int64)(stateMachine)+0x50) == 4)
		{
			if (!a1->m_unkptr01)
			{
				if (ccStageManager::GetInstance())
				{
					__int64 v4 = *(__int64*)(moduleBase + 0x1416BDA20 - 0x140000C00 + 0x8);
					ccStageManager * inst = (ccStageManager*)*(__int64*)(moduleBase + 0x141617840 - 0x140000C00); // ccStageManager::GetInstance()
					ccStageObjectManager * objManager = (ccStageObjectManager*)(inst->m_unkptr01);
					ccGameProperty::UnknownFunction00(v4, (__int64)(a1) + 0x50, "StageObjectList", objManager);
					ccGameProperty* Property = ccGameProperty::GetPropertyHelper(0x1416BDA20, "StageMove");
					__int64 v7 = Property->m_valueB;
					if (v7)
					{
						__int64 funct8 = Utilities::GetVirtualFunction(v7, 1);
						__int64 v8 = (moduleBase + 0x1415CB7E0 - 0x140000C00) == reinterpret_cast<__int64(__fastcall*)(__int64)>(funct8)(v7) ? *(__int64*)(v7 + 0x10) : 0;
						if (v8)
							unnamed::sub_14044F5B0(v8, *(int*)(moduleBase + 0x141611A88 - 0x140000C00));
					}
					a1->m_unkptr01 = 1;
				}

				__int64 v9 = a1->m_unkptr02;
				if (v9)
				{
					__int64 funct0 = Utilities::GetVirtualFunction(v9, 0);
					reinterpret_cast<void(__fastcall*)(__int64, __int64)>(funct0)(v9, 1);
					a1->m_unkptr02 = 0;
				}

				__int64 v10 = Game::operator_new(0x50, "", 0x400);
				if (v10)
					v3 = unnamed::sub_14063F164(v10);

				const char* v11 = *(const char**)(moduleBase + 0x14144B490 - 0x140000C00);
				a1->m_unkptr02 = v3;

				unnamed::sub_14030F7D8(*(__int64*)(moduleBase + 0x1416BDA20 - 0x140000C00 + 0x8), (__int64)(a1)+0x50, v11, v3);
			}
			unnamed::sub_1403E4428((__int64)a1);
		}
	}
	return;
	//reinterpret_cast<void(__fastcall*)(ccSceneBoss12_Phase01*)>(moduleBase + 0x3E391C)(a1);
	
	// Original stuff
	ccDuelTeam * p1 = (ccDuelTeam*)(BattleUtils::GetPlayerContainer(0));
	ccDuelTeam * p2 = (ccDuelTeam*)(BattleUtils::GetPlayerContainer(1));
	params* m_params = a1->m_customParam;

	if (p1 && p2)
	{
		ccPlayerContainer * p1c = p1->m_leader;
		ccPlayerContainer * p2c = p2->m_leader;
		
		if (p1c && p2c)
		{
			ccPlayerMain * p1m = p1c->m_playerController;
			ccPlayerMain * p2m = p2c->m_playerController;

			if (p1m && p2m)
			{
				// When you reach 180 health, both characters run backwards and after 3 seconds control is regained
				if (m_params->m_booleans[0] == false)
				{
					if (p2c->m_health < 180)
					{
						m_params->m_booleans[0] = true;
						//p2c->m_playerController->m_modelScale = 2;
						p1m->m_PL_ACT_CURRENT = 0x11;
						p2m->m_PL_ACT_CURRENT = 0x11;
						p1m->m_enableInput = false;
						p2m->m_enableInput = false;
						//info_mision::SetOpen(m_params->m_mision, "+¡Cuidado con el Kamui de Obito!", 0, 0, 1);
						//FrameworkHelpers::SetFog(256 / 111, 0, 0, 10, 3465, 1);
					}
				}
				else
				{
					if (m_params->m_booleans[1] == false)
					{
						if (m_params->m_timers[0] < (Game::GetFPS() * 3)) m_params->m_timers[0]++; // if timer is less than (fps * 3), add to the timer (count 3 seconds)
						else
						{
							m_params->m_booleans[1] = true;
							p1m->m_PL_ACT_CURRENT = 0x10;
							p2m->m_PL_ACT_CURRENT = 0x10;
							p1m->m_enableInput = true;
							p2m->m_enableInput = true;
						}
					}
					else
					{

					}
				}
			}
		}
	}
}

__int64 __fastcall ccSceneBoss12_Phase01::Finalize(ccSceneBoss12_Phase01 * a1)
{
	return 0;
}
