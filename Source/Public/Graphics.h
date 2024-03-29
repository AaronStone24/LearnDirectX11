#pragma once
#include "CustomHeaders.h"
#include "HandleException.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <memory>
#include <random>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <Windows.h>

class Graphics
{
	friend class Bindable;
public:
	class Exception : public HandleException
	{
		using HandleException::HandleException;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawIndexed(UINT count) noexcept;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetRasterizerState(int choice) noexcept;
private:
	DirectX::XMMATRIX projection;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mWireframeRS = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mSolidRS = nullptr;
};