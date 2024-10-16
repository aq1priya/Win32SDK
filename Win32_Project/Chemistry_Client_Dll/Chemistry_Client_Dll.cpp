#include<Windows.h>
#include"Chemistry_Server_Dll.h"
#include<stdio.h>

//global variable declarations
IConcentration *pIConcentration = NULL;
IMoleFraction *pIMoleFraction = NULL;
IMolarity *pIMolarity = NULL;
IMolality *pIMolality = NULL;
HRESULT hr;

BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	//code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_PROCESS_DETACH:
		break;

	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

extern "C" void InitializeCOM(void)
{
	HRESULT hr;
	//COM initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM library cannot be initialized.\nProgram will exit now"), TEXT("Pogram error"), MB_OK);
		exit(0);
	}
}

extern "C" void UnInitializeCOM(void)
{
	CoUninitialize();
}

extern "C" float CalculateConcentrationByMass(float MassOfSolute, float MassOfSolvent)
{
	float SoluteConcentrationByMass;
	hr = CoCreateInstance(CLSID_SolutionProperties, NULL, CLSCTX_INPROC_SERVER,
		IID_IConcentration, (void **)&pIConcentration);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IConcentration Interface can not be obtained"), TEXT("Error"), MB_OK);
	}
	//Call ConcentrationOfSoluteByMass() of IConcentration 
	pIConcentration->ConcentrationOfSoluteByMass(MassOfSolute, MassOfSolvent, &SoluteConcentrationByMass);
	return SoluteConcentrationByMass;
}

extern "C" float CalculateConcentrationByVolume(float VolumeOfSolute, float VolumeOfSolvent)
{
	float SoluteConcentrationByVolume;

	//Call ConcentrationOfSoluteByVolume() of IConcentration 
	pIConcentration->ConcentrationOfSoluteByVolume(VolumeOfSolute, VolumeOfSolvent, &SoluteConcentrationByVolume);
	return SoluteConcentrationByVolume;
}

extern "C" float CalculateMoleFractionOfSolute(float MolesOfSolute, float MolesOfSolvent)
{
	
	float SoluteMoleFraction;
	//Call QueryInterface on IConcentration to get IMoleFraction's pointer
	hr = pIConcentration->QueryInterface(IID_IMoleFraction, (void **)&pIMoleFraction);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMoleFraction Interface can not be obtained"), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
	}
	//Release IConcentration
	pIConcentration->Release();
	pIConcentration = NULL;

	//Call IMoleFraction's MoleFractionOfSolute()
	pIMoleFraction->MoleFractionOfSolute(MolesOfSolute, MolesOfSolvent, &SoluteMoleFraction);
	return SoluteMoleFraction;
}
extern "C" float CalculateMoleFractionOfSolvent(float MolesOfSolute, float MolesOfSolvent)
{
	float SolventMoleFraction;

	//call IMoleFraction's MoleFractionOfSolvent()
	pIMoleFraction->MoleFractionOfSolvent(MolesOfSolute, MolesOfSolvent, &SolventMoleFraction);
	return SolventMoleFraction;
}

extern "C" float CalculateMolarity(float MolesOfSolute, float VolumeOfSolute, float VolumeOfSolvent)
{
	float Molarity;

	//Call QueryInterface on IMoleFraction to get IMolarity's pointer
	hr = pIMoleFraction->QueryInterface(IID_IMolarity, (void **)&pIMolarity);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMolarity Interface can not be obtained"), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
	}

	//Release pIMoleFraction
	pIMoleFraction->Release();
	pIMoleFraction = NULL;

	//Call IMolarity's method
	pIMolarity->Molarity(MolesOfSolute, VolumeOfSolute, VolumeOfSolvent, &Molarity);
	return Molarity;
}

extern "C" float CalculateMolality(float MolesOfSolute, float MassOfSolute, float MassOfSolvent)
{
	float Molality;

	//Call QueryInterface on IMolarity to get IMolality's pointer
	hr = pIMolarity->QueryInterface(IID_IMolality, (void **)&pIMolality);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMolality Interface can not be obtained"), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
	}

	//Release IMolarity
	pIMolarity->Release();
	pIMolarity = NULL;

	//Call IMolality's methods
	pIMolality->Molality(MolesOfSolute, MassOfSolute, MassOfSolvent, &Molality);

	//Relese IMolality
	pIMolality->Release();
	pIMolality = NULL;

	return Molality;
}