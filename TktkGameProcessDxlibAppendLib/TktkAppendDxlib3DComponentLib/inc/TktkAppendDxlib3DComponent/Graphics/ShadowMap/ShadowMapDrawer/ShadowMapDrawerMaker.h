#ifndef SHADOW_MAP_DRAWER_MAKER_H_
#define SHADOW_MAP_DRAWER_MAKER_H_

#include "ShadowMapDrawer.h"

namespace tktk
{
	class ShadowMapDrawerMaker
	{
	public:

		// インスタンス作成開始
		static ShadowMapDrawerMaker& makeStart();

	public:

		// 作成する
		ShadowMapDrawer* create();

		// シャドウマップの生成を開始する描画優先度
		ShadowMapDrawerMaker& shadowMapCreateStarterDrawPriority(float value);

		// シャドウマップの生成を終了する描画優先度
		ShadowMapDrawerMaker& shadowMapCreateFinisherDrawPriority(float value);

		// シャドウマップの適応を開始する描画優先度
		ShadowMapDrawerMaker& shadowMapEnablerDrawPriority(float value);

		// シャドウマップの適応を終了する描画優先度
		ShadowMapDrawerMaker& shadowMapDisablerDrawPriority(float value);

		// 使用するシャドウマップのId
		ShadowMapDrawerMaker& shadowMapId(int value);

		// シャドウマッピングをする範囲の最小座標
		ShadowMapDrawerMaker& drawAreaMinPos(const Vector3& value);

		// シャドウマッピングをする範囲の最大座標
		ShadowMapDrawerMaker& drawAreaMaxPos(const Vector3& value);

	private:

		// 自身のポインタ
		static ShadowMapDrawerMaker m_self;

	private:

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