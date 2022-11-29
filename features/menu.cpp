#include "menu.h"
#include "variables.h"

void menu::Setup(IDirect3DDevice9* device) noexcept
{
	if (!dxSetup)
	{
		ImGui::CreateContext();

		ImGui_ImplWin32_Init(FindWindowA("Valve001", nullptr));
		ImGui_ImplDX9_Init(device);

		// textures, fonts, etc...

		dxSetup = true;
	}
}

void menu::Render() noexcept
{
	if (!IsOpen()) 
		return;

	ImGui::Begin("misc");
	{
		ImGui::Checkbox("bunnyhop", &variables::misc::bunnyHop);
	}
	ImGui::End();

	ImGui::Begin("players");
	{

	}
	ImGui::End();

	ImGui::Begin("world");
	{

	}
	ImGui::End();

	ImGui::Begin("screen");
	{
		ImGui::Checkbox("show debug info", &variables::screen::debugInfo);
	}
	ImGui::End();
}

void menu::Press() noexcept
{
	guiOpen = !guiOpen;
}

bool menu::IsOpen() noexcept
{
	return guiOpen;
}