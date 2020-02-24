#ifndef HAS_FUNC_CLASS_H_
#define HAS_FUNC_CLASS_H_

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasIsActiveChecker.h>
#include "../../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	template<template<class ReturnType, class... ArgsType> class FuncRunner, class ReturnType, class... ArgsType>
	class HasFuncClass
	{
	public:

		template<class T>
		HasFuncClass(ProcessingClassPtr processingClassPtr, T*)
			: m_processingClassPtr(processingClassPtr)
			, m_vtablePtr(&VTableInitializer<T>::m_vtable) {}

	public:

		ReturnType runFunc(ReturnType& defaultReturnValue, ArgsType... args)
		{
			if (m_processingClassPtr.isNull()) return defaultReturnValue;

			return m_vtablePtr->runFunc(m_processingClassPtr->voidPtr(), defaultReturnValue, std::forward<ArgsType>(args)...);
		}

		ProcessingClassPtr processingClassPtr() const
		{
			return m_processingClassPtr;
		}

	private:

		struct VTable
		{
			ReturnType(*runFunc)(void*, ReturnType&, ArgsType...);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;

			static ReturnType runFunc(void* self, ReturnType& defaultReturnValue, ArgsType... args)
			{
				return checkAndRunFunc(reinterpret_cast<T*>(self), defaultReturnValue, std::forward<ArgsType>(args)...);
			}

			template<class U>
			static ReturnType checkAndRunFunc(U runClass, ReturnType& defaultReturnValue, ArgsType... args)
			{
				if (isActive_runner<bool>::checkAndRun(runClass, true)) return FuncRunner<ReturnType, ArgsType...>::checkAndRun(runClass, std::forward<ArgsType>(args)...);
				return defaultReturnValue;
			}
		};

	private:

		ProcessingClassPtr m_processingClassPtr;

		VTable* m_vtablePtr;
	};

	template<template<class ReturnType, class... ArgsType> class FuncRunner, class ReturnType, class... ArgsType>
	template<class T>
	typename HasFuncClass<FuncRunner, ReturnType, ArgsType...>::VTable HasFuncClass<FuncRunner, ReturnType, ArgsType...>::VTableInitializer<T>::m_vtable =
	{
		&HasFuncClass<FuncRunner, ReturnType, ArgsType...>::template VTableInitializer<T>::runFunc
	};

	template<template<class ReturnType, class... ArgsType> class FuncRunner, class... ArgsType>
	class HasFuncClass<FuncRunner, void, ArgsType...>
	{
	public:

		template<class T>
		HasFuncClass(ProcessingClassPtr processingClassPtr, T*)
			: m_processingClassPtr(processingClassPtr)
			, m_vtablePtr(&VTableInitializer<T>::m_vtable) {}

	public:

		void runFunc(ArgsType... args)
		{
			if (m_processingClassPtr.isNull()) return;

			return m_vtablePtr->runFunc(m_processingClassPtr->voidPtr(), std::forward<ArgsType>(args)...);
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
				if (isActive_runner<bool>::checkAndRun(runClass, true)) FuncRunner<void, ArgsType...>::checkAndRun(runClass, std::forward<ArgsType>(args)...);
			}
		};

	private:

		ProcessingClassPtr m_processingClassPtr;

		VTable* m_vtablePtr;
	};

	template<template<class ReturnType, class... ArgsType> class FuncRunner, class... ArgsType>
	template<class T>
	typename HasFuncClass<FuncRunner, void, ArgsType...>::VTable HasFuncClass<FuncRunner, void, ArgsType...>::VTableInitializer<T>::m_vtable =
	{
		&HasFuncClass<FuncRunner, void, ArgsType...>::template VTableInitializer<T>::runFunc
	};
}
#endif // !HAS_FUNC_CLASS_H_