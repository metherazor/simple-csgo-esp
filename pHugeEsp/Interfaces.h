struct player_info_s {
	char __pad1[0x10];
	char name[32];
	char __pad2[0x64];
	char guid[32 + 1];
	char __pad3[0x17B];
};

class Vector {
public:
	Vector() {

	}
	Vector(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float x, y, z;
};

class CBaseEntity {
public:
	int getHealth() {
		return *(int*)((DWORD)this + 0xFC);
	}
	const Vector& getOrigin() {
		typedef const Vector&(__thiscall* oFn)(void*);
		return call_vfunc<oFn>(this, 10)(this);
	}
	bool isDormant() {
		typedef bool(__thiscall* oFn)(void*);
		return call_vfunc<oFn>(this->getNetworkable(), 9)(this->getNetworkable());
	}
	void* getNetworkable() {
		return (void*)((DWORD)this + 0x8);
	}
	int getTeam() {
		return *(int*)((DWORD)this + 0xF0);
	}
};

class IVEngineClient {
public:
	int GetLocalPlayer() {
		typedef int(__thiscall* oFn)(void*);
		return call_vfunc<oFn>(this, 12)(this);
	}
	bool IsInGame() {
		typedef bool(__thiscall* oFn)(void*);
		return call_vfunc<oFn>(this, 26)(this);
	}
	bool getPlayerInfo(int index, player_info_s* player_info) {
		typedef bool(__thiscall* oFn)(void*, int, player_info_s*);
		return call_vfunc<oFn>(this, 8)(this, index, player_info);
	}
};

class ISurface {
public:
	void DrawSetColor(int r, int g, int b, int a = 255) {
		typedef void(__thiscall* oFn)(void*, int, int, int, int);
		return call_vfunc<oFn>(this, 15)(this, r, g, b, a);
	}
	void DrawLine(int x1, int y1, int x2, int y2) {
		typedef void(__thiscall* oFn)(void*, int, int, int, int);
		return call_vfunc<oFn>(this, 19)(this, x1, y1, x2, y2);
	}
	void DrawSetTextFont(unsigned long font) {
		typedef void(__thiscall* oFn)(void*, unsigned long);
		return call_vfunc<oFn>(this, 23)(this, font);
	}
	void DrawSetTextColor(int r, int g, int b, int a = 255) {
		typedef void(__thiscall* oFn)(void*, int, int, int, int);
		return call_vfunc<oFn>(this, 25)(this, r, g, b, a);
	}
	void DrawSetTextPos(int x, int y) {
		typedef void(__thiscall* oFn)(void*, int, int);
		return call_vfunc<oFn>(this, 26)(this, x, y);
	}
	void DrawPrintText(const wchar_t* text, int len) {
		typedef void(__thiscall* oFn)(void*, const wchar_t*, int, int);
		return call_vfunc<oFn>(this, 28)(this, text, len, 0);
	}
	unsigned long CreateFont() {
		typedef unsigned long(__thiscall* oFn)(void*);
		return call_vfunc<oFn>(this, 71)(this);
	}
	bool SetFontGlyphSet(unsigned long font, const char* fontn, int tall, int weight, int blur, int scanlines, int flags) {
		typedef bool(__thiscall* oFn)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
		return call_vfunc<oFn>(this, 72)(this, font, fontn, tall, weight, blur, scanlines, flags, 0, 0);
	}
};

class IPanel {
public:
	const char* GetName(unsigned int Panel) {
		typedef const char*(__thiscall* oFn)(void*, unsigned int);
		return call_vfunc<oFn>(this, 36)(this, Panel);
	}
};

class IVDebugOverlay {
public:
	int ScreenPosition(const Vector& point, Vector& screen) {
		typedef int(__thiscall* oFn)(void*, const Vector&, Vector&);
		return call_vfunc<oFn>(this, 13)(this, point, screen);
	}
};

class CClientEntityList {
public:
	CBaseEntity* GetClientEntity(int index) {
		typedef CBaseEntity*(__thiscall* oFn)(void*, int);
		return call_vfunc<oFn>(this, 3)(this, index);
	}
	int GetHighestEntityIndex() {
		typedef int(__thiscall* oFn)(void*);
		return call_vfunc<oFn>(this, 6)(this);
	}
};

class CInterfaces {
public:
	ISurface* Surface;
	IPanel* Panel;
	IVEngineClient* Engine;
	IVDebugOverlay* DebugOverlay;
	CClientEntityList* EntList;
}; CInterfaces Interfaces;

bool WorldToScreen(const Vector& point, Vector& screen) {
	return(Interfaces.DebugOverlay->ScreenPosition(point, screen) != 1);
}