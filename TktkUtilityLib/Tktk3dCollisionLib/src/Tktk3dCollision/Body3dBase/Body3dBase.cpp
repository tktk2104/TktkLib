#include "Tktk3dCollision/Body3dBase/Body3dBase.h"

Body3dBase::Body3dBase(
	ShapeType3D shapeType,
	const Matrix4 & localMatrix
)
	: m_shapeType(shapeType)
	, m_worldMatrix(Matrix4::identity)
	, m_localMatrix(localMatrix)
{
}

Body3dBase::~Body3dBase()
{
}

void Body3dBase::transform(const Matrix4 & world)
{
	m_worldMatrix = world;
}

Matrix4 Body3dBase::calculatePose() const
{
	return m_localMatrix * m_worldMatrix;
}

const Matrix4 & Body3dBase::getWorldMatrix() const
{
	return m_worldMatrix;
}

const Matrix4& Body3dBase::getLocalMatrix() const
{
	return m_localMatrix;
}

void Body3dBase::setLocalMatrix(const Matrix4 & localMatrix)
{
	m_localMatrix = localMatrix;
}

ShapeType3D Body3dBase::getShapeType() const
{
	return m_shapeType;
}