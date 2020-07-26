#ifndef BOUNDING_POLYGON_2D_H_
#define BOUNDING_POLYGON_2D_H_

#include <vector>
#include "Body2dBase/Body2dBase.h"

class BoundingPolygon2d
	: public Body2dBase
{
public:

	BoundingPolygon2d(
		const std::vector<tktkMath::Vector2>& vertexs,
		const tktkMath::Vector2& localPosition = tktkMath::vec2Zero
	);

	bool isCollide(const Body2dBase& other, HitInfo2D* hitinfo) const override;

public:

	// ���_���W���v�Z
	std::vector<tktkMath::Vector2> calculateVertexs() const;

	// ���[�J���̒��_���W���v�Z
	std::vector<tktkMath::Vector2> calculateLocalVertexs() const;

private:

	std::vector<tktkMath::Vector2> m_vertexs;
};

#endif // !BOUNDING_POLYGON_2D_H_