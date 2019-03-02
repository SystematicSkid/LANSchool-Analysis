#include "lanschool.h"

void Init()
{
	// Create debug console for output
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	if (!Internal::addresses.Init())
		MessageBoxA(NULL, "Addresses: Failed to initialize.", NULL, NULL);
	if (!Internal::hooks.Init())
		MessageBoxA(NULL, "Hooks: Failed to initialize.", NULL, NULL);
}

DWORD __stdcall DllMain(HMODULE dll, DWORD callreason, void* reserved)
{
	if (callreason == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Init, NULL, NULL, NULL);
		return 1;
	}

	return 0;
}
