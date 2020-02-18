#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapCreateStarter.h"

#include <TktkDxlib3DWrapper/Assets/Assets3DManager.h>
#include <DxLib.h>

namespace tktk
{
	ShadowMapCreateStarter::ShadowMapCreateStarter(
		float drawPriority,
		std::weak_ptr<ShadowMapDrawer> shadowMapDrawer
	)
		: ComponentBase(drawPriority)
		, m_shadowMapDrawer(shadowMapDrawer)
	{
	}

	void ShadowMapCreateStarter::draw() const
	{
		if (m_shadowMapDrawer.expired() || !m_shadowMapDrawer.lock()->isActive()) return;

		// シャドウマップへの描画を開始
		DxLib::ShadowMap_DrawSetup(
			Assets3DManager::getShadowMapAssets().lock()->getShadowMapHandle(m_shadowMapDrawer.lock()->getShadowMapId())
		);
	}
}