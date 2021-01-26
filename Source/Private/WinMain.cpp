#include "../Public/Window.h"
#include <sstream>

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int mCmdShow)
{
	try{
		//Create Window

		Window wnd(360, 480, L"A New Window");

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
	catch (const HandleException& e)
	{
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	:
	HandleException(line, file),
	hr(hr)
{}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
	return "Window Exception";
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&pMsgBuf), 0, nullptr
	);
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}