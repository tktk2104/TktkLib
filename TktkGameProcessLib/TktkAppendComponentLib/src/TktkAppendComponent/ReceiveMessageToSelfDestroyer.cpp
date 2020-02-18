#include "TktkAppendComponent/ReceiveMessageToSelfDestroyer.h"

namespace tktk
{
	ReceiveMessageToSelfDestroyer::ReceiveMessageToSelfDestroyer(
		int destroyMessegeType
	)
		: m_destroyMessegeType(destroyMessegeType)
	{
	}

	void ReceiveMessageToSelfDestroyer::handleMessage(int eventMessageType, const tktk::SafetyVoidPtr& param)
	{
		if (eventMessageType == m_destroyMessegeType)
		{
			getGameObject()->destroy();
		}
	}
}