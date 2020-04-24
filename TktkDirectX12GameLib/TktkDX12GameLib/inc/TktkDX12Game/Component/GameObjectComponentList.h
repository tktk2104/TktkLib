#ifndef GAME_OBJECT_COMPONENT_LIST_H_
#define GAME_OBJECT_COMPONENT_LIST_H_

#include <forward_list>
#include "ComponentBasePtr.h"

namespace tktk
{
	class ComponentBase;

	class GameObjectComponentList
	{
	public:

		GameObjectComponentList() = default;

	public:

		template <class ComponentType>
		void add(const std::weak_ptr<ComponentType>& componentPtr);

		template <class ComponentType>
		ComponentPtr<ComponentType> find() const;

		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> findAll() const;

		void removeDeadComponent();

	private:

		std::forward_list<ComponentBasePtr> m_componentList;
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class ComponentType>
	inline void GameObjectComponentList::add(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_componentList.push_front(componentPtr);
	}

	template<class ComponentType>
	inline ComponentPtr<ComponentType> GameObjectComponentList::find() const
	{
		for (const auto& node : m_componentList)
		{
			if (node.canCast<ComponentType>())
			{
				return node.castPtr<ComponentType>();
			}
		}
		return nullptr;
	}

	template<class ComponentType>
	inline std::forward_list<ComponentPtr<ComponentType>> GameObjectComponentList::findAll() const
	{
		std::forward_list<ComponentBasePtr> result;

		for (const auto& node : m_componentList)
		{
			if (node.canCast<ComponentType>())
			{
				result.push_front(node.castPtr<ComponentType>());
			}
		}
		return result;
	}
}
#endif // !GAME_OBJECT_COMPONENT_LIST_H_
