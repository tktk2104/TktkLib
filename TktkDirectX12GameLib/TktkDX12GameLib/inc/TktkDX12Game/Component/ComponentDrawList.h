#ifndef COMPONENT_DRAW_LIST_H_
#define COMPONENT_DRAW_LIST_H_

#include <memory>
#include <map>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>
#include "ComponentDrawRunner.h"

namespace tktk
{
	class ComponentDrawList
	{
	public:

		ComponentDrawList() = default;

	public:

		// �����̃R���|�[�l���g�̌^���udraw()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
		// ���`��D��x�̓f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		template <class ComponentType, std::enable_if_t<has_draw_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::shared_ptr<ComponentType>& componentPtr);
		template <class ComponentType, std::enable_if_t<!has_draw_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::shared_ptr<ComponentType>& componentPtr);

		// �`��D��x���Łudraw()�v�֐����Ă�
		void runDraw();

		// ���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	private:

		std::multimap<float, ComponentDrawRunner> m_drawList;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �����̃R���|�[�l���g�̌^���udraw()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
	template<class ComponentType, std::enable_if_t<has_draw_checker<ComponentType*, void>::value>*>
	inline void ComponentDrawList::addComponent(const std::shared_ptr<ComponentType>& componentPtr)
	{
		m_drawList.emplace(componentPtr->getDrawPriority(), componentPtr);
	}
	template<class ComponentType, std::enable_if_t<!has_draw_checker<ComponentType*, void>::value>*>
	inline void ComponentDrawList::addComponent(const std::shared_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_DRAW_LIST_H_