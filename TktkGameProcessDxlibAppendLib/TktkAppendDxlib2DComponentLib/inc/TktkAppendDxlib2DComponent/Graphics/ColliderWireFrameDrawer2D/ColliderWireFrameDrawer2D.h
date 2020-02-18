#ifndef COLLIDER_WIREFRAME_DRAWER_2D_H_
#define COLLIDER_WIREFRAME_DRAWER_2D_H_

#include <memory>
#include <TktkMath/Color.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncClassList.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasSetActiveClass.h>
#include <TktkComponentFramework/Component/ComponentBase.h>

namespace tktk
{
	class ColliderWireFrameDrawer2D
		: public ComponentBase
	{
	public:

		ColliderWireFrameDrawer2D(
			float drawPriority,			// 描画優先度
			const Color& wireFrameColor	// ワイヤーフレームの色
		);

	public:

		void start();
		void update();
		void onEnable();
		void onDisable();

	private:

		float m_drawPriority;
		Color m_wireFrameColor;

		// アクティブ状態を切り替えるためのコンテナのラッパー
		RunFuncClassList<HasSetActiveClass> m_hasSetActiveClassList;
	};
}
#endif // !COLLIDER_WIREFRAME_DRAWER_2D_H_