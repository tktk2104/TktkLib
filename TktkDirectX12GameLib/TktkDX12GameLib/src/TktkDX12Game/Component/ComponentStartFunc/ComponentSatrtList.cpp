#include "TktkDX12Game/Component/ComponentStartFunc/ComponentSatrtList.h"

namespace tktk
{
	void ComponentSatrtList::runStart()
	{
		for (auto& node : m_startList)
		{
			node.runStart();
		}
	}

	void ComponentSatrtList::removeDeadComponent()
	{
		m_startList.remove_if([](const auto& node) { return node.isDead(); });
	}
}