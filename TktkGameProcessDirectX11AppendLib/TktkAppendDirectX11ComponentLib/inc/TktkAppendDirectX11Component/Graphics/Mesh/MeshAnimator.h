#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "MeshDrawer.h"

namespace tktk
{
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(
			CfpPtr<MeshDrawer> meshDrawer,
			int animationId,
			float animFrameIntervalPerSec,
			float animSpeedRate
		);
		~MeshAnimator();

	public:

		void start();
		void update();

	public:

		int getAnimationId() const;

		// �g�p����A�j���[�V������ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setAnimationId(IdType id)
		{
			setAnimationIdImpl(static_cast<int>(id));
		}
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setAnimationId(IdType id) { static_assert(false, "AnimationId Fraud Type"); }

		// �A�j���[�V�����̍Đ����x�������擾����
		float getAnimSpeedRate() const;

		// �A�j���[�V�����̍Đ����x������ݒ肷��
		void setAnimSpeedRate(float rate);

	private:

		// �e��id�w��n�̊֐��̎���
		void setAnimationIdImpl(int id);

	private:

		CfpPtr<MeshDrawer> m_meshDrawer;

		int m_animationId{ 0 };

		float m_animSecTimer{ 0.0f };

		float m_animFrameIntervalPerSec{ 60.0f };

		float m_animSpeedRate{ 1.0f };
	};
}
#endif // !MESH_ANIMATOR_H_