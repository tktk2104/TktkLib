#ifndef COMPONENT_DRAW_RUNNER_H_
#define COMPONENT_DRAW_RUNNER_H_

#include <memory>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>
#include "ComponentBase.h"

namespace tktk
{
	class ComponentDrawRunner
	{
	public:

		template <class ComponentType>
		ComponentDrawRunner(const std::shared_ptr<ComponentType>& componentPtr);

	public:

		void runDraw();

		bool isDead() const;

	private:

		struct VTable
		{
			void(*runDraw)(const std::shared_ptr<ComponentBase>&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// udraw()vŠÖ”‚ğ‚Á‚Ä‚¢‚½‚çŒÄ‚Ôˆ—‚ğs‚¤ˆ×‚ÌŠÖ”
			static void runDraw(const std::shared_ptr<ComponentBase>& runPtr);

			static VTable m_vtable;
		};

	private:

		VTable*							m_vtablePtr;
		std::shared_ptr<ComponentBase>	m_componentPtr;
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class ComponentType>
	inline ComponentDrawRunner::ComponentDrawRunner(const std::shared_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_componentPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentDrawRunner::VTable ComponentDrawRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentDrawRunner::VTableInitializer<ComponentType>::runDraw,
	};

	template<class ComponentType>
	inline void ComponentDrawRunner::VTableInitializer<ComponentType>::runDraw(const std::shared_ptr<ComponentBase>& runPtr)
	{
		draw_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr));
	}
}
#endif // !COMPONENT_DRAW_RUNNER_H_