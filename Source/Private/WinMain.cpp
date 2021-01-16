#include "../Public/Window.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int mCmdShow)
{
	//Create Window
	
	Window wnd(360, 480, L"A New Window");

	// Listen for messages

	MSG msg = { 0 };
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0 ,0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	
	return msg.wParam;
}