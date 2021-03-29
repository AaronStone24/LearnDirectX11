#pragma once

#include <vector>
#include <array>
#include "IndexedTriangleList.h"
#include "Math.h"
#include "Util.h"

class Plane
{
public:
	template<class V>
	static IndexedTraingleList<V> MakeTesselated(int width, int height, int div_x, int div_y)
	{
		assert(div_x >= 1);
		assert(div_y >= 1);

		//constexpr float width = 2.0f;
		//constexpr float height = 2.0f;
		const int nVertices_x = div_x + 1;
		const int nVertices_y = div_y + 1;
		std::vector<V> vertices(nVertices_x * nVertices_y);

		{
			const float side_x = width / 2.0f;
			const float side_y = height / 2.0f;
			const float dx = width / float(div_x);
			const float dy = height / float(div_y);
			const auto bottomLeft = DirectX::XMVectorSet(-side_x, -side_y, 0.0f, 0.0f);

			for (int y = 0, i = 0; y < nVertices_y; y++)
			{
				const float y_pos = float(y) * dy;
				for (int x = 0; x < nVertices_x; x++, i++)
				{
					const auto v = DirectX::XMVectorAdd(
						bottomLeft,
						DirectX::XMVectorSet(float(x) * dx, 0.0f, y_pos, 0.0f)
					);
					DirectX::XMStoreFloat3(&vertices[i].pos, v);
					vertices[i].color = Colors::color[i % Colors::numColors];
				}
			}
		}

		std::vector<unsigned short> indices;
		indices.reserve(sq(div_x * div_y) * 6);
		{
			const auto vxy2i = [nVertices_x](size_t x, size_t y)
			{
				return (unsigned short)(y * nVertices_x + x);
			};
			for (size_t y = 0; y < div_y; y++)
			{
				for (size_t x = 0; x < div_x; x++)
				{
					const std::array<unsigned short, 4> indexArray =
						{ vxy2i(x, y), vxy2i(x + 1, y), vxy2i(x, y + 1), vxy2i(x + 1, y + 1) };
					indices.push_back(indexArray[0]);
					indices.push_back(indexArray[2]);
					indices.push_back(indexArray[1]);
					indices.push_back(indexArray[1]);
					indices.push_back(indexArray[2]);
					indices.push_back(indexArray[3]);
				}
			}
		}

		return { std::move(vertices), std::move(indices) };
	}

	template<class V>
	static IndexedTraingleList<V> Make()
	{
		return MakeTesselated<V>(1, 1, 1, 1);
	}
};