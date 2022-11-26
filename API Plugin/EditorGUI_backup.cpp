#include "EditorGUI.h"
#include "EditorBase.h"
#include "MouseLook.h"
#include <sstream>

#include "GameObjectCreator.h"

#include "ccStageManager.h"
#include "ccStageClumpContainer.h"
#include "ccStageObjectManager.h"
#include "ccStageObjectList.h"
#include "FileParser.h"

#include "ccAdvBaseAnm.h"
#include "nuccAnm.h"

#include <WinSock2.h>
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")
XINPUT_STATE controller;

#include "ComponentGUI.h"
#include "ccUiLayoutParts.h"
#include "ccGameRootStateMachine.h"
#include "ccDuelTeam.h"
#include "ccGame.h"

bool EditorGUI::WindowList[100];
std::vector<nuccFileLoadList::loadStruct*> loadList;
std::vector<nuccFileLoadList::loadStruct*> gizmoLoadList;
__int64 EditorGUI::frameCounter = 0;

#define editor_stageEditor 0
int editor_fileSelected = -1;
char editor_spawnPath[255] = "data/spc/1cmnbod1.xfbin";
char editor_spawnModel[255] = "1cmnbod1";
char editor_spawnAnmPath[255] = "";
std::string editor_spawnAnmName = "";
bool editor_spawnShowList = false;
int editor_spawnSelected = -1;
Vector3 editor_spawnPosition = Vector3(0, 0, 0);
Vector3 editor_spawnScale = Vector3(1, 1, 1);
Vector3 editor_moveAxis = Vector3(0, 0, 0);
Vector3 editor_scaleAxis = Vector3(0, 0, 0);
bool editor_spawnHasAnm = false;
char editor_spawnSaveStagePath[255] = "";

#define editor_musicWindow 1
int editor_musicWindowID = 0;
int editor_musicWindowChannel = 0;
int editor_musicWindowSEParams[3];

#define editor_cameraWindow 2
float EditorGUI::editor_cameraWindowPos[3];
float EditorGUI::editor_cameraWindowLook[3];
bool EditorGUI::editor_cameraWindowEnableCam = true;
int EditorGUI::editor_cameraWindowMode = 0;
float editor_cameraWindowPlAngle = 0;
float editor_cameraWindowPlHeight = 400;
float editor_cameraWindowPlDistance = 600;
Vector3 editor_cameraWindowPlLookOffset = Vector3(0, 0, 100);

#define editor_playerWindow 3
int editor_playerWindowPID = 0;
Vector3 editor_playerWindowPlPos = Vector3(0, 0, 0);
int editor_playerWindow_tab = 0;

#define editor_renderEditor 4
Vector3 EditorGUI::editor_renderEditorColor;
Vector3 EditorGUI::editor_renderEditorParams = Vector3(10, 100000, 1);
float editor_renderEditorOutlineSize = 0;
Vector3 editor_renderEditorOutline = Vector3(0, 0, 0);
Vector3 editor_renderEditorLightColor = Vector3(0, 0, 0);
Vector3 editor_renderEditorShadowDirc = Vector3(0, 0, 0);
Vector3 editor_renderEditorLightDir = Vector3(0, 0, 0);
ColorFilterDirectionalSettings EditorGUI::editor_colorFilterDir;
bool editor_visibilityEditorShowStageClump = true;
bool editor_visibilityEditorShowStageAnm = true;
bool editor_renderEditor_enableChanges = false;

#define editor_advEditor 5
std::string editor_advEditor_battleParam = "";
int editor_advEditor_pushScene = 0x8;
std::string editor_advEditor_gpSpawnChar = "";
Vector3 editor_advEditor_gpSpawnPos;

#define editor_uiEditor 6
std::string editor_uiEditor_path = "data/ui/max/boot_logo/boot_logo.xfbin";
std::string editor_uiEditor_name = "criware";
int editor_uiEditor_int = 0;

#define editor_sceneEditor 7
int editor_sceneEditor_selected = 0;
int editor_sceneEditor_actualTab = 0;

Editor::ComponentGUI* editor_componentGUI;
NuccAnm * customAnm;

void EditorGUI::InitGUI()
{
	for (int x = 0; x < sizeof(WindowList); x++)
	{
		WindowList[x] = false;
	}
}

unsigned int v6[6]; // [rsp+30h] [rbp-18h] BYREF
const char *v7 = "+123";
const char *v8 = "+234";
const char* v9 = "+345";
static const char* const values[] = { "+string one", "+string two" };

