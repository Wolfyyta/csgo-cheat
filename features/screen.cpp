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
			drawList->AddText(ImVec2(10, 50), ImColor(255, 255, 255, 255), "CLocalPlayer is 0");
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

	if (variables::players::boxEsp && globals::local)
	{
		for (int i = 0; i < interfaces::globals->maxClients; i++)
		{
			CEntity* ent = interfaces::entityList->GetEntityFromIndex(i);

			if (!ent)
				continue;

			if (!ent->IsAlive())
				return;

			if (globals::local->GetTeam() == ent->GetTeam())
				continue;

			CVector min, max;
			if (!utils::GetBBox(ent, min, max))
				continue;

			int x = min.x;
			int y = min.y;
			int w = max.x - min.x;
			int h = max.y - min.y;

			interfaces::surface->DrawSetColor(255, 255, 255, 255);
			interfaces::surface->DrawOutlinedRect(x, y, w, h);
		}
	}
}
