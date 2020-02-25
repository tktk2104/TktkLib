#ifndef BOUNDING_POLYGON_2D_H_
#define BOUNDING_POLYGON_2D_H_

#include <vector>
#include "Body2dBase/Body2dBase.h"

class BoundingPolygon2d
	: public Body2dBase
{
public:

	BoundingPolygon2d(
		const std::vector<Vector2>& vertexs,
		const Vector2& localPosition = Vector2::zero
	);

	bool isCollide(const Body2dBase& other, HitInfo2D* hitinfo) const override;

public:

	// 頂点座標を計算
	std::vector<Vector2> calculateVertexs() const;

	// ローカルの頂点座標を計算
	std::vector<Vector2> calculateLocalVertexs() const;

private:

	std::vector<Vector2> m_vertexs;
};

#endif // !BOUNDING_POLYGON_2D_H_