#include "TktkDX12Game/Component/ComponentMainList.h"

namespace tktk
{
	void ComponentMainList::activeChangeCheck()
	{
		for (const auto& node : m_mainList)
		{
			if (!node->activeChangeCheck()) continue;

			if (node->isActive())
			{
				m_vtablePtr->runOnEnable(node);
			}
			else
			{
				m_vtablePtr->runOnDisable(node);
			}
		}
	}

	void ComponentMainList::runUpdate()
	{
		m_vtablePtr->runUpdate(m_mainList);
	}

	void ComponentMainList::removeDeadComponent()
	{
		m_mainList.remove_if([this](const auto& node)
		{
			if (node->isDead())
			{
				m_vtablePtr->runOnDestroy(node);
				return true;
			}
			return false;
		});
	}
}