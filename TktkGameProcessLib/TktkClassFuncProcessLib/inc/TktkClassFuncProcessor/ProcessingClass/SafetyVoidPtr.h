#ifndef SAFETY_VOID_PTR_H_
#define SAFETY_VOID_PTR_H_

#include "ClassTypeChecker.h"

namespace tktk
{
	// �R���X�g���N�^�����̃|�C���^���uvoidPtr�v�Ƃ��ĊǗ�����N���X
	// ���̃N���X�̃f�X�g���N�^���Ă΂�鎞�A�Ǘ�����|�C���^�̌��̌^�̃f�X�g���N�^���Ă�
	class SafetyVoidPtr
	{
	public:

		// void*��nullptr�Ƃ��č쐬����
		SafetyVoidPtr();

		template<class T>
		explicit SafetyVoidPtr(T* rawPtr);

		// �f�X�g���N�^�Ŏ��g�̃|�C���^���J������
		~SafetyVoidPtr();

		// �R�s�[�֎~
		SafetyVoidPtr(const SafetyVoidPtr& other) = delete;
		SafetyVoidPtr& operator = (const SafetyVoidPtr& other) = delete;

		// ���[�u�R���X�g���N�^
		SafetyVoidPtr(SafetyVoidPtr&& other) noexcept;
		SafetyVoidPtr& operator = (SafetyVoidPtr&& other) noexcept;

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

		// ���O��VTable
		struct VTable
		{
			unsigned int(*getTypeId)();
			unsigned int(*getTypeSize)();
			void(*runDestructor)(void**);
		};

		// ���O��VTable�̎��Ԃ����鏊
		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;
			static unsigned int getTypeId();
			static unsigned int getTypeSize();
			static void runDestructor(void** self);
		};

	private:

		void* m_rawPtr;
		VTable* m_vtablePtr;
	};

	template<class T>
	inline SafetyVoidPtr::SafetyVoidPtr(T* rawPtr)
		: m_rawPtr(rawPtr)
		, m_vtablePtr(&VTableInitializer<T>::m_vtable)
	{
	}

	// �����̃|�C���^�Ǝ��g�̎��|�C���^���������ǂ����𔻒肷��
	template<class T>
	inline bool SafetyVoidPtr::isSame(T * other) const
	{
		return (m_rawPtr == other);
	}

	// �e���v���[�g�p�����[�^�[�̌^�Ɏ��g�̎��|�C���^���L���X�g�ł��邩�𔻒肷��
	template<class T>
	inline bool SafetyVoidPtr::canCast() const
	{
		return (m_vtablePtr->getTypeId() == ClassTypeChecker::getClassId<T>());
	}

	// �e���v���[�g�p�����[�^�[�̌^�Ɏ��g�̃|�C���^���L���X�g����
	template<class T>
	inline T * SafetyVoidPtr::castPtr() const
	{
		if (canCast<T>()) return reinterpret_cast<T*>(m_rawPtr);
		return nullptr;
	}

	template<class T>
	typename SafetyVoidPtr::VTable SafetyVoidPtr::VTableInitializer<T>::m_vtable =
	{
		&SafetyVoidPtr::VTableInitializer<T>::getTypeId,
		&SafetyVoidPtr::VTableInitializer<T>::getTypeSize,
		&SafetyVoidPtr::VTableInitializer<T>::runDestructor
	};

	// ���g�̃|�C���^�̌��̌^���ԍ����擾����
	template<class T>
	inline unsigned int SafetyVoidPtr::VTableInitializer<T>::getTypeId()
	{
		return ClassTypeChecker::getClassId<T>();
	}

	// ���g�̃|�C���^�̌��̌^�̃T�C�Y���擾����
	template<class T>
	inline unsigned int SafetyVoidPtr::VTableInitializer<T>::getTypeSize()
	{
		return sizeof(T);
	}

	// void�^�̃T�C�Y���擾���Ȃ��悤�ɂ��邽�߂̕�
	inline unsigned int SafetyVoidPtr::VTableInitializer<void>::getTypeSize() { return 0U; }

	// ���g�̃|�C���^���J������
	template<class T>
	inline void SafetyVoidPtr::VTableInitializer<T>::runDestructor(void ** self)
	{
		// �����̃|�C���^�̎��ԁi�|�C���^�j�����Ɂunullptr�v�������牽�����Ȃ�
		if (*self == nullptr) return;

		// �|�C���^�̊J��
		delete(reinterpret_cast<T*>(*self));

		// �����̃|�C���^���unullptr�v�ɂ���
		*self = nullptr;
	}
}
#endif // !SAFETY_VOID_PTR_H_