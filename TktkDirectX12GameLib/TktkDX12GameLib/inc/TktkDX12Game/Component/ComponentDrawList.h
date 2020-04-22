#ifndef COMPONENT_DRAW_LIST_H_
#define COMPONENT_DRAW_LIST_H_

#include <memory>
#include <map>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>
#include "ComponentDrawRunner.h"

namespace tktk
{
	class ComponentDrawList
	{
	public:

		ComponentDrawList() = default;

	public:

		// 引数のコンポーネントの型が「draw()」関数を持っていたら自身のコンテナに追加する
		// ※描画優先度はデフォルト（0.0f）で値が小さい程、早く実行される
		template <class ComponentType, std::enable_if_t<has_draw_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::shared_ptr<ComponentType>& componentPtr);
		template <class ComponentType, std::enable_if_t<!has_draw_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::shared_ptr<ComponentType>& componentPtr);

		// 描画優先度順で「draw()」関数を呼ぶ
		void runDraw();

		// 死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	private:

		std::multimap<float, ComponentDrawRunner> m_drawList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 引数のコンポーネントの型が「draw()」関数を持っていたら自身のコンテナに追加する
	template<class ComponentType, std::enable_if_t<has_draw_checker<ComponentType*, void>::value>*>
	inline void ComponentDrawList::addComponent(const std::shared_ptr<ComponentType>& componentPtr)
	{
		m_drawList.emplace(componentPtr->getDrawPriority(), componentPtr);
	}
	template<class ComponentType, std::enable_if_t<!has_draw_checker<ComponentType*, void>::value>*>
	inline void ComponentDrawList::addComponent(const std::shared_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_DRAW_LIST_H_