#ifndef HAS_TWO_ARG_FUNC_CLASS_H_
#define HAS_TWO_ARG_FUNC_CLASS_H_

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasIsActiveChecker.h>
#include "../../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	template<class HasFuncChecker, class FuncRunner, class FirstArgType, class SecondArgType>
	class HasTwoArgFuncClass
	{
	public:

		template<class T>
		HasTwoArgFuncClass(ProcessingClassPtr processingClassPtr, T*);
		~HasTwoArgFuncClass() {};

	public:

		bool hasFuncCheck() const;

		void runFunc(FirstArgType arg1, SecondArgType arg2);

		ProcessingClassPtr processingClassPtr() const;

	private:


		struct VTable
		{
			bool(*hasFunc)(void*);
			void(*runFunc)(void*, FirstArgType, SecondArgType);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;

			static bool hasFunc(void* self);
			static void runFunc(void* self, FirstArgType arg1, SecondArgType arg2);

			template<class U>
			static bool checkHasFunc(U runClass);
			template<class U>
			static void checkAndRunFunc(U runClass, FirstArgType arg1, SecondArgType arg2);
		};

	private:

		ProcessingClassPtr m_processingClassPtr;

		VTable* m_vtablePtr;
	};

	template<class HasFuncChecker, class FuncRunner, class FirstArgType, class SecondArgType>
	template<class T>
	inline HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::HasTwoArgFuncClass(ProcessingClassPtr processingClassPtr, T *)
		: m_processingClassPtr(processingClassPtr)
		, m_vtablePtr(&VTableInitializer<T>::m_vtable)
	{
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType, class SecondArgType>
	inline bool HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::hasFuncCheck() const
	{
		if (m_processingClassPtr.isNull()) return false;
		return m_vtablePtr->hasFunc(m_processingClassPtr->voidPtr());
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType, class SecondArgType>
	inline void HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::runFunc(FirstArgType arg1, SecondArgType arg2)
	{
		if (m_processingClassPtr.isNull()) return;
		m_vtablePtr->runFunc(m_processingClassPtr->voidPtr(), arg1, arg2);
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType, class SecondArgType>
	inline ProcessingClassPtr HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::processingClassPtr() const
	{
		return m_processingClassPtr;
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType, class SecondArgType>
	template<class T>
	typename HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::VTable HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::VTableInitializer<T>::m_vtable =
	{
		&HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::VTableInitializer<T>::hasFunc,
		&HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::VTableInitializer<T>::runFunc
	};

	template<class HasFuncChecker, class FuncRunner, class FirstArgType, class SecondArgType>
	template<class T>
	inline bool HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::VTableInitializer<T>::hasFunc(void* self)
	{
		return checkHasFunc(reinterpret_cast<T*>(self));
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType, class SecondArgType>
	template<class T>
	inline void HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::VTableInitializer<T>::runFunc(void * self, FirstArgType arg1, SecondArgType arg2)
	{
		checkAndRunFunc(reinterpret_cast<T*>(self), arg1, arg2);
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType, class SecondArgType>
	template<class T>
	template<class U>
	inline bool HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::VTableInitializer<T>::checkHasFunc(U runClass)
	{
		return HasFuncChecker::check(runClass);
	}

	template<class HasFuncChecker, class FuncRunner, class FirstArgType, class SecondArgType>
	template<class T>
	template<class U>
	inline void HasTwoArgFuncClass<HasFuncChecker, FuncRunner, FirstArgType, SecondArgType>::VTableInitializer<T>::checkAndRunFunc(U runClass, FirstArgType arg1, SecondArgType arg2)
	{
		if (!has_isActive_checker<>::check(runClass) || isActive_runner<>::checkAndRun(runClass))
			FuncRunner::checkAndRun(runClass, arg1, arg2);
	}
}
#endif // !HAS_TWO_ARG_FUNC_CLASS_H_
