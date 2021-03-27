#pragma once
#include "IndexedTriangleList.h"
#include <DirectXMath.h>
#include "Math.h"
#include "Util.h"

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
		vertices.emplace_back();
		vertices.back().pos = { 0.0f, 0.0f, -1.0f };
		vertices.back().color = Colors::color[longDiv % Colors::numColors];
		const auto iCenterNear = (unsigned short)(vertices.size() - 1);

		//far center
		vertices.emplace_back();
		vertices.back().pos = { 0.0f, 0.0f, 1.0f };
		vertices.back().color = Colors::color[(longDiv + 1) % Colors::numColors];
		const auto iCenterFar = (unsigned short)(vertices.size() - 1);

		//base vertices
		for (int i = 0; i < longDiv; i++)
		{
			//near base
			{
				vertices.emplace_back();
				auto v = DirectX::XMVector3Transform(
					base,
					DirectX::XMMatrixRotationZ(longitudeAngle * i);
				);
				DirectX::XMStoreFloat3(&vertices.back.pos(), v);
				vertices.back().color = Colors::color[i % Colors::numColors];
			}
			//far base
			{
				vertices.emplace_back();
				auto v = DirectX::XMVector3Transform(
					base,
					DirectX::XMMatrixRotationZ(i * longitudeAngle);
				);
				v = DirectX::XMVectorAdd(v, offset);
				DirectX::XMStoreFloat3(&vertices.back().pos, v);
				vertices.back().color = Colors::color[i % Colors::numColors];
			}
		}

		//side indices
		std::vector<unsigned short> indices;
		for (unsigned short iLong = 0; iLong < longDiv; iLong++)
		{
			const auto i = iLong * 2;
			const auto mod = longDiv * 2;
			indices.push_back(i + 2);
			indices.push_back((i + 2) % mod + 2);
			indices.push_back(i + 1 + 2);
			indices.push_back((i + 2) % mod + 2);
			indices.push_back((i + 3) % mod + 2);
			indices.push_back(i + 1 + 2);
		}

		//base indices
		for (unsigned short iLong = 0; iLong < longDiv; iLong++)
		{
			const auto i = iLong * 2;
			const auto mod = longDiv * 2;
			indices.push_back(i + 2);
			indices.push_back(iCenterNear);
			indices.push_back((i + 2) % mod + 2);
			indices.push_back(iCenterFar);
			indices.push_back(i + 1 + 2);
			indices.push_back((i + 3) % mod + 2);
		}

		return {
			std::move(vertices),
			std::move(indices)
		};
	}

	template<class V>
	static IndexedTraingleList<V> Make()
	{
		return MakeTesselated<V>(24);
	}
};