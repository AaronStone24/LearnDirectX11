#pragma once
#include "IndexedTriangleList.h"
#include <DirectXMath.h>
#include "Math.h"

class Prism
{
public:
	template<class V>
	static IndexedTraingleList<V> MakeTesselated(int longDiv)
	{
		assert(longDiv >= 1);

		const auto base = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
		const auto offset = DirectX::XMVectorSet(0.0f, 0.0f, 2.0f, 0.0f);
		const float longitudeAngle = 2.0f * PI / float(longDiv);

		//near center
		std::vector<V> vertices;

	}
};