ccStageClump * spawnTest;
//nuccFont2 * font2test;
__int64 v12a; // [rsp+70h] [rbp-90h]
__int64 v12b; // [rsp+70h] [rbp-90h]
__int64 v13; // [rsp+80h] [rbp-80h]
__int64 v14;
bool a = true;
void EditorGUI::LoopGUI(bool Show, __int64 hwnd)
{
	frameCounter++;

	ccCmnCamera * camPtr = FrameworkHelpers::GetActiveCamera();
	XInputGetState(0, &controller);
	
	if (Show)
	{
		// Main menu bar
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("Game Editor"))
		{
			if (ImGui::MenuItem("Stage Editor", "")) { WindowList[editor_stageEditor] = true; }
			if (ImGui::MenuItem("Music Player", "")) { WindowList[editor_musicWindow] = true; }
			if (ImGui::MenuItem("Camera Manager", "")) { WindowList[editor_cameraWindow] = true; }
			if (ImGui::MenuItem("Player Manager", "")) { WindowList[editor_playerWindow] = true; }
			if (ImGui::MenuItem("Render Editor", "")) { WindowList[editor_renderEditor] = true; }
			if (ImGui::MenuItem("Adventure Editor", "")) { WindowList[editor_advEditor] = true; }
			if (ImGui::MenuItem("UI Editor", "")) { WindowList[editor_uiEditor] = true; }
			if (ImGui::MenuItem("Scene Editor", "")) { WindowList[editor_sceneEditor] = true; }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();

		// Spawn window
		if (WindowList[editor_stageEditor])
		{
			//ImGui::SetNextWindowSize(ImVec2(400, 500));
			ImGui::Begin("Stage Editor", &WindowList[editor_stageEditor]);
			ImGui::TextWrapped("You can use this window to edit the current stage.\n");
			Editor::EditorBase * e = Editor::EditorBase::GetInstance();

			ImGui::Dummy(ImVec2(0, 20));
			ImGui::TextWrapped("File List (Loaded by Framework)");

			// Load file
			ImGui::InputText("Path", editor_spawnPath, 255);
			if (ImGui::Button("Load File")) LoadHelperEditor(editor_spawnPath);

			//  File list
			int fileCount = loadList.size();
			if (ImGui::ListBoxHeader("File List"))
			{
				for (int x = 0; x < fileCount; x++)
				{
					std::stringstream ptrRead;
					ptrRead << loadList[x]->path << ": " << std::hex << std::uppercase << (__int64)(loadList[x]->ptr);
					std::string name = ptrRead.str();

					if (ImGui::Selectable(name.c_str(), x == editor_fileSelected))
					{
						editor_fileSelected = x;
					}
				}
				ImGui::ListBoxFooter();
			}
			if (ImGui::Button("Unload") && editor_fileSelected != -1)
			{
				nuccFileLoadList* file = loadList[editor_fileSelected]->ptr;

				if (file)
				{
					nuccFileLoadList::UnloadByIndex(file, 0);
					loadList.erase(loadList.begin() + editor_fileSelected);
				}
			}
			ImGui::SameLine();
			if (fileCount && ImGui::Button("Unload All"))
			{
				for (int x = 0; x < fileCount; x++)
				{
					nuccFileLoadList* file = loadList[x]->ptr;

					if (file)
					{
						nuccFileLoadList::UnloadByIndex(file, 0);
					}
				}
				loadList.clear();
			}
			if (ImGui::Button("List Model") && editor_fileSelected != -1)
			{
				if (editor_fileSelected < loadList.size())
				{
					//const char* name = loadList[editor_fileSelected]->path.c_str();
					const char* name = _strdup(loadList[editor_fileSelected]->path.c_str());
					FrameworkHelpers::ListChunkType("nuccChunkModel", name);
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("List Anm") && editor_fileSelected != -1)
			{
				if (editor_fileSelected < loadList.size())
				{
					const char* name = _strdup(loadList[editor_fileSelected]->path.c_str());
					FrameworkHelpers::ListChunkType("nuccChunkAnm", name);
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("List Texture") && editor_fileSelected != -1)
			{
				if (editor_fileSelected < loadList.size())
				{
					const char* name = _strdup(loadList[editor_fileSelected]->path.c_str());
					FrameworkHelpers::ListChunkType("nuccChunkTexture", name);
				}
			}
			if (ImGui::Button("List Clump") && editor_fileSelected != -1)
			{
				if (editor_fileSelected < loadList.size())
				{
					const char* name = _strdup(loadList[editor_fileSelected]->path.c_str());
					FrameworkHelpers::ListChunkType("nuccChunkClump", name);
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("List Coord") && editor_fileSelected != -1)
			{
				if (editor_fileSelected < loadList.size())
				{
					const char* name = _strdup(loadList[editor_fileSelected]->path.c_str());
					FrameworkHelpers::ListChunkType("nuccChunkCoord", name);
				}
			}

			ImGui::Dummy(ImVec2(20, 0));
			ImGui::InputText("Mesh / Hit", editor_spawnModel, 255);

			// Spawn
			bool spawnedAnmThisFrame = false;
			ImGui::Checkbox("Animated Mesh (No Collision)", &editor_spawnHasAnm);
			ImGui::SameLine();
			if (ImGui::Button("Spawn") && editor_fileSelected != -1)
			{
				ccStageObjectList * objectList = FrameworkHelpers::GetStageObjectListGlobal();

				// Create gizmo
				if (e->editorObjectList.size() == 0)
				{
					__int64 r = LoadHelperEditor("data/editor/gizmo_arrow.xfbin", true);
					if (r) CreateGizmo();
				}

				const char * editor_spawnPathSelected = loadList[editor_fileSelected]->path.c_str();

				bool canCreate = false;
				
				if (editor_spawnHasAnm == false)
				{
					canCreate= FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkClump, editor_spawnPathSelected, editor_spawnModel) ||
						FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkModelHit, editor_spawnPathSelected, editor_spawnModel) ||
						FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkModel, editor_spawnPathSelected, editor_spawnModel);
				}
				else if (editor_spawnHasAnm)
				{
					canCreate = FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkAnm, editor_spawnPathSelected, editor_spawnModel);
				}

				if (canCreate && objectList > 0)
				{
					Editor::EditorObject * eObj = GameObjectCreator::CreateObjectWithMesh(objectList, editor_spawnPathSelected, editor_spawnModel, editor_spawnHasAnm);
					
					if (eObj != nullptr)
					{
						if (editor_spawnHasAnm)
						{
							// Swap static clump to animation clump
							eObj->anmclump = (ccStageAnm*)(eObj->clump);
							eObj->clump = 0;
							std::cout << "Spawned with animation capabilities" << std::endl;

							spawnedAnmThisFrame = true;
						}
						else
						{
							// Keep same clump, and try to find collision
							ccStageObjectList::AddCollision(FrameworkHelpers::GetStageObjectListGlobal(), eObj->clump);
						}
					}
				}
				else
				{
					std::cout << "File not loaded or not found mesh in file" << std::endl;
				}
			}

			if (ImGui::Button("Spawn Test"))
			{
				Utilities::Nop(moduleBase + 0x812059, 5);

				spawnTest = ccStageObjectList::AddClump(0, "data/spc/1cmnbod1.xfbin", "1cmnbod1");
				std::cout << "alloc " << std::hex << (__int64)spawnTest << std::endl;

				DWORD old = Utilities::ChangeProtect(moduleBase + 0x812059, 5, PAGE_EXECUTE_READWRITE);
				char goback[5] = { 0xE8, 0xDE, 0x26, 0x00, 0x00 };
				memcpy((void*)(moduleBase + 0x812059), goback, 5);
				Utilities::ChangeProtect(moduleBase + 0x812059, 5, old);
			}

			if (spawnTest)
			{
				__int64 base = *(__int64*)((__int64)(spawnTest) + 24);
				__int64 nc = *(__int64*)(base + 24);
				NuccClump::Update((NuccClump*)nc);
				NuccClump::Draw((NuccClump*)nc);
			}

			// Object List
			ImGui::Dummy(ImVec2(0, 20));
			ImGui::Text("Object List");
			if (ImGui::ListBoxHeader("Object List"))
			{
				for (int x = 0; x < e->editorObjectList.size(); x++)
				{
					std::stringstream ptrRead;
					if(e->editorObjectList[x]->anmclump == nullptr) ptrRead << e->editorObjectList[x]->name << " [ccStageClump]: " << std::hex << std::uppercase << (__int64)(e->editorObjectList[x]->clump);
					else ptrRead << e->editorObjectList[x]->name << " [ccStageAnm]: " << std::hex << std::uppercase << (__int64)(e->editorObjectList[x]->anmclump);
					std::string name = ptrRead.str();

					if (ImGui::Selectable(name.c_str(), x == editor_spawnSelected))
					{
						editor_spawnSelected = x;

						ccStageClump * c = e->editorObjectList[editor_spawnSelected]->clump;

						if(c != nullptr) editor_spawnPosition = ccStageClump::GetPosition(c);
						else if (e->editorObjectList[editor_spawnSelected]->anmclump != nullptr) editor_spawnPosition = ((nuccAnimParams*)(e->editorObjectList[editor_spawnSelected]->anmclump))->GetPosition();

						if (c != nullptr) editor_spawnScale = ccStageClump::GetScale(c);
						else if (e->editorObjectList[editor_spawnSelected]->anmclump != nullptr) editor_spawnScale = ((nuccAnimParams*)(e->editorObjectList[editor_spawnSelected]->anmclump))->GetScale();
					}
				}
				ImGui::ListBoxFooter();

				if (ImGui::Button("Up"))
				{
					editor_spawnSelected--;
					if (editor_spawnSelected < -1) editor_spawnSelected = -1;
				}
				ImGui::SameLine();
				if (ImGui::Button("Down"))
				{
					editor_spawnSelected++;
					if (editor_spawnSelected >= e->editorObjectList.size()) editor_spawnSelected = e->editorObjectList.size() - 1;
				}
				ImGui::SameLine();
				if (ImGui::Button("Delete Selected"))
				{
					DeleteObject(editor_spawnSelected);
					editor_spawnSelected = -1;
				}
			}

			// Add components
			ImGui::Dummy(ImVec2(0, 20));
			if (editor_spawnSelected != -1)
			{
				if (!editor_componentGUI)
				{
					if (ImGui::Button("GameObject Properties"))
					{
						editor_componentGUI = new Editor::ComponentGUI(e->editorObjectList[editor_spawnSelected]);
					}
				}
				else
				{
					bool state = editor_componentGUI->show;
					if (state)
					{
						editor_componentGUI->Update();
					}
					else
					{
						delete editor_componentGUI;
						editor_componentGUI = nullptr;
					}
				}
			}
			
			// Animation nuccAnm
			if (editor_spawnSelected != -1 && e->editorObjectList[editor_spawnSelected]->anmclump != nullptr)
			{
				ImGui::InputText("Anm ID", &editor_spawnAnmName);
				if (ImGui::Button("Play nuccAnm"))
				{
					__int64 canCreate = 0;

					const char * editor_spawnPathSelected = loadList[editor_fileSelected]->path.c_str();
					canCreate = FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkAnm, editor_spawnPathSelected, editor_spawnAnmName.c_str());

					if (canCreate)
					{
						//std::cout << "Ok 1" << std::endl;

						Editor::EditorObject * eObj = e->editorObjectList[editor_spawnSelected];
						
						//ccStageClump * c = eObj->clump;
						//ccAdvBaseAnm * anm = (eObj->anmclump);
						//anm = *(ccAdvBaseAnm**)((__int64)(anm) + 32);
						//NuccAnm* nuccANM = *(NuccAnm**)((__int64)(anm)+8);

						ccStageAnm * stageAnm = eObj->anmclump;
						ccAdvBaseAnm * advBase = stageAnm->m_advBaseAnm;
						NuccAnm * nuccAnm = advBase->m_nuccAnm;

						//std::cout << "Ok 2" << std::endl;

						__int64 anmchunk = nuccXfbinDocument::SearchAnm(editor_spawnPathSelected, editor_spawnAnmName.c_str());

						//std::cout << "Ok 3" << std::endl;

						if (anmchunk)
						{
							NuccAnm::SetAnm(nuccAnm, anmchunk, 0, 0, 0, 0);
						}
						else std::cout << "Error loading anm" << std::endl;
					}
					else
					{
						std::cout << "Animation " << editor_spawnAnmName << " not found in " << editor_spawnPathSelected << std::endl;
					}
				}
			}

			if (editor_spawnSelected != -1)
			{
				Editor::EditorObject * eObj = e->editorObjectList[editor_spawnSelected];
				ccStageClump * c = eObj->clump;
				Vector3 * scr = new Vector3(-1, -1, -1);
				
				ImGui::Dummy(ImVec2(0, 20));
				ImGui::TextWrapped("Transform Settings");

				// Move Input
				ImGui::InputFloat3("Position", &editor_spawnPosition.x);

				// Move slider
				ImGui::SliderFloat3("Move Axis", &editor_moveAxis.x, -1, 1);
				editor_spawnPosition = editor_spawnPosition + editor_moveAxis * 5;

				if (eObj->clump != nullptr) ccStageClump::SetPosition(c, &editor_spawnPosition);
				else if (eObj->anmclump != nullptr) ((nuccAnimParams*)(eObj->anmclump))->SetPosition(editor_spawnPosition);
				eObj->position = editor_spawnPosition;

				e->editorObjectList[editor_spawnSelected]->position = editor_spawnPosition;
				editor_moveAxis = Vector3(0, 0, 0);

				//ImGui::InputFloat3("Rotation", e->editorObjectList[editor_spawnSelected])

				// Scale input
				ImGui::Dummy(ImVec2(0, 20));
				ImGui::InputFloat3("Scale", &editor_spawnScale.x);

				// Scale slider
				ImGui::SliderFloat3("Scale Axis", &editor_scaleAxis.x, -1, 1);
				editor_spawnScale = editor_spawnScale + editor_scaleAxis * 0.1;

				if (spawnedAnmThisFrame)
				{
					editor_spawnScale.x = 1;
					editor_spawnScale.y = 1;
					editor_spawnScale.z = 1;
				}

				if (eObj->clump != nullptr) ccStageClump::SetScale(c, &editor_spawnScale);
				else if (eObj->anmclump != nullptr && spawnedAnmThisFrame == false) ((nuccAnimParams*)(eObj->anmclump))->SetScale(editor_spawnScale);
				eObj->scale = editor_spawnScale;

				e->editorObjectList[editor_spawnSelected]->scale = editor_spawnScale;
				editor_scaleAxis = Vector3(0, 0, 0);

				if (eObj->anmclump != nullptr)
				{
					ImGui::Dummy(ImVec2(0, 20));
					ImGui::Text("Animation Settings");
					ImGui::InputFloat("Animation Speed", &(((nuccAnimParams*)(eObj->anmclump))->chunkParam->speed));
					ImGui::Checkbox("Display?", (bool*)&(((nuccAnimParams*)(eObj->anmclump))->chunkParam->display));

					// stuff
					NuccAnm * nuccAnm = ((eObj->anmclump)->m_advBaseAnm)->m_nuccAnm;
					ImGui::SliderInt("m_frame", &(nuccAnm->m_actualFrame), 0, nuccAnm->m_maxFrame);
					//ImGui::InputInt("m_frame", &(nuccAnm->m_actualFrame));
				}

				//if (eObj->anmclump != nullptr) ((nuccAnimParams*)(eObj->anmclump))->Update();

				// Update gizmo pos
				int gizmoCount = e->gizmoList.size();
				if (gizmoCount > 0)
				{
					ccStageClump* arrows = e->gizmoList[0]->clump;
					Editor::Animation * arr_anm = (Editor::Animation*)(e->gizmoList[0]->components[0]);
					arr_anm->anmOffset = e->editorObjectList[editor_spawnSelected]->position;
				}
			}
			else
			{
				// Update gizmo pos
				int gizmoCount = e->gizmoList.size();
				if (gizmoCount > 0)
				{
					ccStageClump* arrows = e->gizmoList[0]->clump;
					Editor::Animation * arr_anm = (Editor::Animation*)(e->gizmoList[0]->components[0]);
					arr_anm->anmOffset = Vector3(-9999, -9999, -9999);
				}
			}

			// Misc
			ImGui::Dummy(ImVec2(0, 20));
			ImGui::Text("Spawn Misc Effects");
			if (ImGui::Button("Create Rain"))
			{
				if (LoadHelperEditor("data/stage/sae_rain.xfbin"))
				{
					ccStageObjectList * objectList = FrameworkHelpers::GetStageObjectListGlobal();
					ccStageObjectList* objListPlus = (ccStageObjectList*)((__int64)(objectList)+168);
					unnamed::ccCreateValleyStageEffect(0, objListPlus);
				}
			}

			ImGui::Dummy(ImVec2(0, 20));
			ImGui::Text("Stage Settings");
			ImGui::InputText("Save/Load Path", &editor_spawnSaveStagePath[0], 255);

			if (ImGui::Button("Save"))
			{
				SaveStage();
			}
			ImGui::SameLine();
			if (ImGui::Button("Load"))
			{
				if (FileParser::FileExists(editor_spawnSaveStagePath))
				{
					LoadStage(editor_spawnSaveStagePath);
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Clear Stage"))
			{
				ClearStage(false);
			}

			ImGui::End();
		}

		// Music player
		if (WindowList[editor_musicWindow])
		{
			ImGui::SetNextWindowSize(ImVec2(200, 300));
			ImGui::Begin("Music Player", &WindowList[editor_musicWindow], ImGuiWindowFlags_NoResize);
			ImGui::TextWrapped("You can use this window to play music and sound effects.\n");
			ImGui::InputInt("BGM ID", &editor_musicWindowID);
			ImGui::InputInt("Channel", &editor_musicWindowChannel);
			if (ImGui::Button("Play BGM"))
			{
				unnamed::ccSndBgmCtrl(editor_musicWindowID, editor_musicWindowChannel);
			}

			ImGui::Dummy(ImVec2(0.0f, 20.0f));
			ImGui::InputInt("ID", &editor_musicWindowSEParams[0]);
			if (ImGui::Button("Play SE")) unnamed::ccAdvPlaySound_2D(editor_musicWindowSEParams[0]);
			if (ImGui::Button("Prev"))
			{
				if (editor_musicWindowSEParams[0] > 0) editor_musicWindowSEParams[0]--;
				unnamed::ccAdvPlaySound_2D(editor_musicWindowSEParams[0]);
			}
			if (ImGui::Button("Next"))
			{
				editor_musicWindowSEParams[0]++;
				unnamed::ccAdvPlaySound_2D(editor_musicWindowSEParams[0]);
			}

			ImGui::End();
		}

		// Camera window
		if (WindowList[editor_cameraWindow])
		{
			ImGui::SetNextWindowSize(ImVec2(300, 250));
			ImGui::Begin("Camera Manager", &WindowList[editor_cameraWindow]);

			std::string camText = "Camera: ";

			if (camPtr)
			{
				std::stringstream camPtrRead;
				camPtrRead << std::hex << std::uppercase << camPtr;
				camText = camText + camPtrRead.str();

				editor_cameraWindowPos[0] = *((float*)(((__int64)camPtr) + 112));
				editor_cameraWindowPos[1] = *((float*)(((__int64)camPtr) + 116));
				editor_cameraWindowPos[2] = *((float*)(((__int64)camPtr) + 120));
			}
			else
			{
				camText = camText + "[nullptr]";
			}

			ImGui::TextWrapped(camText.c_str());

			ImGui::InputFloat3("Position", &editor_cameraWindowPos[0]);

			std::string camMoveBtnText = "Disable Camera Movement";
			if (editor_cameraWindowEnableCam == false) camMoveBtnText = "Enable Camera Movement";
			if (ImGui::Button(camMoveBtnText.c_str()))
			{
				editor_cameraWindowEnableCam = !editor_cameraWindowEnableCam;
				if (editor_cameraWindowEnableCam)
				{
					FrameworkHelpers::EnableCameraMovement();
				}
				else
				{
					FrameworkHelpers::DisableCameraMovement();
				}
			}

			ImGui::InputInt("Camera Mode", &editor_cameraWindowMode);

			ImGui::Dummy(ImVec2(0, 20));
			ImGui::InputFloat("Cam Distance", &editor_cameraWindowPlDistance);
			ImGui::InputFloat("Cam Height", &editor_cameraWindowPlHeight);
			ImGui::InputFloat3("Look Offset", &editor_cameraWindowPlLookOffset.x);

			ImGui::End();
		}

		// Player window
		if (WindowList[editor_playerWindow])
		{
			//ImGui::SetNextWindowSize(ImVec2(300, 300));
			ImGui::Begin("Player Window", &WindowList[editor_playerWindow]);

			ImGui::InputInt("PLAYER_SIDE", &editor_playerWindowPID);
			if (editor_playerWindowPID < 0) editor_playerWindowPID = 0;
			if (editor_playerWindowPID > 1) editor_playerWindowPID = 1;

			// Container
			std::string contText = "1P CONTAINER: ";
			ccDuelTeam * container = (ccDuelTeam*)(BattleUtils::GetPlayerContainer(editor_playerWindowPID));

			if (container)
			{
				std::stringstream plPtrRead;
				plPtrRead << std::hex << std::uppercase << container;
				contText = contText + plPtrRead.str();
			}
			else
			{
				contText = contText + "[nullptr]";
			}

			ImGui::TextWrapped(contText.c_str());

			// Player
			std::string plText = "1P CTRL: ";
			ccPlayerMain * pl = BattleUtils::ccGame_GetPlayerLeader(editor_playerWindowPID);

			if (pl)
			{
				std::stringstream plPtrRead;
				plPtrRead << std::hex << std::uppercase << pl;
				plText = plText + plPtrRead.str();
			}
			else
			{
				plText = plText + "[nullptr]";
			}

			ImGui::TextWrapped(plText.c_str());

			if (pl)
			{
				ImGui::InputFloat3("Position", &editor_playerWindowPlPos.x);
				if (ImGui::Button("Set Position"))
				{
					Vector3* pospl = (Vector3*)((__int64)(pl) + 112);
					*pospl = editor_playerWindowPlPos;
				}

				ImGui::InputInt("Tab", &editor_playerWindow_tab);
				if (editor_playerWindow_tab < 0) editor_playerWindow_tab = 0;
				if (editor_playerWindow_tab > 1) editor_playerWindow_tab = 1;

				ImGui::Dummy(ImVec2(0, 10));

				if (editor_playerWindow_tab == 0)
				{
					std::string ptrstr = "ccPlayerMain: " + Utilities::HexToString((__int64)pl);
					ImGui::Text(ptrstr.c_str());

					Vector3 spinepos;
					ccGameObjSubDraw::GetCoordPosByPartialName(pl->m_gameObjSubDraw, &spinepos, "spine");
					ImGui::InputFloat3("Spine", &spinepos.x);

					ImGui::InputFloat("Life", &container->m_leader->m_health);
					ImGui::InputFloat("MaxLife", &container->m_leader->m_maxHealth);

					ImGui::InputFloat("Chakra", &container->m_leader->m_chakra);
					ImGui::InputFloat("MaxChakra", &container->m_leader->m_maxChakra);

					ImGui::InputFloat("Sub", &container->m_leader->m_substitution);
					ImGui::InputFloat("MaxSub", &container->m_leader->m_maxSubstitution);

					ImGui::InputFloat("Armor", &container->m_leader->m_armor);
					ImGui::InputFloat("MaxArmor", &container->m_leader->m_maxArmor);

					ImGui::InputInt4("Item ID", &container->m_leader->m_itemUp);
					ImGui::InputInt4("Item Count", &container->m_leader->m_itemUpCount);

					ImGui::InputInt("Character ID", &container->m_leader->m_playerController->m_characterID);
					ImGui::InputInt("Enable Input", &container->m_leader->m_playerController->m_enableInput);
					ImGui::InputInt("Enable Control", &container->m_leader->m_playerController->m_enableControl);
					ImGui::InputInt("Draw", &container->m_leader->m_playerController->m_enableDraw);
					ImGui::InputFloat("Scale", &container->m_leader->m_playerController->m_modelScale);
				}
				else if (editor_playerWindow_tab == 1)
				{
					std::string ptrstr = "ccGameObjSubDraw: " + Utilities::HexToString((__int64)(pl->m_gameObjSubDraw));
					ImGui::Text(ptrstr.c_str());

					ccGameObjSubDraw * g = container->m_leader->m_playerController->m_gameObjSubDraw;
					ImGui::InputInt("m_flag00", &(g->m_flag00));
					ImGui::InputInt("m_flag01", &(g->m_flag01));
					ImGui::InputInt("m_flag02", &(g->m_flag02));
					ImGui::InputInt("m_flag03", &(g->m_flag03));
					ImGui::InputInt("m_flag04", &(g->m_flag04));
					ImGui::InputInt("m_flag05", &(g->m_flag05));
					ImGui::InputInt("m_flag06", &(g->m_flag06));
					ImGui::InputInt("m_flag07", &(g->m_flag07));
					ImGui::InputInt("m_updateAndDraw", &(g->m_updateAndDraw));
					ImGui::InputInt("m_flag09", &(g->m_flag09));
					ImGui::InputInt("m_flag10", &(g->m_flag10));
					ImGui::InputInt("m_flag11", &(g->m_flag11));
					ImGui::InputInt("m_flag12", &(g->m_flag12));
					ImGui::Text((const char*)&(g->m_str00));
					ImGui::Text((const char*)&(g->m_str01));
					ImGui::Text((const char*)&(g->m_str02));
					ImGui::Text((const char*)&(g->m_str03));
					ImGui::Text((const char*)&(g->m_str04));
					ImGui::Text((const char*)&(g->m_str05));
					ImGui::Text((const char*)&(g->m_str06));
					ImGui::Text((const char*)&(g->m_str07));
				}

				/*if (ImGui::Button("wall run test 1"))
				{
					unnamed::sub_140594A4C((__int64)pl, 0);
				}
				if (ImGui::Button("wall run test 2"))
				{
					unnamed::sub_140594A4C((__int64)pl, 1);
				}
				if (ImGui::Button("wall run test 3"))
				{
					unnamed::sub_140594A4C((__int64)pl, 2);
				}

				if (ImGui::Button("Visible Volume"))
				{
					GameActor::Base * pla = (GameActor::Base*)pl;
					GameActor::Base::CreateVisibleVolume(pla);
				}*/
			}

			ImGui::End();
		}

		// Render editor
		if (WindowList[editor_renderEditor])
		{
			ImGui::Begin("Light and Fog Editor", &WindowList[editor_renderEditor]);

			// Do fog stuff
			ImGui::Checkbox("Enable Changes", &editor_renderEditor_enableChanges);

			ImGui::Text("Fog");
			ImGui::ColorEdit3("Color", &(editor_renderEditorColor.x));
			ImGui::SliderFloat("Start", &(editor_renderEditorParams.x), 1, editor_renderEditorParams.y);
			ImGui::SliderFloat("End", &(editor_renderEditorParams.y), editor_renderEditorParams.x, 50000);
			ImGui::SliderFloat("Amount", &(editor_renderEditorParams.z), 0, 10);

			// Get outline values
			Vector3 * outlineParam = (Vector3*)(moduleBase + 0x0161B990 - 0xC00);
			float * outlineSizeParam = (float*)(moduleBase + 0x0161B990 - 0xC00 + 16);
			editor_renderEditorOutline = *outlineParam;
			editor_renderEditorOutlineSize = *outlineSizeParam;

			// Do outline stuff
			ImGui::Dummy(ImVec2(0, 10));
			ImGui::ColorEdit3("Outline", &(editor_renderEditorOutline.x));
			ImGui::SliderFloat("Size", &editor_renderEditorOutlineSize, 0, 5);

			if (editor_renderEditor_enableChanges)
			{
				*outlineParam = editor_renderEditorOutline;
				*outlineSizeParam = editor_renderEditorOutlineSize;
			}

			__int64 lightptr = (moduleBase + 0x161B950);
			__int64 ptr = Game::ObjectList_GetPtrLightsAndFog();

			// Do light color stuff
			ImGui::Text("Light");
			editor_renderEditorLightColor = *(Vector3*)(lightptr);
			ImGui::SliderFloat3("Light Color", &(editor_renderEditorLightColor.x), -2, 2);

			if(editor_renderEditor_enableChanges) *(Vector3*)(lightptr) = editor_renderEditorLightColor;

			// Do light direction stuff
			editor_renderEditorLightDir = *(Vector3*)(lightptr + 144);
			ImGui::SliderFloat3("Light Direction", &(editor_renderEditorLightDir.x), -20000, 20000);
			if(editor_renderEditor_enableChanges) *(Vector3*)(lightptr + 144) = editor_renderEditorLightDir;

			//std::cout << "Color: " << std::hex << lightptr << std::endl;
			//std::cout << "Render: " << std::hex << ptr << std::endl;

			// Do shadow stuff
			ImGui::Text("Shadows");
			editor_renderEditorShadowDirc = *(Vector3*)(ptr + 916);
			ImGui::SliderFloat3("Shadow Direction", &(editor_renderEditorShadowDirc.x), -20000, 20000);
			if(editor_renderEditor_enableChanges) *(Vector3*)(ptr + 916) = editor_renderEditorShadowDirc;

			ImGui::Dummy(ImVec2(0, 20));
			// Color filter
			ImGui::Text("Color Filter");
			ImGui::Checkbox("Enable", &editor_colorFilterDir.enable);
			ImGui::InputFloat("Alpha Blend", &editor_colorFilterDir.alphaBlend);
			ImGui::ColorEdit4("Filter Color A", &(editor_colorFilterDir.colorA.x));
			ImGui::ColorEdit4("Filter Color B", &(editor_colorFilterDir.colorB.x));
			ImGui::ColorEdit4("Filter Color C", &(editor_colorFilterDir.colorC.x));
			ImGui::SliderFloat2("Filter Direction", &(editor_colorFilterDir.direction.x), 0, 8);
			ImGui::SliderFloat2("Filter Scale", &(editor_colorFilterDir.scale.x), 0, 10);
			ImGui::SliderFloat("Middle Point", &(editor_colorFilterDir.middlePoint), 0, 1);

			//std::cout << "Filter: " << std::hex << ccGameDrawEnv::nuccColorFilterDirectionalGetPtr(0) << std::endl;

			// Extra shit
			__int64 a = Game::ObjectList_GetPtrLightsAndFog();
			if (a && false)
			{
				if (ImGui::Button("ClearCelShade")) for(int x = 0; x < 6; x++) ccGameDrawEnv::ClearCelShadeParam(a, x);
				if (ImGui::Button("ClearFog")) for (int x = 0; x < 6; x++) ccGameDrawEnv::ClearFogParam(a, x);
				if (ImGui::Button("ClearShadow")) for (int x = 0; x < 6; x++) ccGameDrawEnv::ClearShadowParam(a, x);
				if (ImGui::Button("ClearGlare")) for (int x = 0; x < 6; x++) ccGameDrawEnv::ClearGlareParam(a, x);
				if (ImGui::Button("ClearSoftFocus")) for (int x = 0; x < 6; x++) ccGameDrawEnv::ClearSoftFocusParam(a, x);
				if (ImGui::Button("ClearDoF")) for (int x = 0; x < 6; x++) ccGameDrawEnv::ClearDoFParam(a, x);
				if (ImGui::Button("ClearMotBlur")) for (int x = 0; x < 6; x++) ccGameDrawEnv::ClearMotBlurParam(a, x);
			}

			if (ImGui::Button("Clear Lights"))
			{
				ccGame * ccg = ccGame::GetInstance();
				ccGameDrawEnv::ReleaseLightAll(&(ccg->m_gameDrawEnvInstance));
				std::cout << "Released lights" << std::endl;
			}

			if (ImGui::Button("Test Anm"))
			{
				__int64 obj_ = *(__int64*)(moduleBase + 0x14161C9C0 - 0x140000C00);

				if (obj_)
				{
					__int64 obj2_ = *(__int64*)(obj_ + 160);

					if (obj2_)
					{
						NuccAnm * anm_ = *(NuccAnm**)(obj2_ + 24);

						if (anm_)
						{
							__int64 anmChunk = nuccXfbinDocument::SearchAnm("data/ui/max/modesel/modesel00_r00.xfbin", "modesel_nkb00_ent00");
							NuccAnm::SetAnm(anm_, anmChunk, 0, 0, 0, 0);
						}
						else
						{
							std::cout << "No anm" << std::endl;
						}
					}
					else
					{
						std::cout << "No obj2" << std::endl;
					}
				}
				else
				{
					std::cout << "No obj" << std::endl;
				}
			}

			if (ImGui::Button("Test Anm 2"))
			{
				if (customAnm == nullptr)
				{
					customAnm = (NuccAnm*)(Game::operator_new(0x1C0, "", 0x2C9));
					NuccAnm::nuccAnm((__int64)customAnm);

					__int64 v4 = Game::operator_new(0x30, "", 0x108);
					ccTaskBase::EntryTaskWithAllo11(v4, "Draw", 87, 0, (__int64)(customAnm), (__int64)(void*)(NuccAnm::Draw));

					//__int64 v5 = Game::operator_new(0x30, "", 0x108);
					//ccTaskBase::EntryTaskWithAllo11(v5, "Animate", 87, 0, (__int64)(customAnm), (__int64)(void*)(NuccAnm::Animate));
				}
				
				__int64 anmChunk = nuccXfbinDocument::SearchAnm("data/ui/max/modesel/modesel00_r00.xfbin", "modesel_nkb00_ent00");
				NuccAnm::SetAnm(customAnm, anmChunk, 0, 0, 0, 1);
			}

			if (editor_visibilityEditorShowStageClump == false)
			{
				if (ImGui::Button("Display Stage Models"))
				{
					editor_visibilityEditorShowStageClump = true;
					char * bytes = new char[5]{ (char)0xE8, (char)0xAF, (char)0xB9, (char)0xFF, (char)0xFF };
					Utilities::PasteBytes(moduleBase + 0x813BF8, bytes, 5);
				}
			}
			else
			{
				if (ImGui::Button("Hide Stage Models"))
				{
					editor_visibilityEditorShowStageClump = false;
					Utilities::Nop(moduleBase + 0x813BF8, 5);
				}
			}

			if (editor_visibilityEditorShowStageAnm == false)
			{
				if (ImGui::Button("Display Stage Animations"))
				{
					editor_visibilityEditorShowStageAnm = true;
					char * bytes = new char[5]{ (char)0xE8, (char)0x29, (char)0xAD, (char)0xFF, (char)0xFF };
					Utilities::PasteBytes(moduleBase + 0x813C2A, bytes, 5);
				}
			}
			else
			{
				if (ImGui::Button("Hide Stage Animations"))
				{
					editor_visibilityEditorShowStageAnm = false;
					Utilities::Nop(moduleBase + 0x813C2A, 5);
				}
			}

			ImGui::End();
		}

		// Adventure editor
		if (WindowList[editor_advEditor])
		{
			ImGui::Begin("Misc Editor", &WindowList[editor_advEditor]);

			__int64 plPtr = unnamed::ccGetAdvPlayer();

			std::stringstream plRead;
			plRead << std::hex << std::uppercase << plPtr;
			std::string pltext = "Player : " + plRead.str();
			ImGui::Text(pltext.c_str());

			ImGui::InputText("Battle ID", &editor_advEditor_battleParam);

			if (ImGui::Button("Change Battle By ID"))
			{
				unnamed::ccChangeBattleById(editor_advEditor_battleParam.c_str(), 0);
			}

			ImGui::InputInt("Scene ID", &editor_advEditor_pushScene);
			if (ImGui::Button("Push Scene"))
			{
				__int64 * ab = (__int64*)(moduleBase + 0x1416BDA18 - 0x140000C00);
				//GameUtilities::ccSceneManager_Push(*ab, editor_advEditor_pushScene);
				std::cout << "Pushed scene " << editor_advEditor_pushScene << std::endl;
			}

			if (ImGui::Button("Pop Scene"))
			{
				__int64 * ab = (__int64*)(moduleBase + 0x1416BDA18 - 0x140000C00);
				//GameUtilities::ccSceneManager_Pop(*ab);
				std::cout << "Popped scene " << std::endl;
			}

			if (ImGui::Button("Change Scene"))
			{
				__int64 * ab = (__int64*)(moduleBase + 0x1416BDA18 - 0x140000C00);
				//GameUtilities::ccSceneManager_Change(*ab, editor_advEditor_pushScene);
				std::cout << "Changed scene " << editor_advEditor_pushScene << std::endl;
			}

			ImGui::InputText("GP Char ID", &editor_advEditor_gpSpawnChar);
			ImGui::InputFloat3("GP Spawn Pos", &editor_advEditor_gpSpawnPos.x);
			if (ImGui::Button("Spawnear un pibe"))
			{
				//std::cout << "part 0" << std::endl;
				GameLua::ccPlayerPoolSet(editor_advEditor_gpSpawnChar.c_str(), 10);
				//std::cout << "part 1" << std::endl;
				GameLua::ccEntryReSpawnID(editor_advEditor_gpSpawnChar.c_str(), 1, 0);
				//std::cout << "part 2" << std::endl;
				GameLua::ccEntryGroupBattleChar(editor_advEditor_gpSpawnChar.c_str(), true, true, editor_advEditor_gpSpawnPos.x, editor_advEditor_gpSpawnPos.y, editor_advEditor_gpSpawnPos.z, 0, 1, "", -1);
				//std::cout << "part 3" << std::endl;
			}

			ImGui::End();
		}

		// UI editor
		if (WindowList[editor_uiEditor])
		{
			ImGui::Begin("UI Editor", &WindowList[editor_uiEditor]);

			ImGui::InputText("Sprite Path", &editor_uiEditor_path);
			ImGui::InputText("Sprite Name", &editor_uiEditor_name);
			ImGui::InputInt("Sprite Param", &editor_uiEditor_int);

			if (editor_uiEditor_int < 0) editor_uiEditor_int = 0;

			if (ImGui::Button("Spawn Sprite"))
			{
				ccUiLayoutParts * a = ccUiLayoutParts::CreateSpriteInit(editor_uiEditor_path.c_str(), editor_uiEditor_name.c_str(), editor_uiEditor_int);
				std::cout << "Created" << std::endl;
				ccGameObject::Init(Game::ObjectList_GetInstanceGlobal(), (__int64)a);
				std::cout << std::hex << std::uppercase << a << std::endl;
			}

			if (ImGui::Button("Choice Test"))
			{
				__int64 test = Game::operator_new(0x210, "", 0x147);
				ccUiSelectWindow* v3 = ccUiSelectWindow::CcUiSelectWindow(test, "ccUiFlashSelectWindow_EnterEntryBattle", 0);

				if (v3)
				{
					v6[0] = 0;
					//v7 = "MSG_ConfirmOK";
					v6[1] = 16;
					v6[2] = 64;
					v6[3] = 2;

					ccUiSelectWindow::sub_140B117F0(v3, (__int64)&v7, 2, 0);
					//ccUiSelectWindow::sub_1406A4B94(v3, v6, &v7, 1, 1, -1);
					//ccUiSelectWindow::SetYesNoSelect(v3, "+User Created Stages", 1);
					ccUiSelectList::SetSelect(v3, 0);
					ccUiSelectList::SetSelect(v3, 1);
					ccUiSelectList::PushKeyHelp(v3);
					ccUiSelectList::GetKeyHelp(v3);
				}
			}

			if (ImGui::Button("Reload System Files"))
			{
				std::cout << "Attempting to reload files..." << std::endl;
				ccGameRootStateMachine * instance = ccGameRootStateMachine::GetInstance();
				ccGameRootStateMachine::EnterLoadCmn(instance);

				//ccStageInfoManager * stg = (ccStageInfoManager*)((__int64)(instance)+280);
				//ccStageInfoManager::Create(stg);
				//ccGameRootStateMachine::CreateBtlParam(instance);
				std::cout << "Files reloaded successfully" << std::endl;
			}

			ImGui::End();
		}

		// Scene editor
		if (WindowList[editor_sceneEditor])
		{
			ImGui::Begin("Scene Editor", &WindowList[editor_uiEditor]);

			std::vector<ccStageClump*> objects;

			ccStageManager* stageManager = ccStageManager::GetInstance();
			if (stageManager)
			{
				ccStageObjectManager* stageObjectManager = ccStageObjectManager::GetManager(stageManager);
				if (stageObjectManager)
				{
					//std::cout << "stageObjectManager: " << std::hex << stageObjectManager << std::endl;

					int objectListNum = ccStageObjectManager::GetObjectListNum(stageObjectManager);

					for (int actualList = 0; actualList < objectListNum; actualList++)
					{
						ccStageObjectList* objList = ccStageObjectManager::GetObjectList(stageObjectManager, actualList);

						std::string tempStr = "ClumpList: " + Utilities::HexToString(*(__int64*)&(objList->m_clumpList));
						ImGui::Text(tempStr.c_str());

						//std::cout << "objlist " << std::hex << actualList << ": " << std::hex << objList << std::endl;
						//std::cout << "*vector " << std::hex << actualList << ": " << std::hex << *(__int64*)&(objList->m_clumpList) << std::endl;
						//std::cout << "size: " << std::hex << objList->m_clumpList->size() << std::endl;
						//std::cout << "[0] " << std::hex << actualList << ": " << std::hex << *(__int64*)&(objList->m_clumpList[0]) << std::endl;

						int end = 500;
						unsigned __int64 actualAddress = (unsigned __int64)&(objList->m_clumpList[0]);
						while (*(__int64*)actualAddress < 0xFFFFFFFFFFF && end > 0)
						{
							ccStageClump* c = (ccStageClump*)(*(__int64*)actualAddress);
							if (c) objects.push_back(c);
							actualAddress += 8;
							end--;
						}
					}
				}
				else
				{
					ImGui::Text("No stage object manager");
				}
			}
			else
			{
				ImGui::Text("No stage manager");
			}

			//  Object list
			int objectCount = objects.size();
			if (ImGui::ListBoxHeader("Clumps"))
			{
				for (int x = 0; x < objectCount; x++)
				{
					std::stringstream ptrRead;
					ptrRead << "Container: " << (const char*)&(objects[x]->m_name[0]) << ": " << std::hex << std::uppercase << (__int64)(objects[x]);
					std::string name = ptrRead.str();

					if (ImGui::Selectable(name.c_str(), x == editor_sceneEditor_selected))
					{
						editor_sceneEditor_selected = x;
					}
				}
				ImGui::ListBoxFooter();
			}

			if (editor_sceneEditor_selected >= objectCount) editor_sceneEditor_selected = objectCount - 1;
			if (editor_sceneEditor_selected < -1) editor_sceneEditor_selected = -1;

			// If there's a clump selected
			if (editor_sceneEditor_selected > -1)
			{
				ImGui::Text("Object:");
				ccStageClump * clump = objects[editor_sceneEditor_selected];
				ImGui::Text((const char*)(clump->m_name));

				std::string tempStr = "ccStageClump: " + Utilities::HexToString((__int64)(clump));
				ImGui::Text(tempStr.c_str());

				tempStr = "ccStageBaseClump: " + Utilities::HexToString((__int64)(clump->m_stageBaseClump));
				ImGui::Text(tempStr.c_str());

				tempStr = "NuccClump: " + Utilities::HexToString((__int64)(clump->m_stageBaseClump->m_nuccClump));
				ImGui::Text(tempStr.c_str());

				ImGui::InputInt("Tab (0 = ccStageClump, 1 = BaseClump, 2 = NuccClump", &editor_sceneEditor_actualTab);

				if (editor_sceneEditor_actualTab < 0) editor_sceneEditor_actualTab = 0;
				if (editor_sceneEditor_actualTab > 2) editor_sceneEditor_actualTab = 2;

				ImGui::Dummy(ImVec2(0, 10));

				if (editor_sceneEditor_actualTab == 0)
				{
					ImGui::Text("ccStageClump");
					ImGui::InputInt("m_alwaysUpdate", &(clump->m_alwaysUpdate));
					ImGui::InputInt("m_flag01", &(clump->m_flag01));
					ImGui::InputInt("m_flag02", &(clump->m_flag02));
					ImGui::InputInt("m_flag03", &(clump->m_flag03));
					ImGui::InputInt("m_flag04", &(clump->m_flag04));
					ImGui::InputInt("m_draw", &(clump->m_draw));
					ImGui::InputFloat3("m_vector00", (float*)&(clump->m_vector00));
				}
				else if (editor_sceneEditor_actualTab == 1)
				{
					ccStageBaseClump * baseClump = clump->m_stageBaseClump;
					ImGui::Text("ccStageBaseClump");
					ImGui::InputInt("m_draw", &(baseClump->m_draw));
					ImGui::InputInt("m_flag00", &(baseClump->m_flag00));
					ImGui::InputInt("m_isUpdated", &(baseClump->m_isUpdated));
					ImGui::InputFloat3("m_position", (float*)&(baseClump->m_position));
					ImGui::InputFloat3("m_scale", (float*)&(baseClump->m_scale));
				}
				else if (editor_sceneEditor_actualTab == 2)
				{
					/*NuccClump * nclump = clump->m_stageBaseClump->m_nuccClump;
					ImGui::InputInt("m_isUpdated", &(nclump->m_isUpdated));
					ImGui::InputFloat3("m_position", (float*)&(nclump->m_position));
					ImGui::InputFloat3("m_scale", (float*)&(nclump->m_scale));*/
					//ImGui::InputFloat3("m_position", (float*)&(nclump->m_position));
					//ImGui::InputFloat3("m_scale", (float*)&(nclump->m_scale));
				}
			}

			ImGui::End();
		}
	}

	// Set fog
	if(editor_renderEditor_enableChanges) FrameworkHelpers::SetFog(editor_renderEditorColor.x, editor_renderEditorColor.y, editor_renderEditorColor.z, editor_renderEditorParams.x, editor_renderEditorParams.y, editor_renderEditorParams.z);

	// Set color filter
	__int64 cfptr = Game::ObjectList_GetPtrLightsAndFog();
	if(editor_renderEditor_enableChanges) ColorFilterDirectionalSettings::SetSettings(cfptr, &editor_colorFilterDir);

	Vector3 newPos = Vector3(editor_cameraWindowPos[0], editor_cameraWindowPos[1], editor_cameraWindowPos[2]);

	switch (editor_cameraWindowMode)
	{
		default:
		{
			if (camPtr && editor_cameraWindowEnableCam == false)
			{
				if (Editor::MouseLook::instance == nullptr) Editor::MouseLook::instance = new Editor::MouseLook();
				Editor::MouseLook::instance->Update((HWND)(hwnd));

				// 24, 28, 32
				Vector3 * look = &(camPtr->m_look);
				Vector3 forward = Editor::MouseLook::instance->CalculateLookPoint();
				Vector3 right = Vector3(forward.y, forward.x, forward.z);

				float camSpeed = 8;
				if (GetAsyncKeyState(VK_SHIFT)) camSpeed = 16;

				if (GetAsyncKeyState('W')) newPos = newPos + (forward.Normalize() * camSpeed);
				if (GetAsyncKeyState('S')) newPos = newPos - (forward.Normalize() * camSpeed);
				//if (GetAsyncKeyState('A')) newPos = newPos - (right.Normalize() * camSpeed);
				//if (GetAsyncKeyState('D')) newPos = newPos + (right.Normalize() * camSpeed);

				*look = (newPos)+(forward * 5);

				ccCmnCamera::SetCameraPosNew(camPtr, &newPos);

				camPtr->m_internalPosX = newPos.x;
				camPtr->m_internalPosY = newPos.y;
				camPtr->m_internalPosZ = newPos.z;

				camPtr->m_fov = 90;
				camPtr->m_tilt_unk = 0;
				camPtr->m_tilt = Vector3(0, 1, 0.01);

				ccCmnCamera::Update(camPtr);

				/*float * fov = (float*)((__int64)(camPtr)+44);
				*fov = 90;

				*((float*)(((__int64)camPtr) + 140)) = 0;
				*((float*)(((__int64)camPtr) + 144)) = 2;
				*((float*)(((__int64)camPtr) + 148)) = 0.01;*/
			}
			break;
		}
		case 1:
		{
			ccPlayerMain* pl = BattleUtils::ccGame_GetPlayerLeader(0);

			if (pl)
			{
				Vector3* plPos = (Vector3*)((__int64)(pl) + 112);
				Vector3 * look = &(camPtr->m_look);
				*look = *plPos + editor_cameraWindowPlLookOffset;

				// editor_cameraWindowPlAngle
				if (controller.Gamepad.sThumbLX)
				{

				}

				if (GetAsyncKeyState('Z') || controller.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) editor_cameraWindowPlAngle = editor_cameraWindowPlAngle - (0.03);
				if (GetAsyncKeyState('C') || controller.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) editor_cameraWindowPlAngle = editor_cameraWindowPlAngle + (0.03);

				float xinputh = controller.Gamepad.sThumbRX / 32767;
				if (xinputh < -0.2 || xinputh > 0.2) editor_cameraWindowPlAngle = editor_cameraWindowPlAngle + (xinputh / 50);

				Vector3 calculatedPos = *plPos + Vector3(editor_cameraWindowPlDistance * sinf(editor_cameraWindowPlAngle), editor_cameraWindowPlDistance * cosf(editor_cameraWindowPlAngle), editor_cameraWindowPlHeight);

				ccCmnCamera::SetCameraPosNew(camPtr, &calculatedPos);

				camPtr->m_fov = 90;
				camPtr->m_tilt_unk = 0;
				camPtr->m_tilt = Vector3(0, 1, 0.01);

				//*((float*)(((__int64)camPtr) + 136)) = 0;
				//*((float*)(((__int64)camPtr) + 140)) = 0;
				//*((float*)(((__int64)camPtr) + 144)) = 2;
				//*((float*)(((__int64)camPtr) + 148)) = 0.01;
			}
			break;
		}
	}
}

