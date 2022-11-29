#include "screen.h"
#include "variables.h"
#include "../globals.h"

void screen::DrawOnScreen(ImDrawList* drawList)
{
	if (variables::screen::debugInfo)
	{
		auto cmd = globals::cmd;
		auto local = globals::local;

		if (local)
		{
			drawList->AddText(ImVec2(10, 50), ImColor(255, 255, 255, 255), "CLocalPlayer is valid");
		}
		else
		{
			drawList->AddText(ImVec2(10, 10), ImColor(255, 255, 255, 255), "CLocalPlayer is 0");
		}

		if (cmd)
		{
			drawList->AddText(ImVec2(10, 10), ImColor(255, 255, 255, 255), "CUserCmd is valid");
		}
		else
		{
			drawList->AddText(ImVec2(10, 10), ImColor(255, 255, 255, 255), "CUserCmd is 0");
		}
	}
}
