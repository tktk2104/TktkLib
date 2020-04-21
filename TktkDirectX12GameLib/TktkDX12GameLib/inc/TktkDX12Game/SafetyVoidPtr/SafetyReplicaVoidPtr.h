#ifndef SAFETY_REPLICA_VOID_PTR_H_
#define SAFETY_REPLICA_VOID_PTR_H_

#ifdef _DEBUG
#include <stdexcept>
#endif
#include "SafetyVoidPtrVTable.h"

namespace tktk
{
	class SafetyOriginalVoidPtr;

	// �uSafetyOriginalVoidPtr�v�ŊǗ�����|�C���^���R�s�[���Ďg�����߂̃N���X
	class SafetyReplicaVoidPtr
	{
	public:

		// nullptr�Ƃ��č쐬����
		SafetyReplicaVoidPtr();

		SafetyReplicaVoidPtr(const SafetyOriginalVoidPtr& original);

		// �f�X�g���N�^�ł͉������Ȃ�
		~SafetyReplicaVoidPtr() = default;

	public:

		bool isNull();

		// �����̃|�C���^�Ǝ��g�̎��|�C���^���������ǂ����𔻒肷��
		template<class T>
		bool isSame(T* other) const;

		// �e���v���[�g�p�����[�^�[�̌^�Ɏ��g�̎��|�C���^���L���X�g�ł��邩�𔻒肷��
		template<class T>
		bool canCast() const;

		// �e���v���[�g�p�����[�^�[�̌^�Ɏ��g�̃|�C���^���L���X�g����
		template<class T>
		T* castPtr() const;

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
	inline bool SafetyReplicaVoidPtr::isSame(T* other) const
	{
		return (m_rawPtr == other);
	}

	template<class T>
	inline bool SafetyReplicaVoidPtr::canCast() const
	{
		return (m_vtablePtr->getTypeId() == ClassTypeChecker::getClassId<T>());
	}

	template<class T>
	inline T* SafetyReplicaVoidPtr::castPtr() const
	{
		if (isNull()) return nullptr;

#ifdef _DEBUG
		if (canCast<T>()) return reinterpret_cast<T*>(m_rawPtr);
		throw std::runtime_error("invalid cast");
#else
		return reinterpret_cast<T*>(m_rawPtr);
#endif // _DEBUG
	}
}
#endif // !SAFETY_REPLICA_VOID_PTR_H_