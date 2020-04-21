#include "TktkDX12Game/Component/ComponentMainList.h"

namespace tktk
{
	void ComponentMainList::runUpdate()
	{
		m_vtablePtr->runUpdate(m_mainList);
	}
}