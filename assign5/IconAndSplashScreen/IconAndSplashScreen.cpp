#include <windows.h>
#include "IconAndSplashScreen.h"

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
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ICON_APPLICATION));
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(ICON_APPLICATION));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;

	RegisterClassEx(&wndClass);
	hwnd = CreateWindow(szAppName,
		TEXT("Custom Icon and Splash Screen Application"),
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
	HINSTANCE hInstance;
	switch (iMsg)
	{

	case WM_CREATE: 
		hInstance = LPCREATESTRUCT(lParam)->hInstance;
		hBitmap = LoadBitmap(hInstance, LPCWSTR(BITMAP_BACKGROUND));
		break;

	case WM_PAINT:
		RECT rect;
		BITMAP bitmapObj;
		HDC hdcMem;
		HDC hdcPaint;
		PAINTSTRUCT ps;

		GetClientRect(hwnd, &rect);
		hdcPaint = BeginPaint(hwnd, &ps);
		hdcMem = CreateCompatibleDC(NULL);
		SelectObject(hdcMem, (HGDIOBJ)hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bitmapObj);
		StretchBlt(hdcPaint, 0, 0, rect.right, rect.bottom,
		hdcMem, 0, 0, bitmapObj.bmWidth, bitmapObj.bmHeight, SRCCOPY);
		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

