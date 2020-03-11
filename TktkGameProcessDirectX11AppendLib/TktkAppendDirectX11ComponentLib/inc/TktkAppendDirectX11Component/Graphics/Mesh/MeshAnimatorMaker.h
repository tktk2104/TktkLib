#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "MeshAnimator.h"

namespace tktk
{
	class MeshAnimatorMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static MeshAnimatorMaker& makeStart(GameObjectPtr user);

	private:

		// ���g�̃|�C���^
		static MeshAnimatorMaker m_self;

	private:

		// �v���C�x�[�g�R���X�g���N�^�B
		MeshAnimatorMaker() = default;
		MeshAnimatorMaker(const MeshAnimatorMaker& other) = default;
		MeshAnimatorMaker& operator = (const MeshAnimatorMaker& other) = default;

	public:

		// �쐬����
		CfpPtr<MeshAnimator> create();

		// �A�j���[�V������K�p���郁�b�V���`��R���|�[�l���g��ݒ肷��
		MeshAnimatorMaker& meshDrawer(CfpPtr<MeshDrawer> value);

		// �g�p����A�j���[�V������ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshAnimatorMaker& animationId(IdType value)
		{
			return animationIdImpl(static_cast<int>(value));
		}
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshAnimatorMaker& animationId(IdType value) { static_assert(false, "AnimationId Fraud Type"); }

		// �P�b�Ԃɉ��t���[���A�j���[�V�������Đ����邩��ݒ肷��
		MeshAnimatorMaker& animFrameIntervalPerSec(float value);

		// �A�j���[�V�����̍Đ����x������ݒ肷��
		MeshAnimatorMaker& animSpeedRate(float value);

	private:

		// �e��id�w��n�̊֐��̎���
		MeshAnimatorMaker& animationIdImpl(int value);

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		CfpPtr<MeshDrawer> m_meshDrawer{};
		int m_animationId{ 0 };
		float m_animFrameIntervalPerSec{ 60.0f };
		float m_animSpeedRate{ 1.0f };
	};
}

#endif // !MESH_ANIMATOR_MAKER_H_