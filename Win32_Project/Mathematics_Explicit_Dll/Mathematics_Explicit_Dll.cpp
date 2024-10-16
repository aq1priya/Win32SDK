#include <windows.h>
#include<math.h>
#include "Mathematics_Explicit_Dll.h"

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
	return(TRUE);
}
//find nth term in AP series
extern "C" float AP_nthTerm(float FirstTerm, float CommonDifference, float n)
{
	float Term;
	Term = FirstTerm + ((n - 1)*CommonDifference);
	return (Term);
}

//find Sum of AP series of n elements 
extern "C" float AP_SumOfSeries(float FirstTerm, float CommonDifference, float n)
{
	float Sum;
	Sum = ((2 * FirstTerm) + ((n - 1)*CommonDifference))*(n / 2);
	return(Sum);
}

//find nth term of GP Series
extern "C" float GP_nthTerm(float FirstTerm, float CommonRatio, float n)
{
	double Term;
	Term = FirstTerm * (pow(CommonRatio, (n - 1)));
	return ((float)Term);
}

//find Sum of GP series of n elements
extern "C" double GP_SumOfSeries(float FirstTerm, float CommonRatio, float n)
{
	double Sum;
	if (CommonRatio > 1)
	{
		Sum = (FirstTerm * (pow(CommonRatio, n) - 1)) / (CommonRatio - 1);
		return((float)Sum);
	}
	else {
		Sum = (FirstTerm * (1 - pow(CommonRatio, n))) / (CommonRatio - 1);
		return((float)Sum);
	}
}