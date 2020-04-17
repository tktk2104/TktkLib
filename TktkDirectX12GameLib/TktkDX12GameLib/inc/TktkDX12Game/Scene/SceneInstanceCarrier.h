#ifndef SCENE_INSTANCE_CARRIER_H_
#define SCENE_INSTANCE_CARRIER_H_

#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasEndChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>
#include "../SafetyVoidPtr/SafetyVoidPtr.h"

namespace tktk
{
	class SceneInstanceCarrier
	{
	public:

		SceneInstanceCarrier() = default;

	public:

		template<class SceneType, class... Args>
		void initialize(Args... constructorArgs);

		void finalize();

		void enableScene();

		void disableScene();

		void update();

	private:

		struct VTable
		{
			void (*start)(const SafetyVoidPtr&);
			void (*update)(const SafetyVoidPtr&);
			void (*end)(const SafetyVoidPtr&);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;

			static void start(const SafetyVoidPtr& self);
			static void update(const SafetyVoidPtr& self);
			static void end(const SafetyVoidPtr& self);

			template <class U>
			static void checkAndRunStart(U runClass);
			template <class U>
			static void checkAndRunUpdate(U runClass);
			template <class U>
			static void checkAndRunEnd(U runClass);
		};

	private:

		bool			m_isActive{ false };
		bool			m_nextFrameIsActive{ false };
		SafetyVoidPtr	m_scenePtr{};
		VTable*			m_vtablePtr{ nullptr };
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template <class T>
	SceneInstanceCarrier::VTable SceneInstanceCarrier::VTableInitializer<T>::m_vtable =
	{
		&SceneInstanceCarrier::VTableInitializer<T>::start,
		&SceneInstanceCarrier::VTableInitializer<T>::update,
		&SceneInstanceCarrier::VTableInitializer<T>::end
	};

	template<class SceneType, class ...Args>
	inline void SceneInstanceCarrier::initialize(Args ...constructorArgs)
	{
		m_isActive			= false;
		m_nextFrameIsActive = false;
		m_scenePtr			= { new SceneType(constructorArgs...) };
		m_vtablePtr			= &VTableInitializer<SceneType>::m_vtable;
	}

	template<class T>
	inline void SceneInstanceCarrier::VTableInitializer<T>::start(const SafetyVoidPtr& self)
	{
		checkAndRunStart(self.castPtr<T>());
	}

	template<class T>
	inline void SceneInstanceCarrier::VTableInitializer<T>::update(const SafetyVoidPtr& self)
	{
		checkAndRunUpdate(self.castPtr<T>());
	}

	template<class T>
	inline void SceneInstanceCarrier::VTableInitializer<T>::end(const SafetyVoidPtr& self)
	{
		checkAndRunEnd(self.castPtr<T>());
	}

	template<class T>
	template<class U>
	inline void SceneInstanceCarrier::VTableInitializer<T>::checkAndRunStart(U runClass)
	{
		start_runner<void>::checkAndRun(runClass);
	}

	template<class T>
	template<class U>
	inline void SceneInstanceCarrier::VTableInitializer<T>::checkAndRunUpdate(U runClass)
	{
		update_runner<void>::checkAndRun(runClass);
	}

	template<class T>
	template<class U>
	inline void SceneInstanceCarrier::VTableInitializer<T>::checkAndRunEnd(U runClass)
	{
		end_runner<void>::checkAndRun(runClass);
	}
	
}
#endif // !SCENE_INSTANCE_CARRIER_H_