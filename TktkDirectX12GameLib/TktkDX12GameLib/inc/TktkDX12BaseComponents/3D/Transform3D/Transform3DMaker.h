#ifndef TRANSFORM_3D_MAKER_H_
#define TRANSFORM_3D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Transform3D.h"

namespace tktk
{
	// �uTransform3D�v�����w���p�[�N���X
	class Transform3DMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		Transform3DMaker() = default;
		Transform3DMaker(const Transform3DMaker& other) = default;
		Transform3DMaker& operator = (const Transform3DMaker& other) = default;

	public:

		// �쐬�J�n
		static Transform3DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<Transform3D> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �������W��ݒ肷��
		Transform3DMaker& initPosition(const tktkMath::Vector3& value);

		// �����X�P�[����ݒ肷��
		Transform3DMaker& initScaleRate(const tktkMath::Vector3& value);

		// ������]��ݒ肷��
		Transform3DMaker& initRotation(const tktkMath::Quaternion& value);

		// ������]��ݒ肷��i�I�C���[�p�j
		Transform3DMaker& initRotation(const tktkMath::Vector3& value);

		// �s�񂩂珉���p�����[�^��ݒ肷��i���W�ϊ����̂݁j
		Transform3DMaker& setInitTransformFromMatrix(const tktkMath::Matrix4& value);

		// �e��Transform3D�Ƃ̊֌W���̎�ނ�ݒ肷��
		Transform3DMaker& traceType(TraceParentType value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static Transform3DMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr			m_user			{  };
		tktkMath::Vector3		m_initPosition	{ tktkMath::vec3Zero };
		tktkMath::Vector3		m_initScaleRate	{ tktkMath::vec3One };
		tktkMath::Quaternion	m_initRotation	{ tktkMath::quaternionIdentity };
		TraceParentType			m_traceType		{ TraceParentType::trace_All };
	};
}
#endif // !TRANSFORM_3D_MAKER_H_