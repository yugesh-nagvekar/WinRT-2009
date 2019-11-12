#include <windows.h>
#include "ClassFactory_Server.h"

// global function declarations 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ClassFactory_Client");

	//COM code -------------------------------------------
	HRESULT hr;

	//code
	//COM Intialisation
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library Can not be Initialized.\nExiting Program."), TEXT("Program Error"), MB_OK);
		exit(0);
	}
	else
	{
		//MessageBox(NULL, TEXT("CoInitialize Done."), TEXT("Test"), MB_OK);
	}


	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;

	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;

	RegisterClassEx(&wndClass);
	hwnd = CreateWindow(szAppName,
		TEXT("Class Factory"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// COM Un-initialization
	CoUninitialize();

	return ((int)msg.wParam);
}

// global variable declarations
ISum *pISum = NULL;
ISubtract *pISubtract = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// function declaration
	void SafeInterfaceRelease(void);

	//variable Declaration
	HRESULT hr;
	int iNum1, iNum2, iSum;
	TCHAR str[255];


	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface Can Not Obtained."), TEXT("Program Error"), MB_OK);
			wsprintf(str, TEXT("hr = %x"), hr);
			//MessageBox(hwnd, str, TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}


		//Initialize argument hardcoded
		iNum1 = 55;
		iNum2 = 45;

		// call SumOfTwoIntegers() of ISum 
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);

		// display the result
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(NULL, str, TEXT("Result"), MB_OK);

		// call QueryInterface() on ISum, to get ISubtrarct's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface Can Not Be Obtained"), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		// as ISum is now not needed onwards, release it
		pISum->Release();
		pISum = NULL;//make released interface NULL

		// again initialize argument hard coded 
		iNum1 = 55;
		iNum2 = 45;

		// call subtract function
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);

		//release ISubtract pointer
		pISubtract->Release();
		pISubtract = NULL;

		// display the result
		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(NULL, str, TEXT("Result"), MB_OK);

		// exit the application
		DestroyWindow(hwnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease(void)
{
	// code
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
}


