#ifndef BODY_2D_BASE_H_
#define BODY_2D_BASE_H_

#include <TktkMath/Vector2.h>
#include <TktkMath/Matrix3.h>

#include "ShapeType2D.h"
#include "HitInfo2D.h"

class Body2dBase
{
public:

	Body2dBase(
		ShapeType2D shapeType,
		const Matrix3 & localMatrix
	);

	virtual ~Body2dBase();

public:

	virtual bool isCollide(const Body2dBase& other, HitInfo2D* hitinfo) const = 0;

public:

	void transform(const Matrix3& world);

	Matrix3 calculatePose() const;

	const Matrix3& getWorldMatrix() const;

	const Matrix3& getLocalMatrix() const;
	void setLocalMatrix(const Matrix3 & localMatrix);

	ShapeType2D getShapeType() const;

private:

	// 図形の種類
	ShapeType2D m_shapeType;

	// ワールドの行列
	Matrix3 m_worldMatrix;

	// ローカルの行列
	Matrix3 m_localMatrix;
};
#endif // !BODY_2D_BASE_H_