__int64 EditorGUI::LoadHelperEditor(const char* path, bool isGizmo)
{
	__int64 result = 0;
	
	// check if it was loaded previously
	result = IsLoaded(path);
	if (result) return result;

	result = nuccFileLoadList::LoadHelper(0, path);

	// Check if loaded
	int timeout = 600;
	int isFileLoaded = -1;
	bool found = false;

	while (timeout > 0 && !found)
	{
		found = (nuccXfbinDocManager::GetXfbinLoadState(path) == 2);
		timeout--;
		Sleep(1);
	}

	if (found)
	{
		nuccFileLoadList::loadStruct * loadPtr = new nuccFileLoadList::loadStruct(path, (nuccFileLoadList*)result);

		if (isGizmo == false) loadList.push_back(loadPtr);
		else gizmoLoadList.push_back(loadPtr);

		std::cout << "Result = " << std::hex << std::uppercase << result << std::endl;
	}
	else
	{
		std::cout << "Error loading file " << path << std::endl;
		result = 0;
	}

	return result;
}

__int64 EditorGUI::IsLoaded(const char* path)
{
	std::string p_str = std::string(path);
	__int64 found = 0;

	for (int x = 0; x < loadList.size(); x++)
	{
		std::string comparePath = std::string(loadList[x]->path);
		if (comparePath == p_str)
		{
			found = (__int64)(loadList[x]->ptr);
			x = loadList.size();
		}
	}

	return found;
}

