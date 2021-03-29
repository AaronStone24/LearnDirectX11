#include "../Public/Graphics.h"
#include <sstream>
#include <d3dcompiler.h>
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

Graphics::Graphics(HWND hWnd)
	:
	projection(DirectX::XMMatrixIdentity())
{
	//Swap Chain descriptor
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	#if defined(_DEBUG)
	// If the project is in a debug build, enable the debug layer.
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	// create device, front/back buffers, and swap chain and rendering context
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pContext
	);

	//gain access to texture subresource in swap chain (back buffer)
	wrl::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&mRenderTargetView
	);

	//depth/stencil buffer descriptor
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDSState;
	pDevice->CreateDepthStencilState(&depthStencilDesc, &pDSState);

	//bind depth state
	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

	//depth/stencil buffer descriptor
	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = 1080u;
	depthTextureDesc.Height = 720u;
	depthTextureDesc.MipLevels = 1u;
	depthTextureDesc.ArraySize = 1u;
	depthTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthTextureDesc.SampleDesc.Count = 1u;
	depthTextureDesc.SampleDesc.Quality = 0u;
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTextureDesc.CPUAccessFlags = 0u;
	depthTextureDesc.MiscFlags = 0u;

	//create the depth/stencil buffer and view
	wrl::ComPtr<ID3D11Texture2D> mDepthStencilBuffer = nullptr;
	pDevice->CreateTexture2D(
		&depthTextureDesc,
		nullptr,
		&mDepthStencilBuffer
	);

	//create depth stencil texture view
	D3D11_DEPTH_STENCIL_VIEW_DESC DSVdesc = {};
	DSVdesc.Format = DXGI_FORMAT_D32_FLOAT;
	DSVdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DSVdesc.Texture2D.MipSlice = 0u;
	pDevice->CreateDepthStencilView(
		mDepthStencilBuffer.Get(),
		&DSVdesc,
		&mDepthStencilView
	);

	//Bind the render target view and depth/stencil view to the pipeline
	pContext->OMSetRenderTargets(
		1u,
		mRenderTargetView.GetAddressOf(), //don't have to release the renderTargetView here so using GetAddressOf()
		mDepthStencilView.Get()
	);

	//configure viewport
	D3D11_VIEWPORT mScreenViewport = {};
	mScreenViewport.TopLeftX = 0;
	mScreenViewport.TopLeftY = 0;
	mScreenViewport.Width = 1080.0f;
	mScreenViewport.Height = 720.0f;
	mScreenViewport.MinDepth = 0.0f;
	mScreenViewport.MaxDepth = 1.0f;
	pContext->RSSetViewports(1, &mScreenViewport);

	//Creating render state objects at initialization time
	//Wireframe descriptor
	D3D11_RASTERIZER_DESC rsDescWF = {};
	ZeroMemory(&rsDescWF, sizeof(D3D11_RASTERIZER_DESC));
	rsDescWF.FillMode = D3D11_FILL_WIREFRAME;
	rsDescWF.FrontCounterClockwise = false;
	rsDescWF.CullMode = D3D11_CULL_NONE;

	//Solid descriptor
	D3D11_RASTERIZER_DESC rsDescS = {};
	ZeroMemory(&rsDescS, sizeof(D3D11_RASTERIZER_DESC));
	rsDescS.FillMode = D3D11_FILL_SOLID;
	rsDescS.FrontCounterClockwise = false;
	rsDescS.CullMode = D3D11_CULL_NONE;

	//Creating wireframe rasterizer
	pDevice->CreateRasterizerState(&rsDescWF, &mWireframeRS);
	//creating solid rasterizer
	pDevice->CreateRasterizerState(&rsDescS, &mSolidRS);
}

void Graphics::EndFrame()
{
	pSwapChain->Present(1u, 0u); 
}

void Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red,green,blue,1.0f };
	pContext->ClearRenderTargetView(mRenderTargetView.Get(), color);
	pContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::DrawIndexed(UINT count) noexcept
{
	pContext->DrawIndexed(count, 0u, 0u);
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
	projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const noexcept
{
	return projection;
}

void Graphics::SetRasterizerState(int choice) noexcept
{
	switch (choice)
	{
	case 0:
		pContext->RSSetState(mSolidRS.Get());
		break;
	case 1:
		pContext->RSSetState(mWireframeRS.Get());
		break;
	default:
		pContext->RSSetState(0);	//the default state
		break;
	}
}

//Exception part down from here
Graphics::InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file)
{
	//join all info messages with newlines into a single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	//remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}

const char* Graphics::InfoException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Graphics::InfoException::GetType() const noexcept
{
	return "Graphics Info Exception";
}

std::string Graphics::InfoException::GetErrorInfo() const noexcept
{
	return info;
}