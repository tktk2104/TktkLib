#ifndef THIRD_PERSON_MODULE_H_
#define THIRD_PERSON_MODULE_H_

#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	// �R�l�̓I��Transform3D���ړ�������R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform3D�z
	class ThirdPersonModule
		: public ComponentBase
	{
	public:

		ThirdPersonModule(
			GameObjectPtr target,						// �J�������ǂ�GameObject
			const Vector3&  targetRelativeLookAtPos,	// �J���������������������GameObject����̑��΍��W
			const Vector3&  relativePos					// ��������GameObject����ǂꂾ�����ꂽ�ʒu�ɃJ������u����
		);

	public:

		// <PolymorphismFunc>
		void start();
		void afterCollide();

	public:

		// �J�������ǂ�GameObject���Đݒ�
		void setTarget(GameObjectPtr target);

		// �J���������������������GameObject����̑��΍��W���Đݒ�
		void setTargetRelativeLookAtPos(const Vector3&  targetRelativeLookAtPos);

		// ��������GameObject����ǂꂾ�����ꂽ�ʒu�ɃJ������u�������Đݒ�
		void setRelativePos(const Vector3&  relativePos);

	private:

		// ���g�̂R�������W�R���|�[�l���g
		CfpPtr<Transform3D> m_selfTransform;

		// �J�������ǂ�GameObject
		GameObjectPtr m_target;

		// �J���������������������GameObject����̑��΍��W
		Vector3 m_targetRelativeLookAtPos;

		// ��������GameObject����ǂꂾ�����ꂽ�ʒu�ɃJ������u����
		Vector3 m_relativePos;
	};
}
#endif // !THIRD_PERSON_MODULE_H_