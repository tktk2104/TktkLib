#ifndef COMPONENT_PTR_H_
#define COMPONENT_PTR_H_

#include <memory>

namespace tktk
{
	template <class ComponentType>
	class ComponentPtr
	{
	public:

		ComponentPtr() = default;

		explicit ComponentPtr(const std::weak_ptr<ComponentType>& weakPtr);

	public:

		bool expired() const;

		std::shared_ptr<ComponentType> operator ->() const;

	private:

		std::weak_ptr<ComponentType> m_componentPtr;
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class ComponentType>
	inline bool ComponentPtr<ComponentType>::expired() const
	{
		return m_componentPtr.expired();
	}

	template<class ComponentType>
	inline std::shared_ptr<ComponentType> ComponentPtr<ComponentType>::operator->() const
	{
		if (m_componentPtr.expired()) return nullptr;
		return m_componentPtr.lock();
	}

	template<class ComponentType>
	inline ComponentPtr<ComponentType>::ComponentPtr(const std::weak_ptr<ComponentType>& weakPtr)
		: m_componentPtr(weakPtr)
	{
	}
}
#endif // !COMPONENT_PTR_H_