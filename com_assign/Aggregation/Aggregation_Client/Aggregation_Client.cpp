#include <windows.h>
#include "Aggregation_Client.h"

// global function declarations 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Aggregation_Client");

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
		TEXT("Aggregation"),
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
IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// function declaration
	void SafeInterfaceRelease(void);

	//variable Declaration
	HRESULT hr;
	int iNum1, iNum2, iResult;
	TCHAR str[255];


	switch (iMsg)
	{
	case WM_CREATE:
		// get ISum's pointer  ----------------------------------------------
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
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iResult);

		// display the result
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iResult);
		MessageBox(NULL, str, TEXT("Result"), MB_OK);

		// call QueryInterface() on ISum, to get ISubtrarct's pointer   ---------------------------------------
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
		iNum2 = 20;

		// call subtract function
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iResult);

		// display the result
		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, iResult);
		MessageBox(NULL, str, TEXT("Result"), MB_OK);

		// call QueryInterface() on ISubtract, to get IMultiplication's pointer   ---------------------------------------
		hr = pISubtract->QueryInterface(IID_IMultiplication, (void **)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface Can Not Be Obtained"), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		// as ISubtract is now not needed onwards, release it
		pISubtract->Release();
		pISubtract = NULL;//make released interface NULL

		// again initialize argument hard coded 
		iNum1 = 12;
		iNum2 = 15;

		// call multiplication function
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iResult);

		// display the result
		wsprintf(str, TEXT("Multiplication of %d and %d = %d"), iNum1, iNum2, iResult);
		MessageBox(NULL, str, TEXT("Result"), MB_OK);

		// call QueryInterface() on ISubtract, to get IMultiplication's pointer   ---------------------------------------
		hr = pIMultiplication->QueryInterface(IID_IDivision, (void **)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface Can Not Be Obtained"), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		// as ISubtract is now not needed onwards, release it
		pIMultiplication->Release();
		pIMultiplication = NULL;//make released interface NULL

		// again initialize argument hard coded 
		iNum1 = 125;
		iNum2 = 25;

		// call division function
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iResult);

		//release ISubtract pointer
		pIDivision->Release();
		pIDivision = NULL;

		// display the result
		wsprintf(str, TEXT("Division of %d and %d = %d"), iNum1, iNum2, iResult);
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


