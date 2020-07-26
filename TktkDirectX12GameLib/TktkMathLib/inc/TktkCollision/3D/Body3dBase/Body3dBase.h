#ifndef BODY_3D_BASE_H_
#define BODY_3D_BASE_H_

#include "../../../TktkMath/Structs/Matrix4.h"
#include "ShapeType3D.h"
#include "HitInfo3D.h"

class Body3dBase
{
public:

	Body3dBase(
		ShapeType3D shapeType,
		const tktkMath::Matrix4 & localMatrix
	);

	virtual ~Body3dBase();

public:

	virtual bool isCollide(const Body3dBase& other, HitInfo3D* hitinfo) const = 0;

public:

	void transform(const tktkMath::Matrix4& world);

	tktkMath::Matrix4 calculatePose() const;

	const tktkMath::Matrix4& getWorldMatrix() const;

	const tktkMath::Matrix4& getLocalMatrix() const;
	void setLocalMatrix(const tktkMath::Matrix4 & localMatrix);

	ShapeType3D getShapeType() const;

private:

	// �}�`�̎��
	ShapeType3D m_shapeType;

	// ���[���h�̍s��
	tktkMath::Matrix4 m_worldMatrix;

	// ���[�J���̍s��
	tktkMath::Matrix4 m_localMatrix;
};
#endif // !BODY_3D_BASE_H_