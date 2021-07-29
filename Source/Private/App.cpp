#include "../Public/App.h"
#include "../Public/Box.h"
#include "../Public/Melon.h"
#include "../Public/Pyramid.h"
#include "../Public/Math.h"
#include "../Public/Hill.h"
#include "../Public/Surface.h"
#include "../Public/GDIPlusManager.h"
#include <sstream>
#include <iomanip>
#include <memory>
#include <algorithm>

GDIPlusManager gdipm;


App::App()
	:
	wnd(1080, 720, L"D3D11 Application")
{
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{	/*
			switch (typedist(rng))
			{
			case 0:
				return std::make_unique<Pyramid>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			case 1:
				return std::make_unique<Box>(
					gfx, rng, adist, ddist,
					odist, rdist, bdist
					);
			case 2:
				return std::make_unique<Hill>(
					gfx
					);
			default:
				assert(false && "bad drawable type in factory");
				return {};
			}
			*/
			return std::make_unique<Hill>(gfx);
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> typedist{ 0,2 };
	};

	Factory f(wnd.Gfx());
	//drawables.reserve(nDrawables);
	wnd.Gfx().SetRasterizerState(0);
	//std::generate_n(std::back_inserter(drawables), nDrawables, f);
	drawables.push_back(std::make_unique<Hill>(wnd.Gfx()));
	const auto s = Surface::FromFile("Source\\Private\\Images\\hummingbird.png");
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 72.0f / 108.0f, 0.5f, 500.0f));
}

void App::DoFrame()
{
	const auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& d : drawables)
	{
		d->Update(dt);
		d->Draw(wnd.Gfx());
	}
	wnd.Gfx().EndFrame();
}

App::~App()
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