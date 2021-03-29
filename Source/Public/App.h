#pragma once
#include "Window.h"
#include "Timer.h"

class App
{
public:
	App();
	//master frame/message loop
	int Go();
	~App();
private:
	void DoFrame();
private:
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 1;
};