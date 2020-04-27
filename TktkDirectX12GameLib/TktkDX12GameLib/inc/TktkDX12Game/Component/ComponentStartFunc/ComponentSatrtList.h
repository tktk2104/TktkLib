#ifndef COMPONENT_SATRT_LIST_H_
#define COMPONENT_SATRT_LIST_H_

#include <memory>
#include <forward_list>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include "ComponentStartRunner.h"

namespace tktk
{
	class ComponentSatrtList
	{
	public:

		ComponentSatrtList() = default;

	public:

		// �����̃R���|�[�l���g�̌^���ustart()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
		template <class ComponentType, std::enable_if_t<has_start_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, std::enable_if_t<!has_start_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

		// �ustart()�v�֐����Ă�
		void runStart();

		// ���Ɂustart()�v�֐����Ă΂ꂽ���A���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	private:

		std::forward_list<ComponentStartRunner> m_startList;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class ComponentType, std::enable_if_t<has_start_checker<ComponentType*, void>::value>*>
	inline void ComponentSatrtList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_startList.emplace_front(componentPtr);
	}
}
#endif // !COMPONENT_SATRT_LIST_H_