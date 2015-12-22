typedef void(__thiscall* PaintTraverseFn)(void*, unsigned int, bool, bool);

PaintTraverseFn oPaintTraverse;

void DrawOutlinedRect(int x, int y, int w, int h, int r, int g, int b, int a = 255) {
	Interfaces.Surface->DrawSetColor(r, g, b, a);
	Interfaces.Surface->DrawLine(x, y, x, y + h);
	Interfaces.Surface->DrawLine(x, y + h, x + w, y + h);
	Interfaces.Surface->DrawLine(x + w, y + h, x + w, y);
	Interfaces.Surface->DrawLine(x + w, y, x, y);
}

void DrawString(const char* text, unsigned int font, int x, int y, int r, int g, int b, int a = 255) {
	wchar_t *pszStringWide = (wchar_t*)(malloc((strlen(text) + 1) * sizeof(wchar_t)));
	mbstowcs(pszStringWide, text, (strlen(text) + 1) * sizeof(wchar_t));
	Interfaces.Surface->DrawSetTextColor(r, g, b, a);
	Interfaces.Surface->DrawSetTextFont(font);
	Interfaces.Surface->DrawSetTextPos(x, y);
	Interfaces.Surface->DrawPrintText(pszStringWide, (int)wcslen(pszStringWide));
	free(pszStringWide);
}

void __fastcall hkPaintTraverse(void* pThis, void*, unsigned int Panel, bool forceRepaint, bool allowForce) {
	oPaintTraverse(pThis, Panel, forceRepaint, allowForce);

	static unsigned int pPanel;
	static unsigned long Font;
	static bool setupDone;

	if (pPanel == Panel || strstr(Interfaces.Panel->GetName(Panel), "FocusOverlayPanel")) {

		if (!setupDone) {
			Font = Interfaces.Surface->CreateFontW();
			Interfaces.Surface->SetFontGlyphSet(Font, "Courier New", 14, 500, 0, 0, 128);
			pPanel = Panel;
			setupDone = true;
		}

		if (!Interfaces.Engine->IsInGame())
			return;

		int local = Interfaces.Engine->GetLocalPlayer();

		for (int i = 0; i < Interfaces.EntList->GetHighestEntityIndex(); i++) {
			if (i == local)
				continue;

			CBaseEntity* ply = Interfaces.EntList->GetClientEntity(i);

			if (ply == NULL)
				continue;

			int team = ply->getTeam();

			player_info_s playerInfo;

			if (ply->isDormant() || ply->getHealth() < 1 || (team != 3 && team != 2) || !Interfaces.Engine->getPlayerInfo(i, &playerInfo))
				continue;

			Vector vPos, vPos2;

			vPos = ply->getOrigin();
			vPos2 = vPos;
			vPos2.z += 70.f;

			Vector vScreen, vScreen2;

			if (WorldToScreen(vPos, vScreen) && WorldToScreen(vPos2, vScreen2)) {
				
				int h = vScreen2.y - vScreen.y;
				int w = h / 2;

				DrawOutlinedRect(vScreen.x - w / 2, vScreen.y, w, h, (team == 2) ? 255 : 0, 0, (team == 2) ? 0 : 255);
				DrawOutlinedRect(vScreen.x - w / 2 + 1, vScreen.y + 1, w - 2, h - 2, 0, 0, 0);
				DrawOutlinedRect(vScreen.x - w / 2 - 1, vScreen.y - 1, w + 2, h + 2, 0, 0, 0);

				DrawString(playerInfo.name, Font, vScreen.x - w / 2 + 5, vScreen.y + h - 3, 220, 220, 220);
			}

		}

	}
}