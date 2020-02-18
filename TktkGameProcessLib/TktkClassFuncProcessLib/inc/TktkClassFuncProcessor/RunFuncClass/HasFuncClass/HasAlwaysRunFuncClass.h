#ifndef HAS_ALWAYS_RUN_FUN_CCLASS_H_
#define HAS_ALWAYS_RUN_FUN_CCLASS_H_

#include "../../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	template<class HasFuncChecker, class FuncRunner>
	class HasAlwaysRunFuncClass
	{
	public:

		template<class T>
		HasAlwaysRunFuncClass(ProcessingClassPtr processingClassPtr, T*);
		~HasAlwaysRunFuncClass() {};

	public:

		bool hasFuncCheck() const;

		void runFunc();

		ProcessingClassPtr processingClassPtr() const;

	private:


		struct VTable
		{
			bool(*hasFunc)(void*);
			void(*runFunc)(void*);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;

			static bool hasFunc(void* self);
			static void runFunc(void* self);

			template<class U>
			static bool checkHasFunc(U runClass);
			template<class U>
			static void checkAndRunFunc(U runClass);
		};

	private:

		ProcessingClassPtr m_processingClassPtr;

		VTable* m_vtablePtr;
	};

	template<class HasFuncChecker, class FuncRunner>
	template<class T>
	inline HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::HasAlwaysRunFuncClass(ProcessingClassPtr processingClassPtr, T *)
		: m_processingClassPtr(processingClassPtr)
		, m_vtablePtr(&VTableInitializer<T>::m_vtable)
	{
	}

	template<class HasFuncChecker, class FuncRunner>
	inline bool HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::hasFuncCheck() const
	{
		if (m_processingClassPtr.isNull()) return false;
		return m_vtablePtr->hasFunc(m_processingClassPtr->voidPtr());
	}

	template<class HasFuncChecker, class FuncRunner>
	inline void HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::runFunc()
	{
		if (m_processingClassPtr.isNull()) return;
		m_vtablePtr->runFunc(m_processingClassPtr->voidPtr());
	}

	template<class HasFuncChecker, class FuncRunner>
	inline ProcessingClassPtr HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::processingClassPtr() const
	{
		return m_processingClassPtr;
	}

	template<class HasFuncChecker, class FuncRunner>
	template<class T>
	typename HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::VTable HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::VTableInitializer<T>::m_vtable =
	{
		&HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::VTableInitializer<T>::hasFunc,
		&HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::VTableInitializer<T>::runFunc
	};

	template<class HasFuncChecker, class FuncRunner>
	template<class T>
	inline bool HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::VTableInitializer<T>::hasFunc(void* self)
	{
		return checkHasFunc(reinterpret_cast<T*>(self));
	}

	template<class HasFuncChecker, class FuncRunner>
	template<class T>
	inline void HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::VTableInitializer<T>::runFunc(void * self)
	{
		checkAndRunFunc(reinterpret_cast<T*>(self));
	}

	template<class HasFuncChecker, class FuncRunner>
	template<class T>
	template<class U>
	inline bool HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::VTableInitializer<T>::checkHasFunc(U runClass)
	{
		return HasFuncChecker::check(runClass);
	}

	template<class HasFuncChecker, class FuncRunner>
	template<class T>
	template<class U>
	inline void HasAlwaysRunFuncClass<HasFuncChecker, FuncRunner>::VTableInitializer<T>::checkAndRunFunc(U runClass)
	{
		FuncRunner::checkAndRun(runClass);
	}
}
#endif // !HAS_ALWAYS_RUN_FUN_CCLASS_H_