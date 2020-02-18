#include "Tktk3dCollision/AxisAlignedBoundingBox.h"

#include "Tktk3dCollision/Body3dBase/CollisionSupport3D.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(
	const Vector3 & boxSize,
	const Vector3& localPosition
) 
	: Body3dBase(
		ShapeType3D::AABB,
		Matrix4::createTranslation(localPosition)
	)
	, m_boxSize(boxSize)
{
}

bool AxisAlignedBoundingBox::isCollide(const Body3dBase & other, HitInfo3D * hitinfo) const
{
	switch (other.getShapeType())
	{
	case ShapeType3D::Sphere:

		return CollisionSupport3D::collideAabbToSphere(*this, other, hitinfo);

	case ShapeType3D::AABB:

		return CollisionSupport3D::collideAabbToAabb(*this, other, hitinfo);
	}
	return false;
}

Vector3 AxisAlignedBoundingBox::calculateCornerPoint(CornerType cornerIndex) const
{
	Vector3 worldBoxSize = calculateBoxSize();

	Vector3 cornerLocalPosition;

	switch (cornerIndex)
	{
	case CornerType::LeftTopBack:		cornerLocalPosition = Vector3(-worldBoxSize.x / 2,  worldBoxSize.y / 2,  worldBoxSize.z / 2); break;
	case CornerType::RightTopBack:		cornerLocalPosition = Vector3( worldBoxSize.x / 2,  worldBoxSize.y / 2,  worldBoxSize.z / 2); break;
	case CornerType::LeftTopFront:		cornerLocalPosition = Vector3(-worldBoxSize.x / 2,  worldBoxSize.y / 2, -worldBoxSize.z / 2); break;
	case CornerType::RightTopFront:		cornerLocalPosition = Vector3( worldBoxSize.x / 2,  worldBoxSize.y / 2, -worldBoxSize.z / 2); break;
	case CornerType::LeftBottomBack:	cornerLocalPosition = Vector3(-worldBoxSize.x / 2, -worldBoxSize.y / 2,  worldBoxSize.z / 2); break;
	case CornerType::RightBottomBack:	cornerLocalPosition = Vector3( worldBoxSize.x / 2, -worldBoxSize.y / 2,  worldBoxSize.z / 2); break;
	case CornerType::LeftBottomFront:	cornerLocalPosition = Vector3(-worldBoxSize.x / 2, -worldBoxSize.y / 2, -worldBoxSize.z / 2); break;
	case CornerType::RightBottomFront:	cornerLocalPosition = Vector3( worldBoxSize.x / 2, -worldBoxSize.y / 2, -worldBoxSize.z / 2); break;
	}

	return calculatePose().calculateTranslation() + cornerLocalPosition;
}

Vector3 AxisAlignedBoundingBox::calculateBoxSize() const
{
	auto selfPose = calculatePose();

	// スケールのみを使用したワールド行列を作成する
	auto ignoreRotateWorldMatrix = Matrix4::createScale(selfPose.calculateScale()) * Matrix4::createTranslation(selfPose.calculateTranslation());

	return (Matrix4::createScale(m_boxSize) * ignoreRotateWorldMatrix).calculateScale();
}

Vector3 AxisAlignedBoundingBox::calculateLocalBoxSize() const
{
	auto selfPose = getLocalMatrix();

	// スケールのみを使用したワールド行列を作成する
	auto ignoreRotateWorldMatrix = Matrix4::createScale(selfPose.calculateScale()) * Matrix4::createTranslation(selfPose.calculateTranslation());

	return (Matrix4::createScale(m_boxSize) * ignoreRotateWorldMatrix).calculateScale();
}
