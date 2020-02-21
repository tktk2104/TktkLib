#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_H_

#include <TktkMath/Color.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncSimpleContainer.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasOneArgFuncClass.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetActiveChecker.h>
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

		void createBoxDrawer(CfpPtr<BoxCollider> boxCollider);
		void createSphereDrawer(CfpPtr<SphereCollider> sphereCollider);

	private:

		float m_drawPriority;
		Color m_wireFrameColor;

		// アクティブ状態を切り替えるためのコンテナのラッパー
		RunFuncSimpleContainer<HasOneArgFuncClass<has_setActive_checker<bool>, setActive_runner<bool>, bool>> m_hasSetActiveClassList;
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_H_