#ifndef HAS_IS_DESTROY_CLASS_H_
#define HAS_IS_DESTROY_CLASS_H_

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasIsDestroyChecker.h>
#include "../../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	class HasIsDestroyClass
	{
	public:

		template<class T>
		HasIsDestroyClass(ProcessingClassPtr processingClass, T*);
		~HasIsDestroyClass() {}

	public:

		void runFunc();

		bool hasFuncCheck();

		ProcessingClassPtr processingClassPtr() const;

	private:

		struct VTable
		{
			bool(*hasFunc)(void*);
			bool(*isDestroy)(void*);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;

			static bool hasFunc(void* self);

			static bool isDestroy(void* self);

			template <class U>
			static bool chackHasFunc(U runClass);

			template <class U>
			static bool checkAndRunIsDestroy(U runClass);
		};

	private:

		ProcessingClassPtr m_processingClass;

		VTable* m_vtablePtr;
	};

	template<class T>
	inline HasIsDestroyClass::HasIsDestroyClass(ProcessingClassPtr processingClass, T*)
		: m_processingClass(processingClass)
		, m_vtablePtr(&VTableInitializer<T>::m_vtable)
	{
	}

	template <class T>
	HasIsDestroyClass::VTable HasIsDestroyClass::VTableInitializer<T>::m_vtable =
	{
		&HasIsDestroyClass::VTableInitializer<T>::hasFunc,
		&HasIsDestroyClass::VTableInitializer<T>::isDestroy
	};

	template<class T>
	inline bool HasIsDestroyClass::VTableInitializer<T>::hasFunc(void* self)
	{
		return chackHasFunc(reinterpret_cast<T*>(self));
	}

	template<class T>
	inline bool HasIsDestroyClass::VTableInitializer<T>::isDestroy(void* self)
	{
		return checkAndRunIsDestroy(reinterpret_cast<T*>(self));
	}

	template<class T>
	template<class U>
	inline bool HasIsDestroyClass::VTableInitializer<T>::chackHasFunc(U runClass)
	{
		return has_isDestroy_checker<>::check(runClass);
	}

	template<class T>
	template<class U>
	inline bool HasIsDestroyClass::VTableInitializer<T>::checkAndRunIsDestroy(U runClass)
	{
		return isDestroy_runner<>::checkAndRun(runClass);
	}
}
#endif // !HAS_IS_DESTROY_CLASS_H_