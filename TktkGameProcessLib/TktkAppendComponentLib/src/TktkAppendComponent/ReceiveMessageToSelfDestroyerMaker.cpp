#include "TktkAppendComponent/ReceiveMessageToSelfDestroyerMaker.h"

namespace tktk
{
	ReceiveMessageToSelfDestroyerMaker ReceiveMessageToSelfDestroyerMaker::m_self;

	ReceiveMessageToSelfDestroyerMaker & ReceiveMessageToSelfDestroyerMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<ReceiveMessageToSelfDestroyer> ReceiveMessageToSelfDestroyerMaker::create()
	{
		return m_user->createComponent<ReceiveMessageToSelfDestroyer>(
			m_destroyMessegeType
			);
	}

	ReceiveMessageToSelfDestroyerMaker & ReceiveMessageToSelfDestroyerMaker::destroyMessegeType(int value)
	{
		m_destroyMessegeType = value;
		return *this;
	}

	void ReceiveMessageToSelfDestroyerMaker::reset()
	{
		m_self.m_destroyMessegeType = 0;
	}
}