#ifndef RECT_COLLIDER_EXTRUSION_MAKER_H_
#define RECT_COLLIDER_EXTRUSION_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "RectColliderExtrusion.h"

namespace tktk
{
	class RectColliderExtrusionMaker
	{
	public:

		// インスタンス作成開始
		static RectColliderExtrusionMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<RectColliderExtrusion> create();

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static RectColliderExtrusionMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
	};
}
#endif // !RECT_COLLIDER_EXTRUSION_MAKER_H_