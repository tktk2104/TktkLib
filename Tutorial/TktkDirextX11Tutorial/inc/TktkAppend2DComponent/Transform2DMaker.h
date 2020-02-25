#ifndef TRANSFORM_2D_MAKER_H_
#define TRANSFORM_2D_MAKER_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "Transform2D.h"

namespace tktk
{
	// Transform2D�̃C���X�^���X���쐬����N���X
	class Transform2DMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static Transform2DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<Transform2D> create();

		// ���W��ݒ�
		Transform2DMaker& position(const Vector2& value);

		// �X�P�[����ݒ�
		Transform2DMaker& scaleRate(const Vector2& value);

		// ��]�p�x��ݒ�
		Transform2DMaker& rotationDeg(float value);

		// �e��Transform2D�Ƃ̊֌W����ݒ�
		Transform2DMaker& traceType(TraceParentType value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static Transform2DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		Vector2 m_initPosition{ Vector2::zero };
		Vector2 m_initScaleRate{ Vector2::one };
		float m_initRotationDeg{ 0.0f };
		TraceParentType m_traceType{ TraceParentType::TRACE_PARENT_ALL };
	};
}
#endif // !TRANSFORM_2D_MAKER_H_