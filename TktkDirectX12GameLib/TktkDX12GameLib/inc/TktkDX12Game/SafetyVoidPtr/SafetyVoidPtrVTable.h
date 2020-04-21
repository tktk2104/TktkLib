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

	// ���O��VTable�̎��Ԃ����鏊
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

	// ���g�̃|�C���^�̌��̌^���ԍ����擾����
	template<class T>
	inline unsigned int SafetyVoidPtrVTableInitializer<T>::getTypeId()
	{
		return ClassTypeChecker::getClassId<T>();
	}

	// ���g�̃|�C���^�̌��̌^�̃T�C�Y���擾����
	template<class T>
	inline unsigned int SafetyVoidPtrVTableInitializer<T>::getTypeSize()
	{
		return sizeof(T);
	}

	// void�^�̃T�C�Y���擾���Ȃ��悤�ɂ��邽�߂̕�
	inline unsigned int SafetyVoidPtrVTableInitializer<void>::getTypeSize() { return 0U; }

	// ���g�̃|�C���^���J������
	template<class T>
	inline void SafetyVoidPtrVTableInitializer<T>::runDestructor(void* self)
	{
		// �|�C���^�̊J��
		delete(reinterpret_cast<T*>(self));
	}
}
#endif // !SAFETY_VOID_PTR_VTABLE_H_