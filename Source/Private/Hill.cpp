#include "../Public/Hill.h"
#include "../Public/Plane.h"
#include "../Public/Bindable/BindableBase.h"

Hill::Hill(Graphics& gfx)
	:
	theta(0.0f),
	phi(0.0f),
	chi(0.0f),
	dtheta(0.5f),
	dphi(0.1f),
	dchi(0.1f)
{
	struct Vertex1
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
	};
	auto model = Plane::MakeTesselated<Vertex1>(160.0f, 160.0f, 50, 50);

	const auto GetHeight = [](float x, float z)
	{
		return 0.3f * (z * sinf(0.1f * x) + x * cosf(0.1f * z));
	};
	
	for (auto& vertex : model.vertices)
	{
		XMFLOAT3 p = vertex.pos;
		p.y = GetHeight(p.x, p.z);
		vertex.pos = p;

		//Color the vertex based on its height
		if (p.y < -10.0f)
		{
			//Sandy beach colour
			vertex.color = XMFLOAT4(1.0f, 0.96f, 0.62f, 1.0f);
		}
		else if (p.y < 5.0f)
		{
			//Light yellow-green
			vertex.color = XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
		}
		else if (p.y < 12.0f)
		{
			//Dark yellow-green
			vertex.color = XMFLOAT4(0.1f, 0.48f, 0.19f, 1.0f);
		}
		else if(p.y < 20.0f)
		{
			//Dark brown
			vertex.color = XMFLOAT4(0.45f, 0.39f, 0.34f, 1.0f);
		}
		else
		{
			//White snow
			vertex.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	
	//model.Transform(DirectX::XMMatrixScaling(30.0f, 30.0f, 30.0f));

	AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"ColorBlendVS.cso");
	auto pvsbc = pvs->GetByteCode();
	AddStaticBind(std::move(pvs));

	AddStaticBind(std::make_unique<PixelShader>(gfx, L"ColorBlendPS.cso"));

	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCBuf>(gfx, *this));
}

DirectX::XMMATRIX Hill::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationY(theta) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 40.0f);
}

void Hill::Update(float dt) noexcept
{
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}