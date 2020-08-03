#ifndef COMPONENT_PTR_H_
#define COMPONENT_PTR_H_

#include <memory>

namespace tktk
{
	// �R���|�[�l���g�̌^����ێ������|�C���^�N���X
	template <class ComponentType>
	class ComponentPtr
	{
	public:

		ComponentPtr() = default;

		explicit ComponentPtr(const std::weak_ptr<ComponentType>& weakPtr);

	public:

		// �|�C���^�������؂ꂩ���肷��
		bool expired() const;

		// �����̃|�C���^�Ǝ��g�������|�C���^���w���Ă��邩���肷��
		bool isSame(const ComponentPtr<ComponentType>& other) const;

		// �|�C���^�̎g�p
		std::shared_ptr<ComponentType> operator ->() const;

	private:

		std::weak_ptr<ComponentType> m_componentPtr;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class ComponentType>
	inline ComponentPtr<ComponentType>::ComponentPtr(const std::weak_ptr<ComponentType>& weakPtr)
		: m_componentPtr(weakPtr)
	{
	}

	// �|�C���^�������؂ꂩ���肷��
	template<class ComponentType>
	inline bool ComponentPtr<ComponentType>::expired() const
	{
		return m_componentPtr.expired();
	}

	// �����̃|�C���^�Ǝ��g�������|�C���^���w���Ă��邩���肷��
	template<class ComponentType>
	inline bool ComponentPtr<ComponentType>::isSame(const ComponentPtr<ComponentType>& other) const
	{
		return !m_componentPtr.expired() && !other.m_componentPtr.expired() && m_componentPtr.lock() == other.m_componentPtr.lock();
	}

	// �|�C���^�̎g�p
	template<class ComponentType>
	inline std::shared_ptr<ComponentType> ComponentPtr<ComponentType>::operator->() const
	{
		if (m_componentPtr.expired()) return nullptr;
		return m_componentPtr.lock();
	}
}
#endif // !COMPONENT_PTR_H_