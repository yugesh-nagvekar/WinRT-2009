#include <windows.h>
#define ColourTimer 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ColourStripsWindow");

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndClass);
	hwnd = CreateWindow(szAppName,
		TEXT("Colour Stripes Application"),
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
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rect;
	PAINTSTRUCT paintStruct;
	HBRUSH hBrush;
	static int iPaintFlag = 0;

	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, ColourTimer, 1000, NULL);
		break;
	case WM_TIMER:
		KillTimer(hwnd, ColourTimer);
		iPaintFlag++;
		if (iPaintFlag > 8)
			iPaintFlag = 0;
		InvalidateRect(hwnd, NULL, true);
		SetTimer(hwnd, ColourTimer, 1000, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		RECT rect;
		int iCurrentColourFlag = 1;
		if (iPaintFlag == 0)
			break;
		GetClientRect(hwnd, &rect);
		hdc = BeginPaint(hwnd, &paintStruct);
		//-------------Getting Geometry-------------------	
		int iRectWidth = rect.right - rect.left;
		int iLeft = 0;
		int iRight = iRectWidth / 8;
		rect.left = iLeft;
		rect.right = iRight;
		//------------------------------------------------	
		while (iCurrentColourFlag <= iPaintFlag)
		{
			switch (iCurrentColourFlag)
			{
			case 1:
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				break;
			case 2:
				hBrush = CreateSolidBrush(RGB(0, 255, 0));
				break;
			case 3:
				hBrush = CreateSolidBrush(RGB(0, 0, 255));
				break;
			case 4:
				hBrush = CreateSolidBrush(RGB(0, 255, 255));
				break;
			case 5:
				hBrush = CreateSolidBrush(RGB(255, 0, 255));
				break;
			case 6:
				hBrush = CreateSolidBrush(RGB(255, 255, 0));
				break;
			case 7:
				hBrush = CreateSolidBrush(RGB(255, 255, 255));
				break;
			default:
				hBrush = CreateSolidBrush(RGB(0, 0, 0));
				break;

			}
			FillRect(hdc, &rect, hBrush);
			rect.left += iRectWidth/8;
			rect.right += iRectWidth/8;
			iCurrentColourFlag++;
		}
		EndPaint(hwnd, &paintStruct);
	}
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

