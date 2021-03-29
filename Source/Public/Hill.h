#pragma once
#include "Drawable/DrawableBase.h"

class Hill : public DrawableBase<Hill>
{
public:
	Hill(Graphics& gfx);
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
};