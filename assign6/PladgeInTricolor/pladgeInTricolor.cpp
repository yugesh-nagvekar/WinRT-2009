#include <windows.h>


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
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndClass);
	hwnd = CreateWindow(szAppName,
		TEXT("Tricoloured Pladge"),
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
	PAINTSTRUCT ps;
	TCHAR str[155];
	RECT rect;
	TCHAR orange[] = TEXT("India is my country. All Indians are my Brothers and Sisters."
		"I love my country and I am proud of its rich and varied heritage.");
	TCHAR white[] = TEXT("I shall always strive to be worthy of it."
		"I shall give my parents, teachers and all elders respect and treat everyone with courtesy.");
	TCHAR green[] = TEXT("To my country and my people, I pledge my devotion."
		"In their well being and prosperity alone, lies my happiness. ");


	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		
		SetTextColor(hdc, RGB(255, 125, 0));
		TextOut(hdc, 5, 5, orange, lstrlenW(orange));
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 5, 25, white, lstrlenW(white));
		SetTextColor(hdc, RGB(0, 255, 0));
		TextOut(hdc, 5, 45, green, lstrlenW(green));


		EndPaint(hwnd, &ps);

		//wsprintf(str, TEXT("Win32 Window"));

		//GetClientRect(hwnd, &rect);

		//hdc = BeginPaint(hwnd, &ps);
		//SetTextColor(hdc, RGB(0, 255, 0));
		//SetBkColor(hdc, RGB(0, 0, 0));
		//DrawText(hdc, orange, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//EndPaint(hwnd, &ps);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}



