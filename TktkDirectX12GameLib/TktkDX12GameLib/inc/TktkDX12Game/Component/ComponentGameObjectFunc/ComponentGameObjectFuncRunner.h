#ifndef COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_
#define COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_

#include <memory>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAfterChangeParentChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionEnterChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionStayChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionExitChecker.h>
#include "../../GameObject/GameObjectPtr.h"
#include "../ComponentBasePtr.h"

namespace tktk
{
	class ComponentGameObjectFuncRunner
	{
	public:

		template <class ComponentType>
		ComponentGameObjectFuncRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		const ComponentBasePtr& getComponentBasePtr() const;

		void runAfterChangeParent(const GameObjectPtr& beforParent);

		void runOnCollisionEnter(const GameObjectPtr& other);

		void runOnCollisionStay(const GameObjectPtr& other);

		void runOnCollisionExit(const GameObjectPtr& other);

		bool isDead() const;

		void destroy();

	private:

		struct VTable
		{
			void(*runAfterChangeParent)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionEnter)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionStay)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionExit)	(const ComponentBasePtr&, const GameObjectPtr&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			static void runAfterChangeParent(const ComponentBasePtr& self, const GameObjectPtr& beforParent);
			static void runOnCollisionEnter	(const ComponentBasePtr& self, const GameObjectPtr& other);
			static void runOnCollisionStay	(const ComponentBasePtr& self, const GameObjectPtr& other);
			static void runOnCollisionExit	(const ComponentBasePtr& self, const GameObjectPtr& other);

			static VTable m_vtable;
		};

	private:

		VTable* m_vtablePtr;
		ComponentBasePtr	m_selfPtr;
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª


	template<class ComponentType>
	inline ComponentGameObjectFuncRunner::ComponentGameObjectFuncRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_selfPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentGameObjectFuncRunner::VTable ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runAfterChangeParent,
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionEnter,
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionStay,
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionExit,
	};

	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runAfterChangeParent(const ComponentBasePtr& self, const GameObjectPtr& beforParent)
	{
		afterChangeParent_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), beforParent);
	}

	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionEnter(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionEnter_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}

	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionStay(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionStay_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}

	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionExit(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionExit_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}
}
#endif // !COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_