void EditorGUI::DeleteObject(int index)
{
	Editor::EditorBase * e = Editor::EditorBase::GetInstance();
	if (index >= e->editorObjectList.size()) return;

	ccStageClump * clump = e->editorObjectList[index]->clump;
	ccStageAnm * anm = e->editorObjectList[index]->anmclump;

	if (clump && !anm)
	{
		ccStageObjectList::DeleteClump(FrameworkHelpers::GetStageObjectListGlobal(), clump);
	}
	else
	{
		ccStageObjectList::DeleteAnm(FrameworkHelpers::GetStageObjectListGlobal(), anm);
	}

	e->editorObjectList[index] = 0;

	std::cout << "Deleted object at " << index << std::endl;
}

void EditorGUI::CreateGizmo()
{
	ccStageObjectList * objectList = FrameworkHelpers::GetStageObjectListGlobal();
	Editor::EditorObject * arrows = GameObjectCreator::CreateObjectWithMesh(objectList, "data/editor/gizmo_arrow.xfbin", "gizmoeditor_arw", false, true);
	arrows->name = "gizmo_arrow";

	if (arrows)
	{
		Editor::Animation * gzm_anm = new Editor::Animation();
		gzm_anm->AddAnimationPoint(Editor::AnimationPoint(Vector3(0, 0, 0), Vector3(1, 1, 1)));
		gzm_anm->AddAnimationPoint(Editor::AnimationPoint(Vector3(0, 0, 0), Vector3(1.25, 1.25, 1.25)));
		ccStageClump * actualClump = arrows->clump;
		gzm_anm->SetClump(actualClump);
		gzm_anm->SetAnimationNextFrame();
		arrows->AddComponent(gzm_anm);
	}
}

