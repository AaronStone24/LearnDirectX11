#include <windows.h>

#define MAX_CLASS_NAME_LENGTH 256
#define HINSTANCE() GetModuleHandle(NULL)

// Global Variables
WCHAR	WindowClass[MAX_CLASS_NAME_LENGTH];
INT		WindowHeight;
INT		WindowWidth;

int CALLBACK wWinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Initialize Global Variables
	wcscpy_s(WindowClass, TEXT("Our First Window"));
	WindowHeight = 786;
	WindowWidth = 1366;

	//Create Windows Class
	
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszMenuName = nullptr;

	wcex.lpszClassName = WindowClass;

	wcex.hInstance = HINSTANCE();

	wcex.lpfnWndProc = DefWindowProc;

	RegisterClassEx(&wcex);

	//create window

	HWND hWnd = CreateWindow(WindowClass, WindowClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HINSTANCE(), nullptr);
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
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	return 0;
}