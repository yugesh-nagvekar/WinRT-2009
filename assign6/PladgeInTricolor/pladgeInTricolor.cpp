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
	
	TCHAR orange1[] = TEXT("India is my country.");
	TCHAR orange2[] = TEXT("All Indians are my Brothers and Sisters.");
	TCHAR orange3[] = TEXT("I love my country and I am proud of");
	TCHAR orange4[] = TEXT("its rich and varied heritage.");

	TCHAR white1[] = TEXT("I shall always strive to be worthy of it.");
	TCHAR white2[] = TEXT("I shall give my parents, teachers and all elders");
	TCHAR white3[] = TEXT("respect and treat everyone with courtesy.");

	TCHAR green1[] = TEXT("To my country and my people,");
	TCHAR green2[] = TEXT("I pledge my devotion. In their");
	TCHAR green3[] = TEXT("well being and prosperity alone,");
	TCHAR green4[] = TEXT("lies my happiness.");


	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		int iCenterH, iCenterV, iBoxTop;
		int iLineNo = 0, iLineHeight = 20, iLineCount = 11;
		GetClientRect(hwnd, &rect);
		iCenterH = rect.left + (rect.right - rect.left)/2;
		iCenterV = rect.top + (rect.bottom - rect.top)/2;
		iBoxTop = iCenterV - (iLineCount / 2) * iLineHeight; // top of box = center - (half of line count)*line hight
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextAlign(hdc, TA_CENTER);
		
		SetTextColor(hdc, RGB(255, 125, 0));
		//textOut with refPoint x - horizontally center and y - vertical top + each line Number * height
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), orange1, lstrlenW(orange1));
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), orange2, lstrlenW(orange2));
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), orange3, lstrlenW(orange3));
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), orange4, lstrlenW(orange4));
		
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), white1, lstrlenW(white1));
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), white2, lstrlenW(white2));
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), white3, lstrlenW(white3));

		SetTextColor(hdc, RGB(0, 255, 0));
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), green1, lstrlenW(green1));
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), green2, lstrlenW(green2));
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), green3, lstrlenW(green3));
		TextOut(hdc, iCenterH, iBoxTop + (iLineNo++ * iLineHeight), green4, lstrlenW(green4));


		EndPaint(hwnd, &ps);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}



