#include "../Public/App.h"
#include <sstream>
#include <iomanip>

App::App()
	:
	wnd(1080, 720, L"D3D11 Application")
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
	wnd.Gfx().DrawTestTriangle(timer.Peek());
	//presenting the frame here
	wnd.Gfx().EndFrame();
}