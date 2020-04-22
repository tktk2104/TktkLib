#include "TktkDX12Game/Component/ComponentManager.h"

namespace tktk
{
	void ComponentManager::update()
	{
		for (const auto& node : m_mainMap)
		{
			node.second->activeChangeCheck();
		}

		for (const auto& node : m_mainMap)
		{
			node.second->runUpdate();
		}



		m_drawList.runDraw();

		for (const auto& node : m_mainMap)
		{
			node.second->removeDeadComponent();
		}

		m_drawList.removeDeadComponent();
	}
}