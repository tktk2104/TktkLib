#include "TktkAppendComponent/StateMachineRegistrationList.h"

#include <algorithm>

namespace tktk
{
	void StateMachineRegistrationList::addNode(ProcessingClassPtr newNode)
	{
		m_stateMachineRegistrationList.push_front(newNode);
	}

	void StateMachineRegistrationList::updateList()
	{
		std::remove_if(
			std::begin(m_stateMachineRegistrationList),
			std::end(m_stateMachineRegistrationList),
			[](ProcessingClassPtr node) { return node.isNull(); }
		);
	}
}