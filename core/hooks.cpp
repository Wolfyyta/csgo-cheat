#include <intrin.h>

#include "hooks.h"
#include "../utils/minhook/minhook.h"

#include "../features/menu.h"
#include "../features/misc.h"
#include "../features/screen.h"

#include "../globals.h"
#include "../features/variables.h"

LONG  __stdcall hooks::EndScene(IDirect3DDevice9* device) noexcept
{
	static const auto retAddr = _ReturnAddress();
	const auto result = EndSceneOriginal(device, device);

	if (_ReturnAddress() == retAddr)
		return result;

	menu::Setup(device);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	screen::DrawOnScreen(ImGui::GetBackgroundDrawList());
	menu::Render();

	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(device, device, params);
	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}

WNDPROC oldWindow = reinterpret_cast<WNDPROC>(SetWindowLongPtr(FindWindowA("Valve001", nullptr), GWL_WNDPROC, reinterpret_cast<LONG_PTR>(hooks::WndProcess)));
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall hooks::WndProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(GUI_KEY) & 1)
		menu::Press();

	if (menu::IsOpen() && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return 1L;

	return CallWindowProc(oldWindow, hWnd, uMsg, wParam, lParam);
}

bool __stdcall hooks::CreateMove(float frameTime, CUserCmd* cmd) noexcept
{
	const auto result = CreateMoveOriginal(interfaces::clientMode, frameTime, cmd);
	if (!cmd || !cmd->commandNumber)
		return result;

	globals::local = interfaces::entityList->GetEntityFromIndex(interfaces::engine->GetLocalPlayerIndex());
	globals::cmd = cmd;

	if (globals::local && globals::local->IsAlive())
	{
		misc::BunnyHop(cmd);
	}

	return false;
}

void __stdcall hooks::PaintTraverse(unsigned int panel, bool forceRepaint, bool allowForce)
{
	if (strstr("HudZoom", interfaces::panel->GetName(panel)) && variables::screen::removeScope)
		return;

	PaintTraverseOriginal(interfaces::panel, panel, forceRepaint, allowForce);
}

float __stdcall hooks::GetViewModelFOV()
{
	if (!globals::local)
		return GetViewModelFOVOriginal(interfaces::clientMode);

	if (globals::local->IsScoped())
		return GetViewModelFOVOriginal(interfaces::clientMode);

	return GetViewModelFOVOriginal(interfaces::clientMode) + variables::world::viewmodelFov;
}

void hooks::SetupHooks()
{
	MH_Initialize();
	{
		MH_CreateHook(utils::Get(interfaces::device, 42), &EndScene, reinterpret_cast<void**>(&EndSceneOriginal));
		MH_CreateHook(utils::Get(interfaces::device, 16), &Reset, reinterpret_cast<void**>(&ResetOriginal));
		MH_CreateHook(utils::Get(interfaces::clientMode, 24), &CreateMove, reinterpret_cast<void**>(&CreateMoveOriginal));
		MH_CreateHook(utils::Get(interfaces::panel, 41), &PaintTraverse, reinterpret_cast<void**>(&PaintTraverseOriginal));
		MH_CreateHook(utils::Get(interfaces::clientMode, 35), &GetViewModelFOV, reinterpret_cast<void**>(&GetViewModelFOVOriginal));
	}
	MH_EnableHook(MH_ALL_HOOKS);
}