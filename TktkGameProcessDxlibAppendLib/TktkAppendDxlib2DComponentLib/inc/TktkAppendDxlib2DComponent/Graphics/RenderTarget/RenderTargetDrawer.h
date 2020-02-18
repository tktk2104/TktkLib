#ifndef RENDER_TARGET_DRAWER_H_
#define RENDER_TARGET_DRAWER_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	class RenderTargetDrawer
		: public ComponentBase
	{
	public:

		RenderTargetDrawer(
			int drawRenderTargetId,			// 描画するレンダーターゲットのId
			float drawPriority,				// 描画優先度
			BlendMode blendMode,			// 描画のブレンド方法の種類
			float blendParam				// 描画のブレンドに使用する値
		);

	public:

		void draw() const;

	private:

		// 描画するレンダーターゲットのId
		int m_drawRenderTargetId;

		// 描画のブレンド方法の種類
		BlendMode m_blendMode;

		// 描画のブレンドに使用する値
		float m_blendParam;
	};
}
#endif // !RENDER_TARGET_DRAWER_H_