#ifndef SHADOW_MAP_DRAWER_MAKER_H_
#define SHADOW_MAP_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "ShadowMapDrawer.h"

namespace tktk
{
	class ShadowMapDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static ShadowMapDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<ShadowMapDrawer> create();

		// �V���h�E�}�b�v�̐������J�n����`��D��x
		ShadowMapDrawerMaker& shadowMapCreateStarterDrawPriority(float value);

		// �V���h�E�}�b�v�̐������I������`��D��x
		ShadowMapDrawerMaker& shadowMapCreateFinisherDrawPriority(float value);

		// �V���h�E�}�b�v�̓K�����J�n����`��D��x
		ShadowMapDrawerMaker& shadowMapEnablerDrawPriority(float value);

		// �V���h�E�}�b�v�̓K�����I������`��D��x
		ShadowMapDrawerMaker& shadowMapDisablerDrawPriority(float value);

		// �g�p����V���h�E�}�b�v��Id
		ShadowMapDrawerMaker& shadowMapId(int value);

		// �V���h�E�}�b�s���O������͈͂̍ŏ����W
		ShadowMapDrawerMaker& drawAreaMinPos(const Vector3& value);

		// �V���h�E�}�b�s���O������͈͂̍ő���W
		ShadowMapDrawerMaker& drawAreaMaxPos(const Vector3& value);

	private:

		// ���g�̃|�C���^
		static ShadowMapDrawerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		float m_shadowMapCreateStarterDrawPriority{ 0.0f };
		float m_shadowMapCreateFinisherDrawPriority{ 0.0f };
		float m_shadowMapEnablerDrawPriority{ 0.0f };
		float m_shadowMapDisablerDrawPriority{ 0.0f };
		int m_shadowMapId{ -1 };
		Vector3 m_drawAreaMinPos{ Vector3::zero };
		Vector3 m_drawAreaMaxPos{ Vector3::one };
	};
}
#endif // !SHADOW_MAP_DRAWER_MAKER_H_