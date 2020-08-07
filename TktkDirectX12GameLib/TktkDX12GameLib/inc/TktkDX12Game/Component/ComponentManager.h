#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include <memory>
#include <utility>
#include <map>
#include <unordered_map>
#include "ComponentUpdatePriorityList.h"
#include "ComponentMainList.h"
#include "ComponentStartFunc/ComponentSatrtList.h"
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

		// �Փ˔���̑g�ݍ��킹��ǉ�����
		void addCollisionGroup(int firstGroup, int secondGroup);

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		template <class ComponentType, class... Args>
		std::weak_ptr<ComponentType> createComponent(Args&&... args);

	private:

		// �P��ނ̃R���|�[�l���g���Ǘ����郊�X�g��V���ɍ��
		template<class ComponentType>
		void createList();

	private:

		ComponentUpdatePriorityList									m_priorityList;		// �R���|�[�l���g�̍X�V�����̌Ăяo�������Ǘ����郊�X�g
		std::multimap<float, std::shared_ptr<ComponentMainList>>	m_mainMap;			// �R���|�[�l���g�����񂷂邽�߂̃}�b�v
		std::unordered_map<int, std::weak_ptr<ComponentMainList>>	m_addComponentMap;	// �R���|�[�l���g��ǉ����邽�߂̃}�b�v
		ComponentSatrtList											m_startList;		// start()���ĂԂ��߂̃��X�g
		ComponentCollisionList										m_collisionList;	// �Փ˔��菈�����ĂԂ��߂̃��X�g
		ComponentDrawList											m_drawList;			// draw()���ĂԂ��߂̃��X�g
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
	inline std::weak_ptr<ComponentType> ComponentManager::createComponent(Args&&... args)
	{
		// �e���v���[�g�����̃R���|�[�l���g���ȑO�ɒǉ����ꂽ�������邩���ׂ�
		auto findNode = m_addComponentMap.find(ClassTypeChecker::getClassId<ComponentType>());
		
		// �����A���񂪏��߂Ēǉ�������ނ̃R���|�[�l���g�������ꍇ�A
		if (findNode == std::end(m_addComponentMap))
		{
			// �V���ȂP��ނ̃R���|�[�l���g���Ǘ����郊�X�g�����A
			createList<ComponentType>();

			// �ǉ��������X�g���擾����
			findNode = m_addComponentMap.find(ClassTypeChecker::getClassId<ComponentType>());
		}

		// �擾�����Ή�����u�P��ނ̃R���|�[�l���g���Ǘ����郊�X�g�v�̒��ɃR���|�[�l���g�����A����weak_ptr��Ԃ�
		auto createdComponent = (*findNode).second.lock()->createComponent<ComponentType>(std::forward<Args>(args)...);
		
		// �e��֐��Ăяo���������X�g�ɂ���weak_ptr��n��
		m_startList.addComponent(createdComponent);
		m_collisionList.addComponent(createdComponent);
		m_drawList.addComponent(createdComponent);

		// ������R���|�[�l���g��weak_ptr��Ԃ��ďI��
		return createdComponent;
	}

	// �P��ނ̃R���|�[�l���g���Ǘ����郊�X�g��V���ɍ��
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