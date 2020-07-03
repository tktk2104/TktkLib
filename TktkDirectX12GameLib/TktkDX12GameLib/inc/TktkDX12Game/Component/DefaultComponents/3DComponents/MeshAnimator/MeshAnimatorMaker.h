#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "MeshAnimator.h"

namespace tktk
{
	// �uMeshAnimator�v�����w���p�[�N���X
	class MeshAnimatorMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		MeshAnimatorMaker() = default;
		MeshAnimatorMaker(const MeshAnimatorMaker& other) = default;
		MeshAnimatorMaker& operator = (const MeshAnimatorMaker& other) = default;

	public:

		// �쐬�J�n
		static MeshAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<MeshAnimator> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉�����[�V����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshAnimatorMaker& initMotionId(IdType value);

	private: /* �e��id�w��n�̊֐��̎��� */

		MeshAnimatorMaker& initMotionIdImpl(unsigned int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static MeshAnimatorMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user{  };
		unsigned int	m_initMotionId{ 0U };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshAnimatorMaker& initMotionId(IdType value) { static_assert(false, "MotionId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p���鏉�����[�V����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline MeshAnimatorMaker& MeshAnimatorMaker::initMotionId(IdType value)
	{
		return initMotionIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !MESH_ANIMATOR_MAKER_H_
