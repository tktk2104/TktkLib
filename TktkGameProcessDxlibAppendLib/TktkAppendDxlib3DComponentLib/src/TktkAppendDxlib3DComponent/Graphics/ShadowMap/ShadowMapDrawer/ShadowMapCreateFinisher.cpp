#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapCreateFinisher.h"

#include <DxLib.h>

namespace tktk
{
	ShadowMapCreateFinisher::ShadowMapCreateFinisher(
		float drawPriority,
		CfpPtr<ShadowMapDrawer> shadowMapDrawer
	)
		: ComponentBase(drawPriority)
		, m_shadowMapDrawer(shadowMapDrawer)
	{
	}

	void ShadowMapCreateFinisher::draw() const
	{
		if (m_shadowMapDrawer.isNull() || !m_shadowMapDrawer->isActive()) return;

		// �V���h�E�}�b�v�ւ̕`����I��
		DxLib::ShadowMap_DrawEnd();
	}
}