void EditorGUI::ClearStage(bool deleteGlobals)
{
	ccStageObjectList* objList = FrameworkHelpers::GetStageObjectListGlobal();
	Editor::EditorBase* e = Editor::EditorBase::GetInstance();

	if (objList)
	{
		ccStageObjectList::Clear(objList);
		e->editorObjectList.clear();
		e->gizmoList.clear();
	}
}

void EditorGUI::SaveStage()
{
	Editor::EditorBase * e = Editor::EditorBase::GetInstance();

	std::vector<BYTE> actual;
	actual = FileParser::b_AddString(actual, "ZM01"); // version

	// Save loaded files
	int fileCount = loadList.size();
	actual = FileParser::b_AddInt(actual, fileCount);
	for (int x = 0; x < fileCount; x++)
	{
		nuccFileLoadList::loadStruct* l = loadList[x];
		actual = FileParser::b_AddInt(actual, l->path.length());
		actual = FileParser::b_AddString(actual, l->path);
	}

	actual = FileParser::b_AddInt(actual, e->editorObjectList.size());
	int objCount = e->editorObjectList.size();
	for (int x = 0; x < objCount; x++)
	{
		Editor::EditorObject * thisObject = e->editorObjectList[x];

		// save name
		actual = FileParser::b_AddInt(actual, thisObject->name.length());
		actual = FileParser::b_AddString(actual, thisObject->name);

		// save path
		actual = FileParser::b_AddInt(actual, thisObject->path.length());
		actual = FileParser::b_AddString(actual, thisObject->path);

		// save mesh
		actual = FileParser::b_AddInt(actual, thisObject->mesh.length());
		actual = FileParser::b_AddString(actual, thisObject->mesh);

		// save pos
		actual = FileParser::b_AddFloat(actual, thisObject->position.x);
		actual = FileParser::b_AddFloat(actual, thisObject->position.y);
		actual = FileParser::b_AddFloat(actual, thisObject->position.z);

		// save scale
		actual = FileParser::b_AddFloat(actual, thisObject->scale.x);
		actual = FileParser::b_AddFloat(actual, thisObject->scale.y);
		actual = FileParser::b_AddFloat(actual, thisObject->scale.z);

		// save type
		if (thisObject->anmclump != nullptr) actual = FileParser::b_AddInt(actual, 1);
		else actual = FileParser::b_AddInt(actual, 0);

		// save components
		actual = FileParser::b_AddInt(actual, thisObject->components.size());
		
		for (int c = 0; c < thisObject->components.size(); c++)
		{
			Editor::Component * comp = thisObject->components[c];
			actual = FileParser::b_AddInt(actual, comp->componentType);
			
			if (comp->componentType == Editor::Component::Types::ScriptedObject) // save script
			{
				Editor::ScriptedObject * scripted = (Editor::ScriptedObject*)comp;
				actual = FileParser::b_AddInt(actual, scripted->script.length());
				actual = FileParser::b_AddString(actual, scripted->script);
			}
			else if (comp->componentType == Editor::Component::Types::Animation) // save anm
			{
				Editor::Animation * anm = (Editor::Animation*)comp;
				actual = FileParser::b_AddInt(actual, int(anm->legacyMode));
				actual = FileParser::b_AddFloat(actual, anm->lerpSpeed);
				
				actual = FileParser::b_AddInt(actual, anm->animationPoints.size());
				for (int anmPoint = 0; anmPoint < anm->animationPoints.size(); anmPoint++)
				{
					Editor::AnimationPoint point = anm->animationPoints[anmPoint];
					actual = FileParser::b_AddVector3(actual, point.position);
					actual = FileParser::b_AddVector3(actual, point.scale);
				}
			}
		}
	}

	try
	{
		FileParser::WriteAllBytes(editor_spawnSaveStagePath, actual);
		std::cout << "Saved file to " << editor_spawnSaveStagePath << std::endl;
	}
	catch (char* msg)
	{
		std::cout << "Error saving file" << std::endl;
	}
}

