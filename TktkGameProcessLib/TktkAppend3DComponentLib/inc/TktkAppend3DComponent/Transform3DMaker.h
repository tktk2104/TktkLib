#ifndef TRANSFORM_3D_MAKER_H_
#define TRANSFORM_3D_MAKER_H_

#include <TktkMath/Vector3.h>
#include <TktkMath/Quaternion.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "Transform3D.h"

namespace tktk
{
	// Transform3D���쐬����N���X
	class Transform3DMaker
	{
	public:

		// �쐬�J�n
		static Transform3DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<Transform3D> create();

		// �������W��ݒ�
		Transform3DMaker& position(const Vector3& value);

		// �����X�P�[����ݒ�
		Transform3DMaker& scaleRate(const Vector3& value);

		// ������]��ݒ�i�N�I�[�^�j�I���ł̎w��j
		Transform3DMaker& rotation(const Quaternion& value);

		// ������]��ݒ�i�I�C���[�p�ł̎w��j
		Transform3DMaker& rotationDeg(const Vector3& value);

		// �e��Transform3D�Ƃ̊֌W����ݒ�
		Transform3DMaker& traceType(TraceParentType value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static Transform3DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		Vector3 m_initPosition{ Vector3::zero };
		Vector3 m_initScaleRate{ Vector3::one };
		Quaternion m_initRotation{ Quaternion::identity };
		TraceParentType m_traceType{ TraceParentType::TRACE_PARENT_ALL };
	};
}
#endif // !TRANSFORM_3D_MAKER_H_