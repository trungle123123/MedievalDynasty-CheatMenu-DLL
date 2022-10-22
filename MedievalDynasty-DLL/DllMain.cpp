#define WIN32_LEAN_AND_MEAN
#include "DllMain.h"
#include "Project.h"

#include <process.h>
#include <stdio.h>
#include <process.h>
#include <filesystem>
#include <Windows.h>

HMODULE hDll = 0;
HMODULE mHinstDLL;
extern "C" UINT_PTR mProcs[12] = { 0 };

void load_original_dll();

LPCSTR mImportNames[] = {
		"DllMain",
		"XInputEnable",
		"XInputGetBatteryInformation",
		"XInputGetCapabilities",
		"XInputGetDSoundAudioDeviceGuids",
		"XInputGetKeystroke",
		"XInputGetState",
		"XInputSetState",
		(LPCSTR)100,
		(LPCSTR)101,
		(LPCSTR)102,
		(LPCSTR)103 };

volatile bool bInitializeCalled = false;

using namespace std;

// Pre-declarations

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID /*lpReserved*/
					 )
{

	if (DLL_PROCESS_ATTACH == ul_reason_for_call)
	{

		load_original_dll();
		for (int i = 0; i < 12; i++) {
			mProcs[i] = (UINT_PTR)GetProcAddress(mHinstDLL, mImportNames[i]);
		}

		//DisableThreadLibraryCalls(hModule);
		hDll = hModule;

		// Guard against multiple calls.
		if (bInitializeCalled) 
		{
			// Decremented reference count.
			FreeLibrary(hModule);
			return FALSE;
		}

		bInitializeCalled = true;

		// Don't do anything important in dll main, just start a new thread, and do your stuff there
		_beginthread(&Start, 0, 0);
	}

	if (DLL_PROCESS_DETACH == ul_reason_for_call)
	{
		FreeLibrary(hModule);
	}

	return TRUE;
}


//Passthrough DLL functionality copied from a chain of copies, originally credited to Michael Koch
extern "C" void XInputEnable_wrapper();
extern "C" void XInputGetBatteryInformation_wrapper();
extern "C" void XInputGetCapabilities_wrapper();
extern "C" void XInputGetDSoundAudioDeviceGuids_wrapper();
extern "C" void XInputGetKeystroke_wrapper();
extern "C" void XInputGetState_wrapper();
extern "C" void XInputSetState_wrapper();
extern "C" void ExportByOrdinal100();
extern "C" void ExportByOrdinal101();
extern "C" void ExportByOrdinal102();
extern "C" void ExportByOrdinal103();

void load_original_dll() {
	char buffer[MAX_PATH];

	// Get path to system dir and to xinput1_3.dll
	GetSystemDirectoryA(buffer, MAX_PATH);

	// Append DLL name
	strcat_s(buffer, "\\xinput1_3.dll");


	printf(buffer);
	// Try to load the system's xinput1_3.dll, if pointer empty
	if (!mHinstDLL) {
		mHinstDLL = LoadLibraryA(buffer);
	}

	// Debug
	if (!mHinstDLL) {
		OutputDebugStringA("PROXYDLL: Original xinput1_3.dll not loaded ERROR ****\r\n");
		ExitProcess(0); // Exit the hard way
	}
}