void EditorGUI::LoadStage(std::string path)
{
	try
	{
		std::vector<BYTE> actual = FileParser::ReadAllBytes(path);
		int index = 4;
		std::string fileVersion = FileParser::b_ReadString(actual, 0, 4);

		if (fileVersion == "ZM00")
		{
			return LoadStage00(actual);
		}
		else if (fileVersion == "ZM01")
		{
			return LoadStage01(actual);
		}
	}
	catch (char* msg)
	{
		std::cout << "Error loading stage: " << editor_spawnSaveStagePath << std::endl;
	}
}

void EditorGUI::LoadStage00(std::vector<BYTE> actual)
{
	ccStageObjectList * objectList = FrameworkHelpers::GetStageObjectListGlobal();
	int index = 4;

	int objCount = FileParser::b_ReadInt(actual, index);
	index += 4;

	for (int x = 0; x < objCount; x++)
	{
		int nameLen = FileParser::b_ReadInt(actual, index);
		index += 4;
		std::string name = FileParser::b_ReadString(actual, index, nameLen);
		index += nameLen;

		int pathLen = FileParser::b_ReadInt(actual, index);
		index += 4;
		std::string path = FileParser::b_ReadString(actual, index, pathLen);
		index += pathLen;

		int meshLen = FileParser::b_ReadInt(actual, index);
		index += 4;
		std::string mesh = FileParser::b_ReadString(actual, index, meshLen);
		index += meshLen;

		float posx = FileParser::b_ReadFloat(actual, index);
		index += 4;
		float posy = FileParser::b_ReadFloat(actual, index);
		index += 4;
		float posz = FileParser::b_ReadFloat(actual, index);
		index += 4;
		Vector3 position = Vector3(posx, posy, posz);

		float scalex = FileParser::b_ReadFloat(actual, index);
		index += 4;
		float scaley = FileParser::b_ReadFloat(actual, index);
		index += 4;
		float scalez = FileParser::b_ReadFloat(actual, index);
		index += 4;
		Vector3 scale = Vector3(scalex, scaley, scalez);

		const char* path_c = path.c_str();
		const char* mesh_c = mesh.c_str();
		__int64 r = LoadHelperEditor(path_c);

		bool found = r;

		if (found)
		{
			bool canCreate = FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkClump, path_c, mesh_c) ||
				FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkModelHit, path_c, mesh_c) ||
				FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkModel, path_c, mesh_c);

			if (canCreate)
			{
				Editor::EditorBase * e = Editor::EditorBase::GetInstance();

				if (e->editorObjectList.size() == 0)
				{
					__int64 r = LoadHelperEditor("data/editor/gizmo_arrow.xfbin", true);
					if (r) CreateGizmo();
				}

				Editor::EditorObject * eObj = GameObjectCreator::CreateObjectWithMesh(objectList, path.c_str(), mesh.c_str(), false);
				if (eObj != nullptr)
				{
					ccStageObjectList::AddCollision(FrameworkHelpers::GetStageObjectListGlobal(), eObj->clump);

					ccStageClump::SetPosition(eObj->clump, &position);
					ccStageClump::SetScale(eObj->clump, &scale);
					eObj->position = position;
				}
			}
			else
			{
				std::cout << "Skipping " << name << " (error in file)" << std::endl;
			}
		}
		else
		{
			std::cout << "Could not load file " << path << " - Skipping" << std::endl;
		}
	}
}

