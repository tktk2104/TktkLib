#ifndef GAME_OBJECT_COMPONENT_LIST_H_
#define GAME_OBJECT_COMPONENT_LIST_H_

#include <forward_list>
#include "ComponentGameObjectFuncRunner.h"

namespace tktk
{
	class ComponentBase;

	// �Q�[���I�u�W�F�N�g�������Ă���R���|�[�l���g�̃��X�g
	class GameObjectComponentList
	{
	public:

		GameObjectComponentList() = default;

	public:

		// �V���ȃR���|�[�l���g��ǉ�����
		template <class ComponentType>
		ComponentPtr<ComponentType> add(const std::weak_ptr<ComponentType>& weakPtr);

		// �e���v���[�g�����̌^�̃R���|�[�l���g���擾����
		// ���擾�ł��Ȃ�������nullptr��Ԃ�
		// �������Y������R���|�[�l���g����������ŏ��Ɍ������P��Ԃ�
		template <class ComponentType>
		ComponentPtr<ComponentType> find() const;

		// �e���v���[�g�����̌^�̃R���|�[�l���g��S�Ď擾����
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> findAll() const;

		// �S�Ắu�q���̑S�ẴR���|�[�l���g�̐e�v�f���ς�������֐��v���Ă�
		void runAfterChangeParentAll(const GameObjectPtr& beforParent);

		// �S�ẴR���|�[�l���g�̏ՓˊJ�n�֐����Ă�
		void runOnCollisionEnterAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g�̏Փ˒��֐����Ă�
		void runOnCollisionStayAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g�̏ՓˏI���֐����Ă�
		void runOnCollisionExitAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g���E��
		void destroyAll();

		void removeDeadComponent();

	private:

		std::forward_list<ComponentGameObjectFuncRunner> m_componentList;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �V���ȃR���|�[�l���g��ǉ�����
	template<class ComponentType>
	inline ComponentPtr<ComponentType> GameObjectComponentList::add(const std::weak_ptr<ComponentType>& weakPtr)
	{
		m_componentList.emplace_front(weakPtr);
		return ComponentPtr<ComponentType>(weakPtr);
	}

	// �e���v���[�g�����̌^�̃R���|�[�l���g���擾����
	// ���擾�ł��Ȃ�������nullptr��Ԃ�
	// �������Y������R���|�[�l���g����������ŏ��Ɍ������P��Ԃ�
	template<class ComponentType>
	inline ComponentPtr<ComponentType> GameObjectComponentList::find() const
	{
		for (const auto& node : m_componentList)
		{
			const auto& gameObjectPtr = node.getComponentBasePtr();

			if (gameObjectPtr.canCast<ComponentType>())
			{
				return gameObjectPtr.castPtr<ComponentType>();
			}
		}
		return ComponentPtr<ComponentType>();
	}

	// �e���v���[�g�����̌^�̃R���|�[�l���g��S�Ď擾����
	template<class ComponentType>
	inline std::forward_list<ComponentPtr<ComponentType>> GameObjectComponentList::findAll() const
	{
		std::forward_list<ComponentBasePtr> result;

		for (const auto& node : m_componentList)
		{
			const auto& gameObjectPtr = node.getComponentBasePtr();

			if (gameObjectPtr.canCast<ComponentType>())
			{
				result.push_front(gameObjectPtr.castPtr<ComponentType>());
			}
		}
		return result;
	}
}
#endif // !GAME_OBJECT_COMPONENT_LIST_H_
