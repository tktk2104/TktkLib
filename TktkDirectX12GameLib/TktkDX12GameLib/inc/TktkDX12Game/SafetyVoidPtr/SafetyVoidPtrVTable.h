#ifndef SAFETY_VOID_PTR_VTABLE_H_
#define SAFETY_VOID_PTR_VTABLE_H_

#include "ClassTypeChecker.h"

namespace tktk
{
	struct SafetyVoidPtrVTable
	{
		unsigned int(*getTypeId)();
		unsigned int(*getTypeSize)();
		void(*runDestructor)(void*);
	};

	// 自前のVTableの実態がある所
	template <class T>
	struct SafetyVoidPtrVTableInitializer
	{
		static unsigned int getTypeId();
		static unsigned int getTypeSize();
		static void runDestructor(void* self);

		static SafetyVoidPtrVTable m_vtable;
	};

	template<class T>
	typename SafetyVoidPtrVTable SafetyVoidPtrVTableInitializer<T>::m_vtable =
	{
		&SafetyVoidPtrVTableInitializer<T>::getTypeId,
		&SafetyVoidPtrVTableInitializer<T>::getTypeSize,
		&SafetyVoidPtrVTableInitializer<T>::runDestructor
	};

	// 自身のポインタの元の型情報番号を取得する
	template<class T>
	inline unsigned int SafetyVoidPtrVTableInitializer<T>::getTypeId()
	{
		return ClassTypeChecker::getClassId<T>();
	}

	// 自身のポインタの元の型のサイズを取得する
	template<class T>
	inline unsigned int SafetyVoidPtrVTableInitializer<T>::getTypeSize()
	{
		return sizeof(T);
	}

	// void型のサイズを取得しないようにするための物
	inline unsigned int SafetyVoidPtrVTableInitializer<void>::getTypeSize() { return 0U; }

	// 自身のポインタを開放する
	template<class T>
	inline void SafetyVoidPtrVTableInitializer<T>::runDestructor(void* self)
	{
		// ポインタの開放
		delete(reinterpret_cast<T*>(self));
	}
}
#endif // !SAFETY_VOID_PTR_VTABLE_H_