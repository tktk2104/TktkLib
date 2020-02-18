#include "Tktk2dCollision/Body2dBase/Body2dBase.h"

Body2dBase::Body2dBase(
	ShapeType2D shapeType,
	const Matrix3 & localMatrix
)
	: m_shapeType(shapeType)
	, m_worldMatrix(Matrix3::identity)
	, m_localMatrix(localMatrix)
{
}

Body2dBase::~Body2dBase()
{
}

void Body2dBase::transform(const Matrix3 & world)
{
	m_worldMatrix = world;
}

Matrix3 Body2dBase::calculatePose() const
{
	return m_localMatrix * m_worldMatrix;
}

const Matrix3 & Body2dBase::getWorldMatrix() const
{
	return m_worldMatrix;
}

const Matrix3 & Body2dBase::getLocalMatrix() const
{
	return m_localMatrix;
}

void Body2dBase::setLocalMatrix(const Matrix3 & localMatrix)
{
	m_localMatrix = localMatrix;
}

ShapeType2D Body2dBase::getShapeType() const
{
	return m_shapeType;
}
