#ifndef COMPONENT_START_RUNNER_H_
#define COMPONENT_START_RUNNER_H_

#include <memory>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>

namespace tktk
{
	class ComponentBase;

	class ComponentStartRunner
	{
	public:

		template <class ComponentType>
		ComponentStartRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		void runStart();

		bool isDead() const;

	private:

		struct VTable
		{
			void(*runStart)(const std::weak_ptr<ComponentBase>&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// ustart()vŠÖ”‚ğ‚Á‚Ä‚¢‚½‚çŒÄ‚Ôˆ—‚ğs‚¤ˆ×‚ÌŠÖ”
			static void runStart(const std::weak_ptr<ComponentBase>& runPtr);

			static VTable m_vtable;
		};

	private:

		bool							m_afterRun{ false };
		VTable*							m_vtablePtr;
		std::weak_ptr<ComponentBase>	m_componentPtr;
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class ComponentType>
	inline ComponentStartRunner::ComponentStartRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_componentPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentStartRunner::VTable ComponentStartRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentStartRunner::VTableInitializer<ComponentType>::runStart,
	};

	template<class ComponentType>
	inline void ComponentStartRunner::VTableInitializer<ComponentType>::runStart(const std::weak_ptr<ComponentBase>& runPtr)
	{
		start_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr.lock()));
	}
}
#endif // !COMPONENT_START_RUNNER_H_