#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapCreateStarter.h"

#include <TktkDxlib3DWrapper/Assets/Assets3DManager.h>
#include <DxLib.h>

namespace tktk
{
	ShadowMapCreateStarter::ShadowMapCreateStarter(
		float drawPriority,
		CfpPtr<ShadowMapDrawer> shadowMapDrawer
	)
		: ComponentBase(drawPriority)
		, m_shadowMapDrawer(shadowMapDrawer)
	{
	}

	void ShadowMapCreateStarter::draw() const
	{
		if (m_shadowMapDrawer.isNull() || !m_shadowMapDrawer->isActive()) return;

		// �V���h�E�}�b�v�ւ̕`����J�n
		DxLib::ShadowMap_DrawSetup(
			Assets3DManager::getShadowMapAssets()->getShadowMapHandle(m_shadowMapDrawer->getShadowMapId())
		);
	}
}