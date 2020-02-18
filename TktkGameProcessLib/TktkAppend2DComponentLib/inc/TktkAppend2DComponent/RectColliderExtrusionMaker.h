#ifndef RECT_COLLIDER_EXTRUSION_MAKER_H_
#define RECT_COLLIDER_EXTRUSION_MAKER_H_

#include "RectColliderExtrusion.h"

namespace tktk
{
	class RectColliderExtrusionMaker
	{
	public:

		// インスタンス作成開始
		static RectColliderExtrusionMaker& makeStart();

	public:

		// 作成する
		RectColliderExtrusion* create();

	private:

		// 自身のポインタ
		static RectColliderExtrusionMaker m_self;
	};
}
#endif // !RECT_COLLIDER_EXTRUSION_MAKER_H_