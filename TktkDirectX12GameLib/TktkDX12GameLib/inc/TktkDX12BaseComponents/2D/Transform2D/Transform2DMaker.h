#ifndef TRANSFORM_2D_MAKER_H_
#define TRANSFORM_2D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Transform2D.h"

namespace tktk
{
	// �uTransform2D�v�����w���p�[�N���X
	class Transform2DMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		Transform2DMaker() = default;
		Transform2DMaker(const Transform2DMaker& other) = default;
		Transform2DMaker& operator = (const Transform2DMaker& other) = default;

	public:

		// �쐬�J�n
		static Transform2DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<Transform2D> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �������W��ݒ肷��
		Transform2DMaker& initPosition(const tktkMath::Vector2& value);

		// �����X�P�[����ݒ肷��
		Transform2DMaker& initScaleRate(const tktkMath::Vector2& value);

		// ������]��ݒ肷��
		Transform2DMaker& initRotationDeg(float value);

		// �e��Transform2D�Ƃ̊֌W���̎�ނ�ݒ肷��
		Transform2DMaker& traceType(TraceParentType value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static Transform2DMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		tktkMath::Vector2	m_initPosition		{ tktkMath::vec2Zero };
		tktkMath::Vector2	m_initScaleRate		{ tktkMath::vec2One };
		float				m_initRotationDeg	{ 0.0f };
		TraceParentType		m_traceType			{ TraceParentType::trace_All };
	};
}
#endif // !TRANSFORM_2D_MAKER_H_