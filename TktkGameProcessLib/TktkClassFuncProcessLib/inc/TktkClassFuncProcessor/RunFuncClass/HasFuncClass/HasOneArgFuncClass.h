#ifndef HAS_ONE_ARG_FUNC_CLASS_H_
#define HAS_ONE_ARG_FUNC_CLASS_H_

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasIsActiveChecker.h>
#include "../../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	template<class HasFuncChecker, class FuncRunner, class FirstArgType>
	class HasOneArgFuncClass
	{
	public:

		template<class T>
		HasOneArgFuncClass(ProcessingClassPtr processingClassPtr, T*);
		~HasOneArgFuncClass() {};

	public:

		bool hasFuncCheck() const;

		void runFunc(FirstArgType arg1);

		ProcessingClassPtr processingClassPtr() const;

	private:


		struct VTable
		{
			bool(*hasFunc)(void*);
			void(*runFunc)(void*, FirstArgType);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;

			static bool hasFunc(void* self);
			static void runFunc(void* self, FirstArgType arg1);

			template<class U>
			static bool checkHasFunc(U runClass);
			template<class U>
			static void checkAndRunFunc(U runClass, FirstArgType arg1);
		};

	private:

		ProcessingClassPtr m_processingClassPtr;

		VTable* m_vtablePtr;
	};

	template<class HasFuncChecker, class FuncRunner, class FirstArgType>
	template<class T>
	inline HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::HasOneArgFuncClass(ProcessingClassPtr processingClassPtr, T *)
		: m_processingClassPtr(processingClassPtr)
		, m_vtablePtr(&VTableInitializer<T>::m_vtable)
	{
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType>
	inline bool HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::hasFuncCheck() const
	{
		if (m_processingClassPtr.isNull()) return false;
		return m_vtablePtr->hasFunc(m_processingClassPtr->voidPtr());
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType>
	inline void HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::runFunc(FirstArgType arg1)
	{
		if (m_processingClassPtr.isNull()) return;
		m_vtablePtr->runFunc(m_processingClassPtr->voidPtr(), arg1);
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType>
	inline ProcessingClassPtr HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::processingClassPtr() const
	{
		return m_processingClassPtr;
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType>
	template<class T>
	typename HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::VTable HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::VTableInitializer<T>::m_vtable =
	{
		&HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::VTableInitializer<T>::hasFunc,
		&HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::VTableInitializer<T>::runFunc
	};

	template<class HasFuncChecker, class FuncRunner, class FirstArgType>
	template<class T>
	inline bool HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::VTableInitializer<T>::hasFunc(void* self)
	{
		return checkHasFunc(reinterpret_cast<T*>(self));
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType>
	template<class T>
	inline void HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::VTableInitializer<T>::runFunc(void * self, FirstArgType arg1)
	{
		checkAndRunFunc(reinterpret_cast<T*>(self), arg1);
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType>
	template<class T>
	template<class U>
	inline bool HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::VTableInitializer<T>::checkHasFunc(U runClass)
	{
		return HasFuncChecker::check(runClass);
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType>
	template<class T>
	template<class U>
	inline void HasOneArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType>::VTableInitializer<T>::checkAndRunFunc(U runClass, FirstArgType arg1)
	{
		if (!has_isActive_checker<>::check(runClass) || isActive_runner<>::checkAndRun(runClass))
			FuncRunner::checkAndRun(runClass, arg1);
	}
}
#endif // !HAS_ONE_ARG_FUNC_CLASS_H_
