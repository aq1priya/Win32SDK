#import "Physics_Server1.tlb" no_namespace, raw_interfaces_only
#include "x64/Debug/physics_server1.tlh"
#include <windows.h>
#include <stdio.h>

//global variables
HRESULT hr;

//Dll Main
BOOL WINAPI DllMain(HMODULE PhysicsClientDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

extern "C" void InitializeCOM(void)
{
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library cannot be initialize"), TEXT("InitializeCOM Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}
}

extern "C" void UninitializeCOM(void)
{
	CoUninitialize();
}

extern "C" void COMErrorMessage(HRESULT hr)
{
	//variable declarations
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%s, # %#x"), szErrorMessage, hr);
		LocalFree(szErrorMessage);
	}
	else
		swprintf_s(str, TEXT("[Could not find a description for error # %#x.]\n"), hr);
	MessageBox(NULL, str, TEXT("COM Error"), MB_OK);
}

extern "C" float CallCriticalVelocity(float Height)
{
	//local variables
	float Vc = 0;
	//TCHAR str[255];
	CLSID clsidPhysics;
	IPhysics *app;

	hr = CLSIDFromProgID(L"ManagedServerForInterop.Physics", &clsidPhysics);
	if (FAILED(hr))
	{
		COMErrorMessage(hr);
	}

	hr = CoCreateInstance(clsidPhysics, NULL, CLSCTX_INPROC_SERVER, __uuidof(IPhysics), (VOID**)&app);
	if (FAILED(hr))
	{
		COMErrorMessage(hr);
	}

	hr = app->CalculateCriticalVelocity(Height, &Vc);

	if (FAILED(hr))
	{
		COMErrorMessage(hr);
	}
	return(Vc);
}
