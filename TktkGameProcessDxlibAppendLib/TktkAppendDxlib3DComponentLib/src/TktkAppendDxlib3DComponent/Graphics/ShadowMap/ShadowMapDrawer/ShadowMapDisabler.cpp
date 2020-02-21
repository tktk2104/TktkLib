#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapDisabler.h"

#include <DxLib.h>

namespace tktk
{
	ShadowMapDisabler::ShadowMapDisabler(
		float drawPriority,
		CfpPtr<ShadowMapDrawer> shadowMapDrawer
	)
		: ComponentBase(drawPriority)
		, m_shadowMapDrawer(shadowMapDrawer)
	{
	}

	void ShadowMapDisabler::draw() const
	{
		if (m_shadowMapDrawer.isNull() || !m_shadowMapDrawer->isActive()) return;

		// 描画に使用するシャドウマップの設定を解除
		SetUseShadowMap(0, -1);
	}
}