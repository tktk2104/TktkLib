#include "Tktk2dCollision/BoundingRect.h"

#include "Tktk2dCollision/Body2dBase/CollisionSupport2D.h"

BoundingRect::BoundingRect(
	const Vector2 & rectSize,
	const Vector2 & localPosition
)
	: Body2dBase(
		ShapeType2D::Rect,
		Matrix3::createTranslation(localPosition)
	)
	, m_rectSize(rectSize)
{
}

bool BoundingRect::isCollide(const Body2dBase & other, HitInfo2D * hitinfo) const
{
	switch (other.getShapeType())
	{
	case ShapeType2D::Circle:

		return CollisionSupport2D::collideRectToCircle(*this, other, hitinfo);

	case ShapeType2D::Rect:

		return CollisionSupport2D::collideRectToRect(*this, other, hitinfo);

	case ShapeType2D::Polygon:

		return CollisionSupport2D::collideRectToPolygon(*this, other, hitinfo);
	}
	return false;
}

Vector2 BoundingRect::calculateCornerPoint(CornerType cornerIndex) const
{
	Vector2 worldRectSize = calculateRectSize();

	Vector2 cornerLocalPosition;

	switch (cornerIndex)
	{
	case CornerType::LeftTop:		cornerLocalPosition = Vector2(-worldRectSize.x / 2, -worldRectSize.y / 2); break;
	case CornerType::RightTop:		cornerLocalPosition = Vector2( worldRectSize.x / 2, -worldRectSize.y / 2); break;
	case CornerType::LeftBottom:	cornerLocalPosition = Vector2(-worldRectSize.x / 2,  worldRectSize.y / 2); break;
	case CornerType::RightBottom:	cornerLocalPosition = Vector2( worldRectSize.x / 2,  worldRectSize.y / 2); break;
	}
	return calculatePose().calculateTranslation() + cornerLocalPosition;
}

Vector2 BoundingRect::calculateRectSize() const
{
	auto selfPose = calculatePose();

	// スケールのみを使用したワールド行列を作成する
	auto ignoreRotateWorldMatrix = Matrix3::createScale(selfPose.calculateScale()) * Matrix3::createTranslation(selfPose.calculateTranslation());

	return (Matrix3::createScale(m_rectSize) * ignoreRotateWorldMatrix).calculateScale();
}