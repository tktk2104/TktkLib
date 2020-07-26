#ifndef BOUNDING_RECT_H_
#define BOUNDING_RECT_H_

#include "Body2dBase/Body2dBase.h"

class BoundingRect
	: public Body2dBase
{
public:

	BoundingRect(
		const tktkMath::Vector2& rectSize,
		const tktkMath::Vector2& localPosition = tktkMath::vec2Zero
	);

	bool isCollide(const Body2dBase& other, HitInfo2D* hitinfo) const override;

public:

	// ���_�̎��
	enum class CornerType
	{
		LeftTop,
		RightTop,
		LeftBottom,
		RightBottom,

		Min = LeftTop,
		Max = RightBottom
	};

public:

	// ���_���W���v�Z
	tktkMath::Vector2 calculateCornerPoint(CornerType cornerIndex) const;

	// �����蔻��̑傫�����v�Z
	tktkMath::Vector2 calculateRectSize() const;

private:

	tktkMath::Vector2 m_rectSize;
};

#endif // !BOUNDING_RECT_H_