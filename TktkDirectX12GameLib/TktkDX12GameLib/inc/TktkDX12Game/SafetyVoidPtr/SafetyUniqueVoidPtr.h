#ifndef SAFETY_UNIQUE_VOID_PTR_H_
#define SAFETY_UNIQUE_VOID_PTR_H_

#ifdef _DEBUG
#include <stdexcept>
#endif
#include "SafetyVoidPtrVTable.h"

namespace tktk
{
	// �R���X�g���N�^�����̃|�C���^���uvoidPtr�v�Ƃ��ĊǗ�����N���X
	// �R�s�[�s�A���[�u�\�ȁustd::unique_ptr�v�̂悤�Ȑ���
	// ���̃N���X�̃f�X�g���N�^���Ă΂�鎞�A�Ǘ�����|�C���^�̌��̌^�̃f�X�g���N�^���Ă�
	class SafetyUniqueVoidPtr
	{
	public:

		// void*��nullptr�Ƃ��č쐬����
		SafetyUniqueVoidPtr();

		template<class T>
		explicit SafetyUniqueVoidPtr(T* rawPtr);

		// �f�X�g���N�^�Ŏ��g�̃|�C���^���J������
		~SafetyUniqueVoidPtr();

		// �R�s�[�֎~
		SafetyUniqueVoidPtr(const SafetyUniqueVoidPtr& other) = delete;
		SafetyUniqueVoidPtr& operator = (const SafetyUniqueVoidPtr& other) = delete;

		// ���[�u�R���X�g���N�^
		SafetyUniqueVoidPtr(SafetyUniqueVoidPtr&& other) noexcept;
		SafetyUniqueVoidPtr& operator = (SafetyUniqueVoidPtr&& other) noexcept;

	public:

		// �����̃|�C���^�Ǝ��g�̎��|�C���^���������ǂ����𔻒肷��
		template<class T>
		bool isSame(T* other) const;

		// �e���v���[�g�p�����[�^�[�̌^�Ɏ��g�̎��|�C���^���L���X�g�ł��邩�𔻒肷��
		template<class T>
		bool canCast() const;

		// �e���v���[�g�p�����[�^�[�̌^�Ɏ��g�̃|�C���^���L���X�g����
		template<class T>
		T* castPtr() const;

		// voidPtr���擾����
		void* voidPtr() const;

		// �Ǘ����Ă���|�C���^�̌��̌^�ԍ����擾����
		unsigned int getClassId() const;

		// �Ǘ����Ă���|�C���^�̌��̌^�̃T�C�Y���擾����
		unsigned int getClassSize() const;

	private:

		void*					m_rawPtr;
		SafetyVoidPtrVTable*	m_vtablePtr;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class T>
	inline SafetyUniqueVoidPtr::SafetyUniqueVoidPtr(T* rawPtr)
		: m_rawPtr(rawPtr)
		, m_vtablePtr(&SafetyVoidPtrVTableInitializer<T>::m_vtable)
	{
	}

	// �����̃|�C���^�Ǝ��g�̎��|�C���^���������ǂ����𔻒肷��
	template<class T>
	inline bool SafetyUniqueVoidPtr::isSame(T* other) const
	{
		return (m_rawPtr == other);
	}

	// �e���v���[�g�p�����[�^�[�̌^�Ɏ��g�̎��|�C���^���L���X�g�ł��邩�𔻒肷��
	template<class T>
	inline bool SafetyUniqueVoidPtr::canCast() const
	{
		return (m_vtablePtr->getTypeId() == ClassTypeChecker::getClassId<T>());
	}

	// �e���v���[�g�p�����[�^�[�̌^�Ɏ��g�̃|�C���^���L���X�g����
	template<class T>
	inline T* SafetyUniqueVoidPtr::castPtr() const
	{
#ifdef _DEBUG
		if (canCast<T>()) return reinterpret_cast<T*>(m_rawPtr);
		throw std::runtime_error("invalid cast");
#else
		return reinterpret_cast<T*>(m_rawPtr);
#endif // _DEBUG
	}
}
#endif // !SAFETY_UNIQUE_VOID_PTR_H_