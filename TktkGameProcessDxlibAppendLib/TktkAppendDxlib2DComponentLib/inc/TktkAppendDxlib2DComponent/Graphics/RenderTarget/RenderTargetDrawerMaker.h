#ifndef RENDER_TARGET_DRAWER_MAKER_H_
#define RENDER_TARGET_DRAWER_MAKER_H_

#include <memory>
#include "RenderTargetDrawer.h"

namespace tktk
{
	class RenderTargetDrawerMaker
	{
	public:

		// インスタンス作成開始
		static RenderTargetDrawerMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<RenderTargetDrawer> create();

		// 描画優先度を設定する
		RenderTargetDrawerMaker& drawPriority(float value);

		// 描画するレンダーターゲットのIdを設定する
		RenderTargetDrawerMaker&  drawRenderTargetId(int value);

		// 描画のブレンド方法の種類を設定する
		RenderTargetDrawerMaker&  blendMode(BlendMode value);

		// 描画のブレンドに使用する値を設定する
		RenderTargetDrawerMaker&  blendParam(float value);

	private:

		// 自身のポインタ
		static RenderTargetDrawerMaker m_self;

	private:

		float m_drawPriority{ 0 };
		int m_drawRenderTargetId{ -1 };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
	};
}
#endif // !RENDER_TARGET_DRAWER_MAKER_H_