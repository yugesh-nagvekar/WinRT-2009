#include <windows.h>
#include "splashScreen.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Window");

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
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;

	RegisterClassEx(&wndClass);
	hwnd = CreateWindow(szAppName,
		TEXT("Background Screen APPLICATION"),
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
	static HBITMAP hBitmap;
	HDC hdcPaint;
	HDC hdcMem;
	RECT rect;
	PAINTSTRUCT ps;
	switch (iMsg)
	{
	case WM_CREATE:
		hBitmap = LoadBitmap((HINSTANCE)GetModuleHandle(TEXT("Window.exe")), MAKEINTRESOURCE(BITMAP_BACKGROUND));
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rect);
		hdcPaint = BeginPaint(hwnd, &ps);
		hdcMem = CreateCompatibleDC(NULL);
		SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), hdcMem);
		StretchBlt(hdcPaint,
			rect.left, rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top,
			hdcMem,
			rect.left, rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top,NULL);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}




