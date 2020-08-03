#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <forward_list>
#include "../../ComponentBase.h"

namespace tktk
{
	class CurStateTypeList;

	// �X�e�[�g�}�V�[���R���|�[�l���g
	// �y�O��R���|�[�l���g�FCurStateTypeList�z
	class StateMachine
		: public ComponentBase
	{
	public:

		StateMachine(int stateType);

	public:

		// <PolymorphismFunc>
		void onDisable();
		void start();
		void update();

	public:

		// ���̃X�e�[�g�Ɏq�v�f��ǉ�����
		void addChild(const GameObjectPtr& child);

		// ���̃X�e�[�g�ɃR���|�[�l���g��ǉ�����
		void addComponent(const ComponentBasePtr& componentPtr);

	private:

		// ���g�̃X�e�[�g�̎��
		int m_selfStateType;

		// ���g�̌��݂̃X�e�[�g�̎�ނ̃R���|�[�l���g
		ComponentPtr<CurStateTypeList> m_curStateTypeList;

		// ���̃X�e�[�g���Ǘ�����GameObject�̃R���e�i
		std::forward_list<GameObjectPtr> m_gameObjectList;

		// ���̃X�e�[�g���Ǘ�����R���|�[�l���g�̃R���e�i
		std::forward_list<ComponentBasePtr> m_componentList;
	};
}
#endif // !STATE_MACHINE_H_