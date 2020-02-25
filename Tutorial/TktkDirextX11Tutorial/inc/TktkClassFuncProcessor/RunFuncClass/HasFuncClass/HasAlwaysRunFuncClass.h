#ifndef HAS_ALWAYS_RUN_FUN_CCLASS_H_
#define HAS_ALWAYS_RUN_FUN_CCLASS_H_

#include "../../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	template<template<class ReturnType, class... ArgsType> class FuncRunner, class ReturnType, class... ArgsType>
	class HasAlwaysRunFuncClass
	{
	public:

		template<class T>
		HasAlwaysRunFuncClass(ProcessingClassPtr processingClassPtr, T*)
			: m_processingClassPtr(processingClassPtr)
			, m_vtablePtr(&VTableInitializer<T>::m_vtable) {}

	public:

		ReturnType runFunc(ReturnType& defaultReturnValue, ArgsType... args)
		{
			if (m_processingClassPtr.isNull()) return defaultReturnValue;

			return m_vtablePtr->runFunc(m_processingClassPtr->voidPtr(), std::forward<ArgsType>(args)...);
		}

		ProcessingClassPtr processingClassPtr() const
		{
			return m_processingClassPtr;
		}

	private:


		struct VTable
		{
			ReturnType(*runFunc)(void*, ArgsType...);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;

			static ReturnType runFunc(void* self, ArgsType... args)
			{
				return checkAndRunFunc(reinterpret_cast<T*>(self), std::forward<ArgsType>(args)...);
			}

			template<class U>
			static ReturnType checkAndRunFunc(U runClass, ArgsType... args)
			{
				return FuncRunner<ReturnType, ArgsType...>::checkAndRun(runClass, std::forward<ArgsType>(args)...);
			}
		};

	private:

		ProcessingClassPtr m_processingClassPtr;

		VTable* m_vtablePtr;
	};

	template<template<class ReturnType, class... ArgsType> class FuncRunner, class ReturnType, class... ArgsType>
	template<class T>
	typename HasAlwaysRunFuncClass<FuncRunner, ReturnType, ArgsType...>::VTable HasAlwaysRunFuncClass<FuncRunner, ReturnType, ArgsType...>::VTableInitializer<T>::m_vtable =
	{
		&HasAlwaysRunFuncClass<FuncRunner, ReturnType, ArgsType...>::template VTableInitializer<T>::runFunc
	};

	template<template<class ReturnType, class... ArgsType> class FuncRunner, class... ArgsType>
	class HasAlwaysRunFuncClass<FuncRunner, void, ArgsType...>
	{
	public:

		template<class T>
		HasAlwaysRunFuncClass(ProcessingClassPtr processingClassPtr, T*)
			: m_processingClassPtr(processingClassPtr)
			, m_vtablePtr(&VTableInitializer<T>::m_vtable) {}

	public:

		void runFunc(ArgsType... args)
		{
			if (m_processingClassPtr.isNull()) return;

			m_vtablePtr->runFunc(m_processingClassPtr->voidPtr(), std::forward<ArgsType>(args)...);
		}

		ProcessingClassPtr processingClassPtr() const
		{
			return m_processingClassPtr;
		}

	private:


		struct VTable
		{
			void(*runFunc)(void*, ArgsType...);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;

			static void runFunc(void* self, ArgsType... args)
			{
				checkAndRunFunc(reinterpret_cast<T*>(self), std::forward<ArgsType>(args)...);
			}

			template<class U>
			static void checkAndRunFunc(U runClass, ArgsType... args)
			{
				FuncRunner<void, ArgsType...>::checkAndRun(runClass, std::forward<ArgsType>(args)...);
			}
		};

	private:

		ProcessingClassPtr m_processingClassPtr;

		VTable* m_vtablePtr;
	};

	template<template<class ReturnType, class... ArgsType> class FuncRunner, class... ArgsType>
	template<class T>
	typename HasAlwaysRunFuncClass<FuncRunner, void, ArgsType...>::VTable HasAlwaysRunFuncClass<FuncRunner, void, ArgsType...>::VTableInitializer<T>::m_vtable =
	{
		&HasAlwaysRunFuncClass<FuncRunner, void, ArgsType...>::template VTableInitializer<T>::runFunc
	};
}
#endif // !HAS_ALWAYS_RUN_FUN_CCLASS_H_