#ifndef HAS_COLLIDE_CLASS_H_
#define HAS_COLLIDE_CLASS_H_

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasIsActiveChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasIsCollideChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnCollideChecker.h>
#include "../../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	class HasCollideClass
	{
	public:

		template<class T>
		HasCollideClass(ProcessingClassPtr processingClass, T*);
		~HasCollideClass() {}

	public:

		void runFunc(HasCollideClass* other);

		bool isActive();

		ProcessingClassPtr processingClassPtr() const;

	private:

		struct VTable
		{
			bool(*isCollide)(void*, ProcessingClassPtr);
			void(*onCollide)(void*, ProcessingClassPtr);
			bool(*isActive)(void*);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;


			static bool isCollide(void* self, ProcessingClassPtr other);
			static void onCollide(void* self, ProcessingClassPtr other);
			static bool isActive(void* self);

			template <class U>
			static bool checkAndRunIsCollide(U runClass, ProcessingClassPtr other);
			template <class U>
			static void checkAndRunOnCollide(U runClass, ProcessingClassPtr other);
			template <class U>
			static bool checkAndRunIsActive(U runClass);
		};

	private:

		ProcessingClassPtr m_processingClass;

		VTable* m_vtablePtr;
	};

	template<class T>
	inline HasCollideClass::HasCollideClass(ProcessingClassPtr processingClass, T*)
		: m_processingClass(processingClass)
		, m_vtablePtr(&VTableInitializer<T>::m_vtable)
	{
	}

	template <class T>
	HasCollideClass::VTable HasCollideClass::VTableInitializer<T>::m_vtable =
	{
		&HasCollideClass::VTableInitializer<T>::isCollide,
		&HasCollideClass::VTableInitializer<T>::onCollide,
		&HasCollideClass::VTableInitializer<T>::isActive
	};

	template<class T>
	inline bool HasCollideClass::VTableInitializer<T>::isCollide(void* self, ProcessingClassPtr other)
	{
		return checkAndRunIsCollide(reinterpret_cast<T*>(self), other);
	}

	template<class T>
	inline void HasCollideClass::VTableInitializer<T>::onCollide(void* self, ProcessingClassPtr other)
	{
		checkAndRunOnCollide(reinterpret_cast<T*>(self), other);
	}

	template<class T>
	inline bool HasCollideClass::VTableInitializer<T>::isActive(void * self)
	{
		return checkAndRunIsActive(reinterpret_cast<T*>(self));
	}

	template<class T>
	template<class U>
	inline bool HasCollideClass::VTableInitializer<T>::checkAndRunIsCollide(U runClass, ProcessingClassPtr other)
	{
		return isCollide_runner<bool, ProcessingClassPtr>::checkAndRun(runClass, false, other);
	}

	template<class T>
	template<class U>
	inline void HasCollideClass::VTableInitializer<T>::checkAndRunOnCollide(U runClass, ProcessingClassPtr other)
	{
		onCollide_runner<void, ProcessingClassPtr>::checkAndRun(runClass, other);
	}

	template<class T>
	template<class U>
	inline bool HasCollideClass::VTableInitializer<T>::checkAndRunIsActive(U runClass)
	{
		return isActive_runner<bool>::checkAndRun(runClass, true);
	}
}
#endif // !HAS_COLLIDE_CLASS_H_