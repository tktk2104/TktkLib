#include "TktkAppendComponent/StateMachine.h"

#include <stdexcept>

namespace tktk
{
	CfpPtr<StateMachine> StateMachine::create(CfpPtr<GameObject> user, int stateType)
	{
		return user->addComponent(new StateMachine(stateType));
	}

	CfpPtr<StateMachine> StateMachine::create(CfpPtr<StateMachine> parentState, int stateType)
	{
		return parentState->addComponent(new StateMachine(stateType));
	}

	StateMachine::StateMachine(int stateType)
		: m_selfStateType(stateType)
	{
	}

	void StateMachine::onDisable()
	{
		m_hasSetActiveClassList.runFunc(false);
	}

	void StateMachine::update()
	{
		if (m_curStateTypeList.isNull())
		{
			auto m_curStateTypeList = getComponent<CurStateTypeList>();

			if (m_curStateTypeList.isNull())
			{
				throw std::runtime_error("StateMachine not found CurStateTypeList");
			}
		}
		m_hasSetActiveClassList.updateContainer();

		bool activeFlag = m_curStateTypeList->contain(m_selfStateType);

		m_hasSetActiveClassList.runFunc(activeFlag);

		m_stateMachineRegistrationList.updateList();
	}

	void StateMachine::addChild(bool isStatic, CfpPtr<GameObject> child)
	{
		child->setActive(false);

		getGameObject()->addChild(child);

		auto processingClass = child.processingClassPtr();

		GameObject* tempPtr = nullptr;

		m_hasSetActiveClassList.checkAndAdd<GameObject>(isStatic, processingClass, tempPtr);
	}
}
