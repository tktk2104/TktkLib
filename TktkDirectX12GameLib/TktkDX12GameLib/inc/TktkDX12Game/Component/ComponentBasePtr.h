#ifndef COMPONENT_BASE_PTR_H_
#define COMPONENT_BASE_PTR_H_

#include <memory>
#include "../SafetyVoidPtr/ClassTypeChecker.h"
#include "ComponentPtr.h"

namespace tktk
{
	class ComponentBase;

	class ComponentBasePtr
	{
	public:

		ComponentBasePtr() = default;

		template <class ComponentType>
		ComponentBasePtr(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		std::shared_ptr<ComponentBase> operator ->() const;

		bool isSame(const ComponentBasePtr& other) const;

		template <class ComponentType>
		bool canCast() const;

		template <class ComponentType>
		ComponentPtr<ComponentType> castPtr() const;

		bool isDead() const;

	private:

		unsigned int					m_componentTypeId{ 0U };
		std::weak_ptr<ComponentBase>	m_componentPtr{ };
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class ComponentType>
	inline ComponentBasePtr::ComponentBasePtr(const std::weak_ptr<ComponentType>& componentPtr)
		: m_componentTypeId(ClassTypeChecker::getClassId<ComponentType>())
		, m_componentPtr(componentPtr)
	{
	}

	template<class ComponentType>
	inline bool ComponentBasePtr::canCast() const
	{
		return (ClassTypeChecker::getClassId<ComponentType>() == m_componentTypeId);
	}

	template<class ComponentType>
	inline ComponentPtr<ComponentType> ComponentBasePtr::castPtr() const
	{
		if (canCast<ComponentType>())
		{
			return ComponentPtr<ComponentType>(std::dynamic_pointer_cast<ComponentType>(m_componentPtr.lock()));
		}
		return ComponentPtr<ComponentType>();
	}
}
#endif // !COMPONENT_BASE_PTR_H_