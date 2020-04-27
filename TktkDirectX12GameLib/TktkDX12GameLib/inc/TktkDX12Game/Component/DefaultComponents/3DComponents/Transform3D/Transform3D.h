#ifndef TRANSFORM_3D_H_
#define TRANSFORM_3D_H_

#include <TktkMath/Structs/Matrix4.h>
#include <TktkMath/Structs/Quaternion.h>
#include <TktkMath/Structs/Vector3.h>
#include "../../../ComponentBase.h"
#include "../../2DComponents/Transform2D/TraceParentType.h"

//#include <TktkAppend2DComponent/TraceParentType.h>

namespace tktk
{
	// �R�����̎��g�̍��W�A��]�A�X�P�[�����Ǘ�����R���|�[�l���g
	class Transform3D
		: public ComponentBase
	{
	public:

		Transform3D(
			const tktkMath::Vector3& initPosition,	// �������W
			const tktkMath::Vector3& initScaleRate,	// �����X�P�[��
			const tktkMath::Quaternion& initRotation,	// ������]
			TraceParentType traceType		// �e��Transform2D�Ƃ̊֌W���̎��
		);

	public:

		// <PolymorphismFunc>
		void start();
		void afterChangeParent(const GameObjectPtr& beforParent);

	public:

		// ���[���h���W���擾
		const tktkMath::Vector3& getWorldPosition() const;
		// ���[���h�X�P�[�����擾
		const tktkMath::Vector3& getWorldScaleRate() const;
		// ���[���h��]���擾
		const tktkMath::Quaternion& getWorldRotation() const;
		// ���[���h��]�i�I�C���[�p�j���v�Z
		tktkMath::Vector3 calculateWorldEulerAngles() const;

		// ���[�J�����W���擾
		const tktkMath::Vector3& getLocalPosition() const;
		// ���[�J���X�P�[�����擾
		const tktkMath::Vector3& getLocalScaleRate() const;
		// ���[�J����]���擾
		const tktkMath::Quaternion& getLocalRotation() const;
		// ���[�J����]�i�I�C���[�p�j���v�Z
		tktkMath::Vector3 calculateLocalEulerAngles() const;

		// ���[���h�̍s����v�Z
		tktkMath::Matrix4 calculateWorldMatrix() const;
		// ���[�J���̍s����v�Z
		tktkMath::Matrix4 calculateLocalMatrix() const;

		// ���[���h���W���w�蕪��������
		void addWorldPosition(const tktkMath::Vector3& position);
		// ���[���h��]���w�蕪��������
		void addWorldRotation(const tktkMath::Quaternion& rotation);
		// ���[���h��]�i�I�C���[�p�j���w�蕪��������
		void addWorldEulerAngles(const tktkMath::Vector3& eulerAngles);

		// ���[�J�����W���w�蕪��������
		void addLocalPosition(const tktkMath::Vector3& position);
		// ���[�J���X�P�[�����w�蕪��������
		void addLocalScaleRate(const tktkMath::Vector3& scaleRate);
		// ���[�J����]���w�蕪��������
		void addLocalRotation(const tktkMath::Quaternion& rotation);
		// ���[�J����]�i�I�C���[�p�j���w�蕪��������
		void addLocalEulerAngles(const tktkMath::Vector3& eulerAngles);

		// ���[���h���W��ݒ�
		void setWorldPosition(const tktkMath::Vector3& position);
		// ���[���h��]��ݒ�
		void setWorldRotation(const tktkMath::Quaternion& rotation);
		// ���[���h��]�i�I�C���[�p�j��ݒ�
		void setWorldEulerAngles(const tktkMath::Vector3& eulerAngles);
		// �uaxis�v�����Ƃ��āudegree�v�x������]�������[���h��]��ݒ�
		void setWorldAxisAngle(const tktkMath::Vector3& axis, float degree);

		// ���[�J�����W��ݒ�
		void setLocalPosition(const tktkMath::Vector3& position);
		// ���[�J���X�P�[����ݒ�
		void setLocalScaleRate(const tktkMath::Vector3& scaleRate);
		// ���[�J����]��ݒ�
		void setLocalRotation(const tktkMath::Quaternion& rotation);
		// ���[�J����]�i�I�C���[�p�j��ݒ�
		void setLocalEulerAngles(const tktkMath::Vector3& eulerAngles);
		// �uaxis�v�����Ƃ��āudegree�v�x������]�������[�J����]��ݒ�
		void setLocalAxisAngle(const tktkMath::Vector3& axis, float degree);

	public:

		// ���[���h��Ԃ̍�����W�n�̑O���x�N�g�����v�Z�iDirectX���j
		tktkMath::Vector3 calculateWorldForwardLH() const;
		// ���[���h��Ԃ̉E����W�n�̑O���x�N�g�����v�Z�iOpenGL���j
		tktkMath::Vector3 calculateWorldForwardRH() const;
		// ���[���h��Ԃ̉E���x�N�g�����v�Z
		tktkMath::Vector3 calculateWorldRight() const;
		// ���[���h��Ԃ̏���x�N�g�����v�Z
		tktkMath::Vector3 calculateWorldUp() const;

		// ���[���h��Ԃ̍�����W�n�̑O���x�N�g�����v�Z�iDirectX���j
		tktkMath::Vector3 calculateLocalForwardLH() const;
		// ���[���h��Ԃ̉E����W�n�̑O���x�N�g�����v�Z�iOpenGL���j
		tktkMath::Vector3 calculateLocalForwardRH() const;
		// ���[���h��Ԃ̉E���x�N�g�����v�Z
		tktkMath::Vector3 calculateLocalRight() const;
		// ���[���h��Ԃ̏���x�N�g�����v�Z
		tktkMath::Vector3 calculateLocalUp() const;

		// ���[���h��Ԃ̍�����W�n�̑O���x�N�g����ݒ�iDirectX���j
		void setWorldForwardLH(const tktkMath::Vector3& forward);
		// ���[���h��Ԃ̉E����W�n�̑O���x�N�g����ݒ�iOpenGL���j
		void setWorldForwardRH(const tktkMath::Vector3& forward);
		// ���[���h��Ԃ̉E���x�N�g����ݒ�
		void setWorldRight(const tktkMath::Vector3& right);
		// ���[���h��Ԃ̏���x�N�g����ݒ�
		void setWorldUp(const tktkMath::Vector3& up);

		// ���[�J����Ԃ̍�����W�n�̑O���x�N�g����ݒ�iDirectX���j
		void setLocalForwardLH(const tktkMath::Vector3& forward);
		// ���[�J����Ԃ̉E����W�n�̑O���x�N�g����ݒ�iOpenGL���j
		void setLocalForwardRH(const tktkMath::Vector3& forward);
		// ���[�J����Ԃ̉E���x�N�g����ݒ�
		void setLocalRight(const tktkMath::Vector3& right);
		// ���[�J����Ԃ̏���x�N�g����ݒ�
		void setLocalUp(const tktkMath::Vector3& up);

		// �w���Transform3D�̕��������悤�Ɏ��g�̃��[���h�s���ϊ�����
		void lookAt(const ComponentPtr<Transform3D>& target, const tktkMath::Vector3& worldUp = tktkMath::vec3Up);
		// �w��̍��W�̕��������悤�Ɏ��g�̃��[���h�s���ϊ�����
		void lookAt(const tktkMath::Vector3& target, const tktkMath::Vector3& worldUp = tktkMath::vec3Up);

		// �w��̍��W�𒆐S�Ƃ������Ŏw�肵���p�x������]������B
		void rotateAround(const tktkMath::Vector3& worldPoint, const tktkMath::Vector3& axis, float angle);

		//// ���[�J�����W���烏�[���h���W�ւƕϊ������s����擾����
		//Matrix4 calculateLocalToWorldMatrix() const;
		//// ���[���h���W���烍�[�J�����W�ւƕϊ������s����擾����
		//Matrix4 calculateWorldToLocalMatrix() const;

	private:

		// ������Transform3D��Ǐ]����̂Ɏg�p���郏�[���h�s����v�Z
		static tktkMath::Matrix4 calculateTraceUseMat(const ComponentPtr<Transform3D>& target, TraceParentType traceType);

		// ������Transform3D��Ǐ]����̂Ɏg�p����X�P�[���l���v�Z
		static tktkMath::Vector3 calculateTraceUseScale(const ComponentPtr<Transform3D>& target, TraceParentType traceType);

		// ������Transform3D��Ǐ]����̂Ɏg�p����t�X�P�[���l���v�Z
		static tktkMath::Vector3 calculateTraceUseInvScale(const ComponentPtr<Transform3D>& target, TraceParentType traceType);

	private:

		// �V�������[�J���s����w�肵�Ď��g�̃��[�J���̃g�����X�t�H�[�����X�V����
		void updateLocalTransform(const tktkMath::Matrix4& newLocalMat, const tktkMath::Vector3 newLocalScale);

		// �V�������[���h�s����w�肵�Ď��g�̃��[���h�̃g�����X�t�H�[�����X�V����
		void updateWorldTransform(const tktkMath::Matrix4& newWorldMat, const tktkMath::Vector3 newWorldScale);

		// �e��Transform3D��T��
		ComponentPtr<Transform3D> findParentTransform3D() const;

		// �S�Ă̎q����Transform3D���X�V����
		void updateAllChildTransform();

		// �w�肵���q����Transform3D���X�V����
		void updateChildTransform(const GameObjectPtr& child);

		// �e��Transform3D�̒Ǐ]���J�n
		void enableParentTransform(const GameObjectPtr& curParent);

		// �e��Transform3D�̒Ǐ]���I��
		void disableParentTransform(const GameObjectPtr& beforParent);

		// �匳��Transform����S�Ă̎q�����X�V����i���|�C���^�Łj
		void findAndUpdateRootTransform(Transform3D* curTransform);

		// �匳��Transform����S�Ă̎q�����X�V����iCfpPtr�Łj
		void findAndUpdateRootTransform(const ComponentPtr<Transform3D>& curTransform);

	private:

		// ���[�J���̍��W
		tktkMath::Vector3 m_localPosition{ tktkMath::vec3Zero };
		// ���[�J���̃X�P�[��
		tktkMath::Vector3 m_localScaleRate{ tktkMath::vec3One };
		// ���[�J���̉�]
		tktkMath::Quaternion m_localRotation{ tktkMath::quaternionIdentity };

		// ���[���h�̍��W
		tktkMath::Vector3 m_worldPosition{ tktkMath::vec3Zero };
		// ���[���h�̃X�P�[��
		tktkMath::Vector3 m_worldScaleRate{ tktkMath::vec3One };
		// ���[�J���̉�]
		tktkMath::Quaternion m_worldRotation{ tktkMath::quaternionIdentity };

		// �e��Transform3D�Ƃ̊֌W��
		TraceParentType m_traceType;
	};
}
#endif // !TRANSFORM_3D_H_