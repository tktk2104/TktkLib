#ifndef TRANSFORM_2D_H_
#define TRANSFORM_2D_H_

#include <TktkMath/Structs/Matrix3.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "TraceParentType.h"

namespace tktk
{
	// �Q�����̎��g�̍��W�A��]�A�X�P�[�����Ǘ�����R���|�[�l���g
	class Transform2D
		: public ComponentBase
	{
	public:

		Transform2D(
			const tktkMath::Vector2& initPosition,	// �������W
			const tktkMath::Vector2& initScaleRate,	// �����X�P�[��
			float initRotationDeg,			// ������]
			TraceParentType traceType		// �e��Transform2D�Ƃ̊֌W���̎��
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// ���[���h���W���擾
		const tktkMath::Vector2& getWorldPosition() const;
		// ���[���h�X�P�[�����擾
		const tktkMath::Vector2& getWorldScaleRate() const;
		// ���[���h��]���擾
		float getWorldRotationDeg() const;

		// ���[�J�����W���擾
		const tktkMath::Vector2& getLocalPosition() const;
		// ���[�J���X�P�[�����擾
		const tktkMath::Vector2& getLocalScaleRate() const;
		// ���[�J����]���擾
		float getLocalRotationDeg() const;

		// ���[���h�̍s����v�Z
		tktkMath::Matrix3 calculateWorldMatrix() const;
		// ���[�J���̍s����v�Z
		tktkMath::Matrix3 calculateLocalMatrix() const;

		// ���[���h���W���w�蕪��������
		void addWorldPosition(const tktkMath::Vector2& position);
		// ���[���h�X�P�[�����w�蕪��������
		void addWorldScaleRate(const tktkMath::Vector2& scaleRate);
		// ���[���h��]���w�蕪��������
		void addWorldRotationDeg(float rotationDeg);

		// ���[�J�����W���w�蕪��������
		void addLocalPosition(const tktkMath::Vector2& position);
		// ���[�J���X�P�[�����w�蕪��������
		void addLocalScaleRate(const tktkMath::Vector2& scaleRate);
		// ���[�J����]���w�蕪��������
		void addLocalRotationDeg(float rotationDeg);

		// ���[���h���W��ݒ�
		void setWorldPosition(const tktkMath::Vector2& position);
		// ���[���h�X�P�[����ݒ�
		void setWorldScaleRate(const tktkMath::Vector2& scaleRate);
		// ���[���h��]��ݒ�
		void setWorldRotationDeg(float rotationDeg);

		// ���[�J�����W��ݒ�
		void setLocalPosition(const tktkMath::Vector2& position);
		// ���[�J���X�P�[����ݒ�
		void setLocalScaleRate(const tktkMath::Vector2& scaleRate);
		// ���[�J����]��ݒ�
		void setLocalRotationDeg(float rotationDeg);

	private:

		// �V�������[�J���s����w�肵�Ď��g�̃��[�J���̃g�����X�t�H�[�����X�V����
		void updateLocalTransform(const tktkMath::Matrix3& newLocalMat);

		// �V�������[���h�s����w�肵�Ď��g�̃��[���h�̃g�����X�t�H�[�����X�V����
		void updateWorldTransform(const tktkMath::Matrix3& newWorldMat);

		// �e��Transform2D��Ǐ]����̂Ɏg�p���郏�[���h�s����擾
		tktkMath::Matrix3 calculateParentTraceUseMat();

		// �e��Transform2D���擾
		ComponentPtr<Transform2D> findParentTransform2D() const;

		// �S�Ă̎q����Transform2D���X�V����
		void updateAllChildTransform();

		// �w�肵���q����Transform2D���X�V����
		void updateChildTransform(const GameObjectPtr& child);

		// �e��Transform2D��Ǐ]���邩�𔻒肷��
		bool isTransformParentCheck(const ComponentPtr<Transform2D>& parentTransform2D);

		// �e��Transform2D�̒Ǐ]���J�n
		void enableParentTransform();

		// �e��Transform2D�̒Ǐ]���I��
		void disableParentTransform();

		// �匳��Transform����S�Ă̎q�����X�V����i���|�C���^�Łj
		void findAndUpdateRootTransform(Transform2D* curTransform);

		// �匳��Transform����S�Ă̎q�����X�V����iCfpPtr�Łj
		void findAndUpdateRootTransform(const ComponentPtr<Transform2D>& curTransform);

	private:

		// �e��Transform��Ǐ]���Ă��邩�H
		bool m_isTransformParent{ false };

		// ���[�J���̍��W
		tktkMath::Vector2 m_localPosition{ tktkMath::vec2Zero };
		// ���[�J���̃X�P�[��
		tktkMath::Vector2 m_localScaleRate{ tktkMath::vec2One };
		// ���[�J���̉�]�i�x���@�j
		float m_localRotationDeg{ 0.0f };

		// ���[���h�̍��W
		tktkMath::Vector2 m_worldPosition{ tktkMath::vec2Zero };
		// ���[���h�̃X�P�[��
		tktkMath::Vector2 m_worldScaleRate{ tktkMath::vec2One };
		// ���[�J���̉�]�i�x���@�j
		float m_worldRotationDeg{ 0.0f };

		// �e��Transform2D�Ƃ̊֌W��
		TraceParentType m_traceType;
	};
}
#endif // !TRANSFORM_2D_H_