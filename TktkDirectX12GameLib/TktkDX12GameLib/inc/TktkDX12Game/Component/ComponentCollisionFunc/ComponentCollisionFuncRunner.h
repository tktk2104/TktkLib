#ifndef COMPONENT_COLLISION_FUNC_RUNNER_H_
#define COMPONENT_COLLISION_FUNC_RUNNER_H_

#include <memory>
#include <forward_list>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasIsCollideChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionEnterChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionStayChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionExitChecker.h>
#include "../../GameObject/GameObjectPtr.h"
#include "../ComponentBasePtr.h"

namespace tktk
{
	class ComponentCollisionFuncRunner
	{
	public:

		template <class ComponentType>
		ComponentCollisionFuncRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		void updateHitObjectList();

		void runCollideFunc(ComponentCollisionFuncRunner& other);

		bool isDead() const;

	private:

		struct VTable
		{
			bool(*runIsCollide)			(const ComponentBasePtr&, const ComponentBasePtr&);
			void(*runOnCollisionEnter)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionStay)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionExit)	(const ComponentBasePtr&, const GameObjectPtr&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			static bool runIsCollide		(const ComponentBasePtr& self, const ComponentBasePtr& other);
			static void runOnCollisionEnter	(const ComponentBasePtr& self, const GameObjectPtr& other);
			static void runOnCollisionStay	(const ComponentBasePtr& self, const GameObjectPtr& other);
			static void runOnCollisionExit	(const ComponentBasePtr& self, const GameObjectPtr& other);

			static VTable m_vtable;
		};

	private:

		struct HitObject
		{
			HitObject(VTable* vtablePtr, ComponentBasePtr selfPtr);

			VTable*				m_vtablePtr;
			ComponentBasePtr	m_selfPtr;
		};

	private:

		VTable*				m_vtablePtr;
		ComponentBasePtr	m_selfPtr;
		std::forward_list<HitObject> m_curHitObjectList;
		std::forward_list<HitObject> m_preHitObjectList;
	};

//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class ComponentType>
	inline ComponentCollisionFuncRunner::ComponentCollisionFuncRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_selfPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentCollisionFuncRunner::VTable ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::runIsCollide,
		&ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::runOnCollisionEnter,
		&ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::runOnCollisionStay,
		&ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::runOnCollisionExit,
	};

	template<class ComponentType>
	inline bool ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::runIsCollide(const ComponentBasePtr& self, const ComponentBasePtr& other)
	{
		return isCollide_runner<bool, const ComponentBasePtr&>::checkAndRun(self.castPtr<ComponentType>(), false, other);
	}

	template<class ComponentType>
	inline void ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::runOnCollisionEnter(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionEnter_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}

	template<class ComponentType>
	inline void ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::runOnCollisionStay(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionStay_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}

	template<class ComponentType>
	inline void ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::runOnCollisionExit(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionExit_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}
}
#endif // !COMPONENT_COLLISION_FUNC_RUNNER_H_