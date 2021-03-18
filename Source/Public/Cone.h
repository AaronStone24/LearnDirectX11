#pragma once
#include "IndexedTriangleList.h"
#include <DirectXMath.h>
#include "Math.h"
#include "Util.h"
#include <random>

class Cone
{
public:
	template<class V>
	static IndexedTraingleList<V> MakeTesselated(int longDiv)
	{
		assert(longDiv >= 3);

		const auto base = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
		const float longitudeAngle = 2.0f * PI / longDiv;

		//base vertices
		std::vector<V> vertices;
		for (int iLong = 0; iLong < longDiv; iLong++)
		{
			vertices.emplace_back();
			auto v = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationZ(longitudeAngle * iLong)
			);
			DirectX::XMStoreFloat3(&vertices.back().pos, v);
			vertices.back().color = Colors::color[iLong % Colors::color.size()];
		}

		//the center
		vertices.emplace_back();
		vertices.back().pos = { 0.0f, 0.0f, -1.0f };
		vertices.back().color = Colors::color[longDiv % Colors::color.size()];
		const auto iCenter = (unsigned short)(vertices.size() - 1);

		//the tip
		vertices.emplace_back();
		vertices.back().pos = { 0.0f, 0.0f, 1.0f };
		vertices.back().color = Colors::color[(longDiv + 1) % Colors::color.size()];
		const auto iTip = (unsigned short)(vertices.size() - 1);
		
		//base indices
		std::vector<unsigned short> indices;
		for (unsigned short iLong = 0; iLong < longDiv; iLong++)
		{
			indices.push_back(iCenter);
			indices.push_back((iLong + 1) % longDiv);
			indices.push_back(iLong);
		}

		//cone indices
		for (unsigned short iLong = 0; iLong < longDiv; iLong++)
		{
			indices.push_back(iLong);
			indices.push_back((iLong + 1) % longDiv);
			indices.push_back(iTip);
		}

		return { std::move(vertices), std::move(indices) };
	}

	template<class V>
	static IndexedTraingleList<V> Make()
	{
		return MakeTesselated<V>(24);
	}
};