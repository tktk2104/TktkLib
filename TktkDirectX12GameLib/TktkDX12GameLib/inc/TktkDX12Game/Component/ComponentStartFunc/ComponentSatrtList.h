#ifndef COMPONENT_SATRT_LIST_H_
#define COMPONENT_SATRT_LIST_H_

#include <memory>
#include <forward_list>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include "ComponentStartRunner.h"

namespace tktk
{
	class ComponentSatrtList
	{
	public:

		ComponentSatrtList() = default;

	public:

		// 引数のコンポーネントの型が「start()」関数を持っていたら自身のコンテナに追加する
		template <class ComponentType, std::enable_if_t<has_start_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, std::enable_if_t<!has_start_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

		// 「start()」関数を呼ぶ
		void runStart();

		// 既に「start()」関数が呼ばれたか、死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	private:

		std::forward_list<ComponentStartRunner> m_startList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType, std::enable_if_t<has_start_checker<ComponentType*, void>::value>*>
	inline void ComponentSatrtList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_startList.emplace_front(componentPtr);
	}
	template<class ComponentType, std::enable_if_t<!has_start_checker<ComponentType*, void>::value>*>
	inline void ComponentSatrtList::addComponent(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_SATRT_LIST_H_