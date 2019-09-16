#include<windows.h>

#include "MathLib.h"

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
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
	return TRUE;
}


extern "C" BOOL IsNumberNegative(int num)
{
	if (num < 0)
	{
		return TRUE;
	}
	return FALSE;
}


extern "C" int MakeSqaure(int num)
{
	if (IsNumberNegative(num))
	{
		return 1;
	}
	return num * num;

}



