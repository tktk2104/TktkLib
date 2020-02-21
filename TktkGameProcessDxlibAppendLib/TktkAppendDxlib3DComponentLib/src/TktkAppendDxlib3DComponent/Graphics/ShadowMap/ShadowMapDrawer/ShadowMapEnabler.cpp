#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapEnabler.h"

#include <TktkDxlib3DWrapper/Assets/Assets3DManager.h>
#include <DxLib.h>

namespace tktk
{
	ShadowMapEnabler::ShadowMapEnabler(
		float drawPriority,
		CfpPtr<ShadowMapDrawer> shadowMapDrawer
	)
		: ComponentBase(drawPriority)
		, m_shadowMapDrawer(shadowMapDrawer)
	{
	}

	void ShadowMapEnabler::draw() const
	{
		if (m_shadowMapDrawer.isNull() || !m_shadowMapDrawer->isActive()) return;

		// 描画に使用するシャドウマップを設定
		DxLib::SetUseShadowMap(
			0,
			Assets3DManager::getShadowMapAssets()->getShadowMapHandle(m_shadowMapDrawer->getShadowMapId())
		);
	}
}