#ifndef COMPONENT_COLLISION_LIST_H_
#define COMPONENT_COLLISION_LIST_H_

#include <array>
#include <unordered_map>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasIsCollideChecker.h>
#include "ComponentCollisionFuncRunner.h"

namespace tktk
{
	class ComponentCollisionList
	{
	public:

		ComponentCollisionList() = default;

	public:

		void runCollisionFunc();

		// ���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	public:

		void addCollisionGroup(int firstGroup, int secondGroup);

		// �����̃R���|�[�l���g�̌^���uisCollide()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
		template <class ComponentType, std::enable_if_t<has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, std::enable_if_t<!has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

	private:

		std::vector<std::pair<int, int>>							m_collisionGroupPairArray;
		std::unordered_multimap<int, ComponentCollisionFuncRunner>	m_collisionList;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �����̃R���|�[�l���g�̌^���uisCollide()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
	template<class ComponentType, std::enable_if_t<has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>*>
	inline void ComponentCollisionList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_collisionList.emplace(componentPtr.lock()->getCollisionGroup(), componentPtr);
	}
	template<class ComponentType, std::enable_if_t<!has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>*>
	inline void ComponentCollisionList::addComponent(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_COLLISION_LIST_H_