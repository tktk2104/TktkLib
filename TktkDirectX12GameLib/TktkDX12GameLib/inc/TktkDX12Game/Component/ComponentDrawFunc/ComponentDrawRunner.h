#ifndef COMPONENT_DRAW_RUNNER_H_
#define COMPONENT_DRAW_RUNNER_H_

#include <memory>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>

namespace tktk
{
	class ComponentBase;

	class ComponentDrawRunner
	{
	public:

		template <class ComponentType>
		ComponentDrawRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		void runDraw();

		bool isDead() const;

	private:

		struct VTable
		{
			void(*runDraw)(const std::weak_ptr<ComponentBase>&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// udraw()vŠÖ”‚ğ‚Á‚Ä‚¢‚½‚çŒÄ‚Ôˆ—‚ğs‚¤ˆ×‚ÌŠÖ”
			static void runDraw(const std::weak_ptr<ComponentBase>& runPtr);

			static VTable m_vtable;
		};

	private:

		VTable*							m_vtablePtr;
		std::weak_ptr<ComponentBase>	m_componentPtr;
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class ComponentType>
	inline ComponentDrawRunner::ComponentDrawRunner(const std::weak_ptr<ComponentType>& componentPtr)
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
	inline void ComponentDrawRunner::VTableInitializer<ComponentType>::runDraw(const std::weak_ptr<ComponentBase>& runPtr)
	{
		draw_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr.lock()));
	}
}
#endif // !COMPONENT_DRAW_RUNNER_H_