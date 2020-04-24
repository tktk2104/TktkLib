#include "TktkDX12Game/Component/GameObjectComponentList.h"

namespace tktk
{
	void GameObjectComponentList::removeDeadComponent()
	{
		m_componentList.remove_if([this](const auto& node) { return node.isDead(); });
	}
}