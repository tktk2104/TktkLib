#include "TktkDX12Game/Component/ComponentDrawRunner.h"

namespace tktk
{
	void ComponentDrawRunner::runDraw()
	{
		if (m_componentPtr->isActive())
		{
			m_vtablePtr->runDraw(m_componentPtr);
		}
	}

	bool ComponentDrawRunner::isDead() const
	{
		return m_componentPtr->isDead();
	}
}