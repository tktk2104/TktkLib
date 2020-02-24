#ifndef COLLIDER_WIREFRAME_DRAWER_2D_H_
#define COLLIDER_WIREFRAME_DRAWER_2D_H_

#include <memory>
#include <TktkMath/Color.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncSimpleContainer.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasAlwaysRunFuncClass.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetActiveChecker.h>
#include <TktkComponentFramework/Component/ComponentBase.h>

namespace tktk
{
	// スーパー★別名ーズ
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker>
	using SimpleCont = RunFuncSimpleContainer<NodeType, HasFuncChecker>;

	template <class JudgePtrType>
	using HasSetActiveChecker = has_setActive_checker<JudgePtrType, void, bool>;

	// サブ★別名ーズ
	using SetActiveCont = SimpleCont<HasAlwaysRunFuncClass<setActive_runner, void, bool>, HasSetActiveChecker>;

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
		SetActiveCont m_hasSetActiveClassList;
	};
}
#endif // !COLLIDER_WIREFRAME_DRAWER_2D_H_