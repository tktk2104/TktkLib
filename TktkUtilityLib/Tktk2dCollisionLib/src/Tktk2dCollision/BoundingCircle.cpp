#include "Tktk2dCollision/BoundingCircle.h"

#include "Tktk2dCollision/Body2dBase/CollisionSupport2D.h"

BoundingCircle::BoundingCircle(
	float radius,
	const Vector2 & localPosition
)
	: Body2dBase(
		ShapeType2D::Circle,
		Matrix3::createTranslation(localPosition)
	)
	, m_radius(radius)
{
}

bool BoundingCircle::isCollide(const Body2dBase & other, HitInfo2D * hitinfo) const
{
	switch (other.getShapeType())
	{
	case ShapeType2D::Circle:

		return CollisionSupport2D::collideCircleToCircle(*this, other, hitinfo);

	case ShapeType2D::Rect:

		return CollisionSupport2D::collideCircleToRect(*this, other, hitinfo);

	case ShapeType2D::Polygon:

		return CollisionSupport2D::collideCircleToPolygon(*this, other, hitinfo);
	}
	return false;
}

float BoundingCircle::calculateRadius() const
{
	Matrix3 worldRadius = Matrix3::createScale(Vector2(m_radius, m_radius)) * calculatePose();

	return worldRadius.calculateScale().x;
}

float BoundingCircle::calculateLocalRadius() const
{
	Matrix3 localRadius = Matrix3::createScale(Vector2(m_radius, m_radius)) * getLocalMatrix();

	return localRadius.calculateScale().x;
}
