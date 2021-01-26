#include "../Public/App.h"
#include <sstream>

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
		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			MessageBoxA(nullptr, "Key Pressed", "Space bar was pressed", MB_OK | MB_ICONEXCLAMATION);
		}
		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();
			static int scrollCount = 0;
			switch (e.GetType())
			{
			case Mouse::Event::Type::WheelUp:
			{
				++scrollCount;
				std::ostringstream oss;
				oss << "Up: " << abs(scrollCount);
				wnd.SetTitle(oss.str());
				break;
			}
			case Mouse::Event::Type::WheelDown:
			{
				--scrollCount;
				std::ostringstream oss;
				oss << "Up: " << abs(scrollCount);
				wnd.SetTitle(oss.str());
				break;
			}
			case Mouse::Event::Type::Leave:
			{
				wnd.SetTitle("Gone!");
				break;
			}
			case Mouse::Event::Type::Move:
			{
				std::ostringstream oss;
				oss << "Mouse position: (" << e.GetPosX() << "," << e.GetPosY() << ")";
				wnd.SetTitle(oss.str());
				break;
			}
			default:
				break;
			}

		}
	}

	if (gResult == -1)
	{
		return -1;
	}

	return msg.wParam;
}

void App::DoFrame()
{

}