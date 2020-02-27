#ifndef POST_EFFECT_DRAWER_MAKER_H_
#define POST_EFFECT_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "PostEffectDrawer.h"

namespace tktk
{
	class PostEffectDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static PostEffectDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<PostEffectDrawer> create();

		// �`��D��x��ݒ肷��
		PostEffectDrawerMaker& drawPriority(float value);

		// �|�X�g�G�t�F�N�g�������鎞�Ɏg�p����p�����[�^�[��ݒ肷��
		PostEffectDrawerMaker& postEffectDrawParameters(const std::vector<PostEffectDrawParameter>& value);

		// �|�X�g�G�t�F�N�g�������鎞�Ɏg�p����p�����[�^�[��ǉ�����
		PostEffectDrawerMaker& addPostEffectDrawParameter(const PostEffectDrawParameter& value);

	private:

		// ���g�̃|�C���^
		static PostEffectDrawerMaker m_self;

	private:
		
		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		float m_drawPriority{ 0 };
		std::vector<PostEffectDrawParameter> m_postEffectDrawParameters;
	};
}
#endif // !POST_EFFECT_DRAWER_MAKER_H_