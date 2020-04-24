#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include <memory>
#include <map>
#include <unordered_map>
#include "ComponentUpdatePriorityList.h"
#include "ComponentMainList.h"
#include "ComponentCollisionFunc/ComponentCollisionList.h"
#include "ComponentDrawFunc/ComponentDrawList.h"

namespace tktk
{
	class ComponentMainList;

	// �S�ẴR���|�[�l���g���Ǘ�����}�l�[�W���[�N���X
	class ComponentManager
	{
	public:

		ComponentManager() = default;

	public:

		// �R���|�[�l���g�̍X�V����
		void update();

		// �R���|�[�l���g�̕`�揈��
		void draw();

	public:

		// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		template <class ComponentType>
		void addUpdatePriority(float priority);

		void addCollisionGroup(int firstGroup, int secondGroup);

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		template <class ComponentType, class... Args>
		std::weak_ptr<ComponentType> createComponent(Args... args);

	private:

		// �P��ނ̃R���|�[�l���g���Ǘ����郊�X�g��V���ɍ��
		template<class ComponentType>
		void createList();

	private:

		ComponentUpdatePriorityList									m_priorityList;
		std::multimap<float, std::shared_ptr<ComponentMainList>>	m_mainMap;
		std::unordered_map<int, std::weak_ptr<ComponentMainList>>	m_addComponentMap;
		ComponentCollisionList										m_collisionList;
		ComponentDrawList											m_drawList;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
	// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
	template<class ComponentType>
	inline void ComponentManager::addUpdatePriority(float priority)
	{
		m_priorityList.addPriority<ComponentType>(priority);
	}

	// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
	template<class ComponentType, class ...Args>
	inline std::weak_ptr<ComponentType> ComponentManager::createComponent(Args ...args)
	{
		auto findNode = m_addComponentMap.find(ClassTypeChecker::getClassId<ComponentType>());
		
		if (findNode == std::end(m_addComponentMap))
		{
			createList<ComponentType>();
			findNode = m_addComponentMap.find(ClassTypeChecker::getClassId<ComponentType>());
		}
		auto createdComponent = (*findNode).second.lock()->createComponent<ComponentType>(args...);
		
		m_collisionList.addComponent(createdComponent);
		m_drawList.addComponent(createdComponent);

		return createdComponent;
	}

	// �R���|�[�l���g�̍X�V����
	template<class ComponentType>
	inline void ComponentManager::createList()
	{
		ComponentType* tempPtr = nullptr;
		auto createList = std::make_shared<ComponentMainList>(tempPtr);
		
		m_mainMap.emplace(m_priorityList.getPriority<ComponentType>(), createList);
		m_addComponentMap.emplace(ClassTypeChecker::getClassId<ComponentType>(), createList);
	}
}
#endif // !COMPONENT_MANAGER_H_