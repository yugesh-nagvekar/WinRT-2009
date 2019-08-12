#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdline,
	int iCmdShow)
{
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Window Message");
	
	MessageBox(NULL, TEXT("STARTING WINDOW"), TEXT("Message Box"), MB_OK | MB_ICONINFORMATION);

	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;

	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION	);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);

	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = 0;

	RegisterClassEx(&wndClass);

	hwnd = CreateWindow(szAppName,
						TEXT("Message Box Application"),
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
	TCHAR str[256];
	switch (iMsg)
	{
	case WM_CREATE:
		wsprintf(str, TEXT("WM_CREATE Arriived....."));
		MessageBox(hwnd,str,TEXT("Message Box"),MB_OK|MB_ICONINFORMATION);

		break;
	case WM_KEYDOWN:
		wsprintf(str, TEXT("Key Pressed....."));
		MessageBox(hwnd, str, TEXT("Message Box"), MB_OK | MB_ICONINFORMATION);

		break;
	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("Mouse Button Pressed....."));
		MessageBox(hwnd, str, TEXT("Message Box"), MB_OK | MB_ICONINFORMATION);

		break;
	case WM_DESTROY:
		wsprintf(str, TEXT("Destroying Window....."));
		MessageBox(hwnd, str, TEXT("Message Box"), MB_OK | MB_ICONHAND);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}