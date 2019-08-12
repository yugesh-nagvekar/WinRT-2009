#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ColourChangingWindow");

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndClass);
	hwnd = CreateWindow(szAppName,
		TEXT("Colour Change Application"),
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
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR:
	{
		switch (LOWORD(wParam))
		{
		case 'r':
		case 'R':
			iPaintFlag = 1;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'g':
		case 'G':
			iPaintFlag = 2;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'b':
		case 'B':
			iPaintFlag = 3;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'c':
		case 'C':
			iPaintFlag = 4;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'm':
		case 'M':
			iPaintFlag = 5;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'y':
		case 'Y':
			iPaintFlag = 6;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'w':
		case 'W':
			iPaintFlag = 7;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'k':
		case 'K':
			iPaintFlag = 0;
			InvalidateRect(hwnd, NULL, true);
			break;
		default:
			break;
		}
	}
	case WM_PAINT:
	{
		GetClientRect(hwnd, &rect);
		hdc = BeginPaint(hwnd, &paintStruct);
		switch (iPaintFlag)
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
		EndPaint(hwnd, &paintStruct);
	}
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

