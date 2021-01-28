#include "../Public/App.h"
#include <sstream>
#include <iomanip>

App::App()
	:
	wnd(800, 600, L"A new Window")
{}

int App::Go()
{
	while (true)
	{
		//process all pending messages
		if (const auto ecode = Window::ProcessMessages())
		{
			//if optional has value that means it was quit value otherwise it won't have a value;
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	//presenting the frame here
	wnd.Gfx().EndFrame();
}