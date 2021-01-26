#include "../Public/App.h"
#include <sstream>
#include <iomanip>

App::App()
	:
	wnd(800, 600, L"A new Window")
{}

int App::Go()
{
	// Listen for messages

	MSG msg = { 0 };
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
		DoFrame();
	}

	if (gResult == -1)
	{
		return -1;
	}

	return msg.wParam;
}

void App::DoFrame()
{
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	wnd.SetTitle(oss.str());
}