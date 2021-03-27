#pragma once
#include "IndexedTriangleList.h"
#include <DirectXMath.h>
#include "Math.h"
#include "Util.h"

class Sphere
{
public:
	template<class V>
	static IndexedTraingleList<V> MakeTesselated(int latDiv, int longDiv)
	{
		assert(latDiv >= 1);
		assert(longDiv >= 1);

		constexpr float radius = 1.0f;
		const auto base = DirectX::XMVectorSet(0.0f, 0.0f, radius, 0.0f);
		const auto latitudeAngle = PI / latDiv;
		const auto longitudeAngle = 2.0f * PI / longDiv;

		std::vector<V> vertices;
		for (int iLat = 1; iLat < latDiv; ++iLat)
		{
			const auto latBase = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationX(iLat * latitudeAngle)
			);
			for (int iLong = 0; iLong < longDiv; ++iLong)
			{
				vertices.emplace_back();
				auto v = DirectX::XMVector3Transform(
					latBase,
					DirectX::XMMatrixRotationZ(iLong * longitudeAngle)
				);
				DirectX::XMStoreFloat3(&vertices.back().pos, v);
				vertices.back().color = Colors::color[(iLat + iLong) % Colors::numColors];
			}
		}

		//add the cap vertices
		const auto iNorthPole = (unsigned short)vertices.size();
		vertices.emplace_back();
		DirectX::XMStoreFloat3(&vertices.back().pos, base);
		vertices.back().color = Colors::color[latDiv % Colors::numColors];
		const auto iSouthPole = (unsigned short)vertices.size();
		vertices.emplace_back();
		DirectX::XMStoreFloat3(&vertices.back().pos, DirectX::XMVectorNegate(base));
		vertices.back().color = Colors::color[longDiv % Colors::numColors];

		const auto calcIdx = [latDiv, longDiv](unsigned short iLat, unsigned short iLong)
		{
			return iLat * longDiv + iLong;
		};
		std::vector<unsigned short> indices;
		for (unsigned short iLat = 0; iLat < latDiv - 2; ++iLat)
		{
			for (unsigned short iLong = 0; iLong < longDiv - 1; ++iLong)
			{
				indices.push_back(calcIdx(iLat, iLong));
				indices.push_back(calcIdx(iLat + 1, iLong));
				indices.push_back(calcIdx(iLat, iLong + 1));
				indices.push_back(calcIdx(iLat, iLong + 1));
				indices.push_back(calcIdx(iLat + 1, iLong));
				indices.push_back(calcIdx(iLat + 1, iLong + 1));
			}
			// wrap band
			indices.push_back(calcIdx(iLat, longDiv - 1));
			indices.push_back(calcIdx(iLat + 1, longDiv - 1));
			indices.push_back(calcIdx(iLat, 0));
			indices.push_back(calcIdx(iLat, 0));
			indices.push_back(calcIdx(iLat + 1, longDiv - 1));
			indices.push_back(calcIdx(iLat + 1, 0));
		}

		// cap fans
		for (unsigned short iLong = 0; iLong < longDiv - 1; iLong++)
		{
			// north
			indices.push_back(iNorthPole);
			indices.push_back(calcIdx(0, iLong));
			indices.push_back(calcIdx(0, iLong + 1));
			// south
			indices.push_back(calcIdx(latDiv - 2, iLong + 1));
			indices.push_back(calcIdx(latDiv - 2, iLong));
			indices.push_back(iSouthPole);
		}
		// wrap triangles
		// north
		indices.push_back(iNorthPole);
		indices.push_back(calcIdx(0, longDiv - 1));
		indices.push_back(calcIdx(0, 0));
		// south
		indices.push_back(calcIdx(latDiv - 2, 0));
		indices.push_back(calcIdx(latDiv - 2, longDiv - 1));
		indices.push_back(iSouthPole);

		return { std::move(vertices),std::move(indices) };
	}

	template<class V>
	static IndexedTraingleList<V> Make()
	{
		return MakeTesselated<V>(12, 24);
	}
};