void EditorGUI::LoadStage01(std::vector<BYTE> actual) // + components
{
	ccStageObjectList * objectList = FrameworkHelpers::GetStageObjectListGlobal();
	int index = 4;

	int fileCount = FileParser::b_ReadInt(actual, index);
	index += 4;
	for (int x = 0; x < fileCount; x++)
	{
		int pathLen = FileParser::b_ReadInt(actual, index);
		index += 4;

		std::string thisPath = FileParser::b_ReadString(actual, index, pathLen);
		index += pathLen;

		__int64 r = LoadHelperEditor(thisPath.c_str());
	}

	int objCount = FileParser::b_ReadInt(actual, index);
	index += 4;

	for (int x = 0; x < objCount; x++)
	{
		int nameLen = FileParser::b_ReadInt(actual, index);
		index += 4;
		std::string name = FileParser::b_ReadString(actual, index, nameLen);
		index += nameLen;

		int pathLen = FileParser::b_ReadInt(actual, index);
		index += 4;
		std::string path = FileParser::b_ReadString(actual, index, pathLen);
		index += pathLen;

		int meshLen = FileParser::b_ReadInt(actual, index);
		index += 4;
		std::string mesh = FileParser::b_ReadString(actual, index, meshLen);
		index += meshLen;

		float posx = FileParser::b_ReadFloat(actual, index);
		index += 4;
		float posy = FileParser::b_ReadFloat(actual, index);
		index += 4;
		float posz = FileParser::b_ReadFloat(actual, index);
		index += 4;
		Vector3 position = Vector3(posx, posy, posz);

		float scalex = FileParser::b_ReadFloat(actual, index);
		index += 4;
		float scaley = FileParser::b_ReadFloat(actual, index);
		index += 4;
		float scalez = FileParser::b_ReadFloat(actual, index);
		index += 4;
		Vector3 scale = Vector3(scalex, scaley, scalez);

		// Read objectType
		int objectType = FileParser::b_ReadInt(actual, index);
		bool isAnm = objectType == 1;
		index += 4;

		// Read components
		int componentCount = FileParser::b_ReadInt(actual, index);
		std::vector<Editor::Component*> componentList;
		index += 4;

		for (int y = 0; y < componentCount; y++)
		{
			Editor::Component::Types componentType = (Editor::Component::Types)(FileParser::b_ReadInt(actual, index));
			index += 4;

			if (componentType == Editor::Component::Types::ScriptedObject)
			{
				int scriptLen = FileParser::b_ReadInt(actual, index);
				index += 4;

				std::string script = FileParser::b_ReadString(actual, index, scriptLen);
				index += scriptLen;

				Editor::ScriptedObject * comp = new Editor::ScriptedObject();
				comp->script = script;

				componentList.push_back(comp);
			}
			else if (componentType == Editor::Component::Types::Animation)
			{
				Editor::Animation * anm = new Editor::Animation();

				int legacyMode = FileParser::b_ReadInt(actual, index);
				index += 4;
				anm->legacyMode = bool(legacyMode);

				float lerpSpeed = FileParser::b_ReadFloat(actual, index);
				index += 4;
				anm->lerpSpeed = lerpSpeed;

				int pointCount = FileParser::b_ReadInt(actual, index);
				index += 4;

				for (int z = 0; z < pointCount; z++)
				{
					Vector3 pointPos = FileParser::b_ReadVector3(actual, index);
					index += 12;

					Vector3 pointScale = FileParser::b_ReadVector3(actual, index);
					index += 12;

					Editor::AnimationPoint anmPointActual = Editor::AnimationPoint(pointPos, pointScale);
					anm->AddAnimationPoint(anmPointActual);
				}

				componentList.push_back(anm);
			}
		}

		const char* path_c = path.c_str();
		const char* mesh_c = mesh.c_str();
		__int64 r = LoadHelperEditor(path_c);

		bool found = r;

		if (found)
		{
			bool canCreate = false;

			if (isAnm == false)
			{
				canCreate = FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkClump, path_c, mesh_c) ||
					FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkModelHit, path_c, mesh_c) ||
					FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkModel, path_c, mesh_c);
			}
			else if (isAnm)
			{
				canCreate = FrameworkHelpers::FindNuccChunk(nuccChunkTypes::nuccChunkAnm, path_c, mesh_c);
			}

			if (canCreate)
			{
				Editor::EditorBase * e = Editor::EditorBase::GetInstance();

				if (e->editorObjectList.size() == 0)
				{
					__int64 r = LoadHelperEditor("data/editor/gizmo_arrow.xfbin", true);
					if (r) CreateGizmo();
				}

				Editor::EditorObject * eObj = GameObjectCreator::CreateObjectWithMesh(objectList, path.c_str(), mesh.c_str(), isAnm);
				if (eObj != nullptr)
				{
					eObj->name = name;

					if (isAnm == false)
					{
						ccStageObjectList::AddCollision(FrameworkHelpers::GetStageObjectListGlobal(), eObj->clump);
						ccStageClump::SetPosition(eObj->clump, &position);
						ccStageClump::SetScale(eObj->clump, &scale);
						eObj->position = position;
						eObj->scale = scale;
					}
					else
					{
						eObj->anmclump = (ccStageAnm*)(eObj->clump);
						eObj->clump = 0;

						((nuccAnimParams*)(eObj->anmclump))->SetPosition(position);
						((nuccAnimParams*)(eObj->anmclump))->SetPosition(scale);
						eObj->position = position;
						eObj->scale = scale;

						((nuccAnimParams*)(eObj->anmclump))->Update();
					}

					for (int z = 0; z < componentList.size(); z++)
					{
						eObj->AddComponent(componentList[z]);
					}
				}
			}
			else
			{
				std::cout << "Skipping " << name << " (error in file)" << std::endl;
			}
		}
		else
		{
			std::cout << "Could not load file " << path << " - Skipping" << std::endl;
		}
	}
}