#ifndef COMPONENT_BASE_PTR_H_
#define COMPONENT_BASE_PTR_H_

#include <memory>
#include "../ClassTypeChecker/ClassTypeChecker.h"
#include "ComponentPtr.h"

namespace tktk
{
	class ComponentBase;

	// �R���|�[�l���g�̌^�����B�������|�C���^�N���X
	class ComponentBasePtr
	{
	public:

		ComponentBasePtr() = default;

		template <class ComponentType>
		ComponentBasePtr(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		// �|�C���^���擾
		std::shared_ptr<ComponentBase> operator ->() const;

		// �����̃|�C���^�Ǝ��g�������|�C���^���w���Ă��邩���肷��
		bool isSame(const ComponentBasePtr& other) const;

		// �����̃|�C���^�Ǝ��g�������|�C���^���w���Ă��邩���肷��
		template <class ComponentType>
		bool isSame(const ComponentPtr<ComponentType>& other) const;

		// �e���v���[�g�����̌^�Ɏ��g�̃|�C���^���L���X�g�ł��邩���肷��
		template <class ComponentType>
		bool canCast() const;

		// �e���v���[�g�����̌^�ɃL���X�g�����uComponentPtr�v���擾����
		// �L���X�g�ł��Ȃ��������́uComponentPtr�v��Ԃ�
		template <class ComponentType>
		ComponentPtr<ComponentType> castPtr() const;

		// �A�N�e�B�u�t���O��ύX����
		void setActive(bool isActive) const;

		// ���S�t���O���擾����
		bool isDead() const;

	private:

		unsigned int					m_componentTypeId{ 0U };
		std::weak_ptr<ComponentBase>	m_componentPtr{ };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class ComponentType>
	inline ComponentBasePtr::ComponentBasePtr(const std::weak_ptr<ComponentType>& componentPtr)
		: m_componentTypeId(ClassTypeChecker::getClassId<ComponentType>())
		, m_componentPtr(componentPtr)
	{
	}

	// �����̃|�C���^�Ǝ��g�������|�C���^���w���Ă��邩���肷��
	template<class ComponentType>
	inline bool ComponentBasePtr::isSame(const ComponentPtr<ComponentType>& other) const
	{
		return other.isSame(castPtr<ComponentType>());
	}

	// �e���v���[�g�����̌^�Ɏ��g�̃|�C���^���L���X�g�ł��邩���肷��
	template<class ComponentType>
	inline bool ComponentBasePtr::canCast() const
	{
		return (ClassTypeChecker::getClassId<ComponentType>() == m_componentTypeId);
	}

	// �e���v���[�g�����̌^�ɃL���X�g�����uComponentPtr�v���擾����
	// �L���X�g�ł��Ȃ��������́uComponentPtr�v��Ԃ�
	template<class ComponentType>
	inline ComponentPtr<ComponentType> ComponentBasePtr::castPtr() const
	{
		if (canCast<ComponentType>())
		{
			return ComponentPtr<ComponentType>(std::dynamic_pointer_cast<ComponentType>(m_componentPtr.lock()));
		}
		return ComponentPtr<ComponentType>();
	}
}
#endif // !COMPONENT_BASE_PTR_H_