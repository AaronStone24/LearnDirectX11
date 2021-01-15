#include <windows.h>
#include "../Public/WindowsMessageMap.h"

#define MAX_CLASS_NAME_LENGTH 256
#define HINSTANCE() GetModuleHandle(NULL)

// Global Variables
WCHAR	WindowClass[MAX_CLASS_NAME_LENGTH];
INT		WindowHeight;
INT		WindowWidth;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	OutputDebugString(mm.s2ws(mm(msg, lParam, wParam)).c_str());

	switch(msg)
	{
	case WM_CLOSE:
		if (MessageBox(hWnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hWnd);
		}
		return (24);
		break;
	case WM_DESTROY:
		PostQuitMessage(99);
		break;
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowTextA(hWnd, "Paid Respects");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowTextA(hWnd, "My Application");
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int mCmdShow)
{
	// Initialize Global Variables
	wcscpy_s(WindowClass, TEXT("Our First Window"));
	WindowHeight = 786;
	WindowWidth = 1366;

	//Create Windows Class
	
	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = WindowClass;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;

	RegisterClassEx(&wcex);

	//create window

	HWND hWnd = CreateWindowEx(0, WindowClass, WindowClass, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0, 0, 1368, 786, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		return 0;
	}

	// Display Window

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// Listen for messages

	MSG msg = { 0 };
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0 ,0)) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}