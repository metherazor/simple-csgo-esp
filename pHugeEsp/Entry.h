#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>

template<typename Function>
Function call_vfunc(void* Base, int Index) {
	return (Function)((*(DWORD**)Base)[Index]);
}

DWORD hkFunc(void* vTable, void* hkFunc, int index) {
	//get own pls ty
}

#include "Interfaces.h"
#include "PaintTraverse.h"