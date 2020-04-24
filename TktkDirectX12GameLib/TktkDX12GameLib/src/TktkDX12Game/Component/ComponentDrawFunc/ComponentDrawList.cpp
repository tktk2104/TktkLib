#include "TktkDX12Game/Component/ComponentDrawFunc/ComponentDrawList.h"

namespace tktk
{
	void ComponentDrawList::runDraw()
	{
		for (auto& node : m_drawList)
		{
			node.second.runDraw();
		}
	}

	void ComponentDrawList::removeDeadComponent()
	{
		for (auto itr = std::begin(m_drawList); itr != std::end(m_drawList);)
		{
			if ((*itr).second.isDead())
			{
				itr = m_drawList.erase(itr);
				continue;
			}
			++itr;
		}
	}
}