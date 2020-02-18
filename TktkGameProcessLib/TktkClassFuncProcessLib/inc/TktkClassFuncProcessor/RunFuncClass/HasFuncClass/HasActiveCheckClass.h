#ifndef HAS_ACTIVE_CHECK_CLASS_H_
#define HAS_ACTIVE_CHECK_CLASS_H_

#include <TktkMetaFunc/HasFuncCheck/HasFuncCheckMacro.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasIsActiveChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnEnableChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnDisableChecker.h>
#include "../../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	// アクティブフラグを参照してフラグ変更時に対応した関数を呼ぶクラス
	class HasActiveCheckClass
	{
	public:

		template<class T>
		HasActiveCheckClass(ProcessingClassPtr processingClass, T*);
		~HasActiveCheckClass() {}

	public:

		void runFunc();

		bool hasFuncCheck();

		ProcessingClassPtr processingClassPtr() const;

	private:

		struct VTable
		{
			bool(*hasFunc)(void*);
			bool(*isActive)(void*);
			void(*onEnable)(void*);
			void(*onDisable)(void*);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;

			static bool hasFunc(void* self);

			static bool isActive(void* self);
			static void onEnable(void* self);
			static void onDisable(void* self);
			

			template <class U>
			static bool chackHasFunc(U runClass);

			template <class U>
			static bool checkAndRunIsActive(U runClass);
			template <class U>
			static void checkAndRunOnEnable(U runClass);
			template <class U>
			static void checkAndRunOnDisable(U runClass);
		};

	private:

		ProcessingClassPtr m_processingClass;

		bool m_preIsActive { false };

		VTable* m_vtablePtr;
	};

	template<class T>
	inline HasActiveCheckClass::HasActiveCheckClass(ProcessingClassPtr processingClass, T*)
		: m_processingClass(processingClass)
		, m_vtablePtr(&VTableInitializer<T>::m_vtable)
	{
	}

	template <class T>
	HasActiveCheckClass::VTable HasActiveCheckClass::VTableInitializer<T>::m_vtable =
	{
		&HasActiveCheckClass::VTableInitializer<T>::hasFunc,
		&HasActiveCheckClass::VTableInitializer<T>::isActive,
		&HasActiveCheckClass::VTableInitializer<T>::onEnable,
		&HasActiveCheckClass::VTableInitializer<T>::onDisable
	};

	template<class T>
	inline bool HasActiveCheckClass::VTableInitializer<T>::hasFunc(void* self)
	{
		return chackHasFunc(reinterpret_cast<T*>(self));
	}

	template<class T>
	inline void HasActiveCheckClass::VTableInitializer<T>::onEnable(void* self)
	{
		checkAndRunOnEnable(reinterpret_cast<T*>(self));
	}

	template<class T>
	inline void HasActiveCheckClass::VTableInitializer<T>::onDisable(void* self)
	{
		checkAndRunOnDisable(reinterpret_cast<T*>(self));
	}

	template<class T>
	inline bool HasActiveCheckClass::VTableInitializer<T>::isActive(void * self)
	{
		return checkAndRunIsActive(reinterpret_cast<T*>(self));
	}

	template<class T>
	template<class U>
	inline bool HasActiveCheckClass::VTableInitializer<T>::chackHasFunc(U runClass)
	{
		return (has_isActive_checker<>::check(runClass));
	}

	template<class T>
	template<class U>
	inline void HasActiveCheckClass::VTableInitializer<T>::checkAndRunOnEnable(U runClass)
	{
		onEnable_runner<>::checkAndRun(runClass);
	}

	template<class T>
	template<class U>
	inline void HasActiveCheckClass::VTableInitializer<T>::checkAndRunOnDisable(U runClass)
	{
		onDisable_runner<>::checkAndRun(runClass);
	}

	template<class T>
	template<class U>
	inline bool HasActiveCheckClass::VTableInitializer<T>::checkAndRunIsActive(U runClass)
	{
		return (!has_isActive_checker<>::check(runClass) || isActive_runner<>::checkAndRun(runClass));
	}
}
#endif // !HAS_ACTIVE_CHECK_CLASS_H_