#include<windows.h>
#include "MathLib.h"

//global callback declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("DLL USER Explicit");


	//initialization of WNDCLASSEX

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	RegisterClassEx(&wndclass);

	//create window

	hwnd = CreateWindow(szAppName,
		TEXT("DLL client Application"),
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

	//message loop

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//HDC hdc;
	//PAINTSTRUCT ps;
	//RECT rc;
	int num = 121;

	TCHAR str[255];
	HINSTANCE hDll = NULL;
	typedef int(*pointerMakeSqaure)(int);
	pointerMakeSqaure pfn = NULL;

	switch (iMsg)
	{

	case WM_CREATE:

		int result;
		hDll = LoadLibrary(TEXT("MathLib.dll"));

		if (hDll == NULL)
		{
			MessageBox(hwnd, TEXT("MathLib.dll Not Found"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		pfn = (pointerMakeSqaure)GetProcAddress(hDll, "MakeSqaure");

		if (pfn == NULL)
		{
			MessageBox(hwnd, TEXT("MakeSquare function Not Found"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		result = pfn(num); // using dll function

		wsprintf(str, TEXT("Square of %d is %d"), num, result);
		MessageBox(hwnd, str, TEXT("Result from DLL"), MB_OK);

		FreeLibrary(hDll);
		DestroyWindow(hwnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//case WM_PAINT:
		//	GetClientRect(hwnd, &rc);
		//	hdc = BeginPaint(hwnd, &ps);
		//	SetTextColor(hdc, RGB(0, 255, 0));
		//	SetBkColor(hdc, RGB(0, 0, 0));
		//	//DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//	EndPaint(hwnd, &ps);
		//	break;

	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}