#ifndef SAFETY_ORIGINAL_VOID_PTR_H_
#define SAFETY_ORIGINAL_VOID_PTR_H_

#ifdef _DEBUG
#include <stdexcept>
#endif
#include <unordered_set>
#include "SafetyVoidPtrVTable.h"
#include "SafetyReplicaVoidPtr.h"

namespace tktk
{
	// �R���X�g���N�^�����̃|�C���^���uvoidPtr�v�Ƃ��ĊǗ�����N���X
	// �R�s�[�s�A���[�u�\�����A���̃N���X���Ǘ�����|�C���^���Ǘ�����uSafetyReplicaVoidPtr�v�����֐�������
	// ���̃N���X�̃f�X�g���N�^���Ă΂�鎞�A�Ǘ�����|�C���^�̌��̌^�̃f�X�g���N�^���Ă�
	class SafetyOriginalVoidPtr
	{
	public:

		friend SafetyReplicaVoidPtr;

	public:

		// void*��nullptr�Ƃ��č쐬����
		SafetyOriginalVoidPtr();

		template<class T>
		explicit SafetyOriginalVoidPtr(T* rawPtr);

		// �f�X�g���N�^�Ŏ��g�̃|�C���^���J������
		~SafetyOriginalVoidPtr();

		// �R�s�[�֎~
		SafetyOriginalVoidPtr(const SafetyOriginalVoidPtr& other) = delete;
		SafetyOriginalVoidPtr& operator = (const SafetyOriginalVoidPtr& other) = delete;

		// ���[�u�R���X�g���N�^
		SafetyOriginalVoidPtr(SafetyOriginalVoidPtr&& other) noexcept;
		SafetyOriginalVoidPtr& operator = (SafetyOriginalVoidPtr&& other) noexcept;

	public:

		static bool isUsePtr(void* ptr);

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

		static std::unordered_set<void*> m_useChecker;

	private:

		void*					m_rawPtr;
		SafetyVoidPtrVTable*	m_vtablePtr;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class T>
	inline SafetyOriginalVoidPtr::SafetyOriginalVoidPtr(T* rawPtr)
		: m_rawPtr(rawPtr)
		, m_vtablePtr(&SafetyVoidPtrVTableInitializer<T>::m_vtable)
	{
		m_useChecker.insert(m_rawPtr);
	}

	template<class T>
	inline bool SafetyOriginalVoidPtr::isSame(T* other) const
	{
		return (m_rawPtr == other);
	}

	template<class T>
	inline bool SafetyOriginalVoidPtr::canCast() const
	{
		return (m_vtablePtr->getTypeId() == ClassTypeChecker::getClassId<T>());
	}

	template<class T>
	inline T* SafetyOriginalVoidPtr::castPtr() const
	{
#ifdef _DEBUG
		if (canCast<T>()) return reinterpret_cast<T*>(m_rawPtr);
		throw std::runtime_error("invalid cast");
#else
		return reinterpret_cast<T*>(m_rawPtr);
#endif // _DEBUG
	}
}
#endif // !SAFETY_ORIGINAL_VOID_PTR_H_