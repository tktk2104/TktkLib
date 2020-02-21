#ifndef THIRD_PERSON_MODULE_MAKER_H_
#define THIRD_PERSON_MODULE_MAKER_H_

#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "ThirdPersonModule.h"

namespace tktk
{
	// ThirdPersonModule�̃C���X�^���X���쐬����\����
	struct ThirdPersonModuleMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static ThirdPersonModuleMaker& makeStart();

	public:

		// �쐬����
		ThirdPersonModule* create();

		// �J�������ǂ�GameObject��ݒ肷��
		ThirdPersonModuleMaker& target(GameObjectPtr value);

		// �J���������������������GameObject����̑��΍��W��ݒ肷��
		ThirdPersonModuleMaker& targetRelativeLookAtPos(const Vector3& value);

		// ��������GameObject����ǂꂾ�����ꂽ�ʒu�ɃJ������u������ݒ肷��
		ThirdPersonModuleMaker& relativePos(const Vector3& value);

	private:

		// ���g�̃|�C���^
		static ThirdPersonModuleMaker m_self;

	private:

		GameObjectPtr m_target;
		Vector3 m_targetRelativeLookAtPos{ Vector3::zero };
		Vector3 m_relativePos{ Vector3(0.0f, 0.0f, -100.0f) };
	};
}
#endif // !THIRD_PERSON_MODULE_MAKER_H_