#ifndef COMPONENT_DRAW_LIST_H_
#define COMPONENT_DRAW_LIST_H_

#include <memory>
#include <map>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>
#include "ComponentDrawRunner.h"

namespace tktk
{
	// �R���|�[�l���g�̕`�揈�����s�����X�g
	class ComponentDrawList
	{
	public:

		ComponentDrawList() = default;

	public:

		// �����̃R���|�[�l���g�̌^���udraw()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
		template <class ComponentType, std::enable_if_t<has_draw_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, std::enable_if_t<!has_draw_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

		// �`��D��x���Łudraw()�v�֐����Ă�
		void runDraw();

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		void moveNewComponent();

		// ���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	private:

		std::multimap<float, ComponentDrawRunner> m_drawList;
		std::multimap<float, ComponentDrawRunner> m_newComponentList;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �����̃R���|�[�l���g�̌^���udraw()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
	template<class ComponentType, std::enable_if_t<has_draw_checker<ComponentType*, void>::value>*>
	inline void ComponentDrawList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_newComponentList.emplace(componentPtr.lock()->getDrawPriority(), componentPtr);
	}
	template<class ComponentType, std::enable_if_t<!has_draw_checker<ComponentType*, void>::value>*>
	inline void ComponentDrawList::addComponent(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_DRAW_LIST_H_