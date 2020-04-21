#include "TktkDX12Game/Component/ComponentManager.h"

namespace tktk
{
	void ComponentManager::update()
	{
		for (const auto& node : m_mainMap)
		{
			node.second->runUpdate();
		}


	}
}