#include "Entry.h"

typedef void*(*CreateInterfaceFn)(const char*, int);


void main() {
	CreateInterfaceFn engineFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
	CreateInterfaceFn vguiFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("vguimatsurface.dll"), "CreateInterface");
	CreateInterfaceFn panelFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("vgui2.dll"), "CreateInterface");
	CreateInterfaceFn clientFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface");

	Interfaces.Engine = (IVEngineClient*)engineFactory("VEngineClient013", 0);
	Interfaces.DebugOverlay = (IVDebugOverlay*)engineFactory("VDebugOverlay004", 0);
	
	Interfaces.Surface = (ISurface*)vguiFactory("VGUI_Surface031", 0);

	Interfaces.Panel = (IPanel*)panelFactory("VGUI_Panel009", 0);

	Interfaces.EntList = (CClientEntityList*)clientFactory("VClientEntityList003", 0);

	oPaintTraverse = (PaintTraverseFn)hkFunc(Interfaces.Panel, hkPaintTraverse, 41);
}

int __stdcall DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
	return 1;
}