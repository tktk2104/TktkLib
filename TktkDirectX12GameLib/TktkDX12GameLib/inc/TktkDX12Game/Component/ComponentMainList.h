#ifndef COMPONENT_MAIN_LIST_H_
#define COMPONENT_MAIN_LIST_H_

#include <memory>
#include <forward_list>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>
#include "ComponentBase.h"

namespace tktk
{
	class ComponentMainList
	{
	public:

		template<class T>
		ComponentMainList(T* rawPtr);

	public:

		template <class ComponentType, class... Args>
		void createComponent(Args... args);

		void runUpdate();

	private:

		struct VTable
		{
			void(*runUpdate)(const std::forward_list<std::shared_ptr<ComponentBase>>&);
		};

		template <class T>
		struct VTableInitializer
		{
			static void runUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
			{
				checkAndRunUpdate<T>(mainList);
			}

			template <class U, std::enable_if_t<has_update_checker<U, void>::value>* = nullptr>
			static void checkAndRunUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
			{
				for (const auto& node : mainList)
				{
					std::dynamic_pointer_cast<std::remove_pointer_t<U>>(node)->update();
				}
			}
			template <class U, std::enable_if_t<!has_update_checker<U, void>::value>* = nullptr>
			static void checkAndRunUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList) {}

			static VTable m_vtable;
		};

	private:

		VTable*												m_vtablePtr;
		std::forward_list<std::shared_ptr<ComponentBase>>	m_mainList;
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class T>
	typename ComponentMainList::VTable ComponentMainList::VTableInitializer<T>::m_vtable =
	{
		&ComponentMainList::VTableInitializer<T>::runUpdate
	};

	template<class T>
	inline ComponentMainList::ComponentMainList(T* rawPtr)
		: m_vtablePtr(&VTableInitializer<T*>::m_vtable)
	{
	}

	template<class ComponentType, class ...Args>
	inline void ComponentMainList::createComponent(Args ...args)
	{
		m_mainList.push_front(std::make_shared<ComponentType>(args...));
	}
}
#endif // !COMPONENT_MAIN_LIST_H_