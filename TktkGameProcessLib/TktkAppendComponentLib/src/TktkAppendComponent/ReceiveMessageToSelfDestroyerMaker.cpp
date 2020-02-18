#include "TktkAppendComponent/ReceiveMessageToSelfDestroyerMaker.h"

namespace tktk
{
	ReceiveMessageToSelfDestroyerMaker ReceiveMessageToSelfDestroyerMaker::m_self;

	ReceiveMessageToSelfDestroyerMaker & ReceiveMessageToSelfDestroyerMaker::makeStart()
	{
		m_self = ReceiveMessageToSelfDestroyerMaker();
		return m_self;
	}

	ReceiveMessageToSelfDestroyer* ReceiveMessageToSelfDestroyerMaker::create()
	{
		return new ReceiveMessageToSelfDestroyer(
			m_destroyMessegeType
		);
	}

	ReceiveMessageToSelfDestroyerMaker & ReceiveMessageToSelfDestroyerMaker::destroyMessegeType(int value)
	{
		m_destroyMessegeType = value;
		return *this;
	}
}