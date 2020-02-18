#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapDisabler.h"

#include <DxLib.h>

namespace tktk
{
	ShadowMapDisabler::ShadowMapDisabler(
		float drawPriority,
		std::weak_ptr<ShadowMapDrawer> shadowMapDrawer
	)
		: ComponentBase(drawPriority)
		, m_shadowMapDrawer(shadowMapDrawer)
	{
	}

	void ShadowMapDisabler::draw() const
	{
		if (m_shadowMapDrawer.expired() || !m_shadowMapDrawer.lock()->isActive()) return;

		// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
		SetUseShadowMap(0, -1);
	}
}