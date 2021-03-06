#ifndef BODY_3D_BASE_H_
#define BODY_3D_BASE_H_

#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix4.h>

#include "ShapeType3D.h"
#include "HitInfo3D.h"

class Body3dBase
{
public:

	Body3dBase(
		ShapeType3D shapeType,
		const Matrix4 & localMatrix
	);

	virtual ~Body3dBase();

public:

	virtual bool isCollide(const Body3dBase& other, HitInfo3D* hitinfo) const = 0;

public:

	void transform(const Matrix4& world);

	Matrix4 calculatePose() const;

	const Matrix4& getWorldMatrix() const;

	const Matrix4& getLocalMatrix() const;
	void setLocalMatrix(const Matrix4 & localMatrix);

	ShapeType3D getShapeType() const;

private:

	// 図形の種類
	ShapeType3D m_shapeType;

	// ワールドの行列
	Matrix4 m_worldMatrix;

	// ローカルの行列
	Matrix4 m_localMatrix;
};
#endif // !BODY_3D_BASE_H_