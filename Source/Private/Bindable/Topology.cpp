#include "../../Public/Bindable/Topology.h"

Topology::Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type) noexcept
	:
	type(type)
{}

void Topology::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->IASetPrimitiveTopology(type);
}