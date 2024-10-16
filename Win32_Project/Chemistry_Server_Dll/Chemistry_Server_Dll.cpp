#include <Windows.h>
#include<stdio.h>
#include"Chemistry_Server_Dll.h"

//class declaration
class CSolutionProperties :public IConcentration, IMoleFraction, IMolarity, IMolality
{
private:
	long m_cRef;
public:
	//constructor
	CSolutionProperties(void);
	//destructor
	~CSolutionProperties(void);

	//IUnknown specific method declarations(inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IConcentration specific method declarations(inherited)
	//HRESULT __stdcall MassOfSolution(float, float, float *);
	//HRESULT __stdcall VolumeOfSolution(float, float, float *);
	HRESULT __stdcall ConcentrationOfSoluteByMass(float, float, float *);
	HRESULT __stdcall ConcentrationOfSoluteByVolume(float, float, float *);

	//IMoleFraction specific method declarations(inherited)
	HRESULT __stdcall MoleFractionOfSolvent(float, float, float *);
	HRESULT __stdcall MoleFractionOfSolute(float, float, float *);

	//IMolarity specific method declarations (inherited)
	HRESULT __stdcall Molarity(float, float,float, float *);

	//IMolality specific method declarations (inherited)
	HRESULT __stdcall Molality(float, float,float, float *);
};

class CSolutionPropertiesClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor
	CSolutionPropertiesClassFactory(void);
	//destructor
	~CSolutionPropertiesClassFactory(void);

	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory specific method declarations (inherited)
	HRESULT  __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

//global variable
long glNumberOfActiveComponents = 0;//number of active components
long glNumbersOfServerLocks = 0; //number of locks on this dll

//DLL Main
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

//Implementation of CSolutionProperties Constructor method
CSolutionProperties::CSolutionProperties(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

//Implementation of CSolutionProperties destructor method
CSolutionProperties::~CSolutionProperties(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}
//Implementation of CSolutionProperties's IUnknowns methods
HRESULT CSolutionProperties::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IConcentration *>(this);
	else if (riid == IID_IConcentration)
		*ppv = static_cast<IConcentration *>(this);
	else if (riid == IID_IMoleFraction)
		*ppv = static_cast<IMoleFraction *>(this);
	else if (riid == IID_IMolarity)
		*ppv = static_cast<IMolarity *>(this);
	else if (riid == IID_IMolality)
		*ppv = static_cast<IMolality *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSolutionProperties::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSolutionProperties::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation Of CSolutionProperties's IConcentration's methods
//HRESULT CSolutionProperties::MassOfSolution(float SoluteMass, float SolventMass, float *pSolutionMass)
//{
//	*pSolutionMass = SoluteMass + SolventMass;
//	return(S_OK);
//}
//HRESULT CSolutionProperties::VolumeOfSolution(float SoluteVolume, float SolventVolume, float *pSolutionVolume)
//{
//	*pSolutionVolume = SoluteVolume + SolventVolume;
//	return(S_OK);
//}
HRESULT CSolutionProperties::ConcentrationOfSoluteByMass(float SoluteMass, float SolventMass, float *pConcentrationByMass)
{
	float SolutionMass;
	SolutionMass = SoluteMass + SolventMass;
	*pConcentrationByMass = (SoluteMass / SolutionMass) * 100;
	return(S_OK);
}
HRESULT CSolutionProperties::ConcentrationOfSoluteByVolume(float SoluteVolume, 
	float SolventVolume, float *pConcentrationByVolume)
{
	float SolutionVolume;
	SolutionVolume = SoluteVolume + SolventVolume;
	*pConcentrationByVolume = (SoluteVolume / SolutionVolume) * 100;
	return(S_OK);
}

//Implementation of CSolutionProperties's IMoleFraction's methods
HRESULT CSolutionProperties::MoleFractionOfSolute(float SoluteMoles, float SolventMoles, float *pMoleFractionOfSolute)
{
	float SolutionMoles;
	SolutionMoles = SoluteMoles + SolventMoles;
	*pMoleFractionOfSolute = (SoluteMoles / SolutionMoles);
	return(S_OK);
}
HRESULT CSolutionProperties::MoleFractionOfSolvent(float SoluteMoles, float SolventMoles, float *pMoleFractionOfSolvent)
{
	
	float SolutionMoles;
	SolutionMoles = SoluteMoles + SolventMoles;
	*pMoleFractionOfSolvent = (SolventMoles / SolutionMoles);
	return(S_OK);
}

//Implementation Of CSolutionProperties's IMolarity's method
HRESULT CSolutionProperties::Molarity(float SoluteMoles, float SoluteVolume, float SolventVolume, float *pMolarity)
{
	float SolutionVolume;
	SolutionVolume = SoluteVolume + SolventVolume;
	*pMolarity = SoluteMoles / SolutionVolume;
	return(S_OK);
}

//Implementation of CSolutionProperties's IMolality's method
HRESULT CSolutionProperties::Molality(float SoluteMoles, float SoluteMass, float SolventMass, float *pMolality)
{
	float SolutionMass;
	SolutionMass = SoluteMass + SolventMass;
	*pMolality = SoluteMoles / SolutionMass;
	return(S_OK);
}

//Implementation of CSolutionPropertiesClassFactory's constructor
CSolutionPropertiesClassFactory::CSolutionPropertiesClassFactory(void)
{
	m_cRef = 1;
}

//Implementation CSolutionPropertiesClassFactory's destructor
CSolutionPropertiesClassFactory::~CSolutionPropertiesClassFactory(void)
{
	//no code
}

//Implementation of CSolutionPropertiesClassFactory's IClassFactory's IUnknown's methods
HRESULT CSolutionPropertiesClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSolutionPropertiesClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSolutionPropertiesClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of CSolutionPropertiesClassFactory's IClassFactory's methods
HRESULT CSolutionPropertiesClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	//variable declarations
	CSolutionProperties *pCSolutionProperties = NULL;
	HRESULT hr;

	//code
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	//create instance of coclass component
	pCSolutionProperties = new CSolutionProperties;
	if (pCSolutionProperties == NULL)
		return(E_OUTOFMEMORY);

	//get the requested interface
	hr = pCSolutionProperties->QueryInterface(riid, ppv);

	pCSolutionProperties->Release();
	return(hr);
}

HRESULT CSolutionPropertiesClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumbersOfServerLocks);
	else
		InterlockedDecrement(&glNumbersOfServerLocks);
	return(S_OK);
}

//Implementation of Exported functions from this dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	
	//variable declarations
	CSolutionPropertiesClassFactory *pCSolutionPropertiesClassFactory = NULL;
	HRESULT hr;
	
	if (rclsid != CLSID_SolutionProperties)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//Create Class factory
	pCSolutionPropertiesClassFactory = new CSolutionPropertiesClassFactory;
	if (pCSolutionPropertiesClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSolutionPropertiesClassFactory->QueryInterface(riid, ppv);
	pCSolutionPropertiesClassFactory->Release();
	return(hr);
}
HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumbersOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}