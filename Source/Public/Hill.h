#pragma once
#include "Drawable/DrawableBase.h"

class Hill : public DrawableBase<Hill>
{
public:
	Hill(Graphics& gfx);
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void Update(float dt) noexcept override;
private:
	float theta;
	float phi;
	float chi;
	float dtheta;
	float dphi;
	float dchi;
};