#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;
//#define XMGLOBALCONST extern CONST __declspec(selectany)

namespace Colors
{
	XMGLOBALCONST XMVECTORF32 White = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
	
	XMGLOBALCONST std::vector<XMFLOAT4> color = {
		XMFLOAT4((const float*)&Colors::White),
		XMFLOAT4((const float*)&Colors::Black),
		XMFLOAT4((const float*)&Colors::Red),
		XMFLOAT4((const float*)&Colors::Green),
		XMFLOAT4((const float*)&Colors::Blue),
		XMFLOAT4((const float*)&Colors::Yellow),
		XMFLOAT4((const float*)&Colors::Cyan),
		XMFLOAT4((const float*)&Colors::Magenta)
	};
}