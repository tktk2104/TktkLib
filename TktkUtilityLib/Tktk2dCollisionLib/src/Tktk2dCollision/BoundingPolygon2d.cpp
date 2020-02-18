#include "Tktk2dCollision/BoundingPolygon2d.h"

#include "Tktk2dCollision/Body2dBase/CollisionSupport2D.h"

BoundingPolygon2d::BoundingPolygon2d(
	const std::vector<Vector2>& vertexs,
	const Vector2 & localPosition
)
	: Body2dBase(
		ShapeType2D::Polygon,
		Matrix3::createTranslation(localPosition)
	)
	, m_vertexs(vertexs)
{
}

bool BoundingPolygon2d::isCollide(const Body2dBase & other, HitInfo2D * hitinfo) const
{
	switch (other.getShapeType())
	{
	case ShapeType2D::Circle:

		return CollisionSupport2D::collidePolygonToCircle(*this, other, hitinfo);

	case ShapeType2D::Rect:

		return CollisionSupport2D::collidePolygonToRect(*this, other, hitinfo);

	case ShapeType2D::Polygon:

		return CollisionSupport2D::collidePolygonToPolygon(*this, other, hitinfo);
	}
	return false;
}

std::vector<Vector2> BoundingPolygon2d::calculateVertexs() const
{
	std::vector<Vector2> transformVertexs = m_vertexs;

	Matrix3 pose = calculatePose();

	for (auto & transformVertex : transformVertexs)
	{
		transformVertex *= pose;
	}
	return transformVertexs;
}

std::vector<Vector2> BoundingPolygon2d::calculateLocalVertexs() const
{
	std::vector<Vector2> transformVertexs = m_vertexs;

	Matrix3 pose = getLocalMatrix();

	for (auto & transformVertex : transformVertexs)
	{
		transformVertex *= pose;
	}
	return transformVertexs;
}
