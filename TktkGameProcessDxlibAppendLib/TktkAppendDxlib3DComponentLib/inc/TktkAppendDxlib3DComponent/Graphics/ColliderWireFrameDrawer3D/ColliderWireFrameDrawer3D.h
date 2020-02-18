#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_H_

#include <memory>
#include <TktkMath/Color.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncClassList.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasSetActiveClass.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/BoxCollider.h>
#include <TktkAppend3DComponent/SphereCollider.h>

namespace tktk
{
	class ColliderWireFrameDrawer3D
		: public ComponentBase
	{
	public:

		ColliderWireFrameDrawer3D(
			float drawPriority,			// 描画優先度
			const Color& wireFrameColor	// ワイヤーフレームの色
		);

	public:

		void start();
		void update();
		void onEnable();
		void onDisable();

	private:

		void createBoxDrawer(std::weak_ptr<BoxCollider> boxCollider);
		void createSphereDrawer(std::weak_ptr<SphereCollider> sphereCollider);

	private:

		float m_drawPriority;
		Color m_wireFrameColor;

		// アクティブ状態を切り替えるためのコンテナのラッパー
		RunFuncClassList<HasSetActiveClass> m_hasSetActiveClassList;
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_H_