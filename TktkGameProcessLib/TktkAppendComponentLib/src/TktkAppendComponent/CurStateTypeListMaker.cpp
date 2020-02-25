#include "TktkAppendComponent/CurStateTypeListMaker.h"

namespace tktk
{
	CurStateTypeListMaker CurStateTypeListMaker::m_self;

	CurStateTypeListMaker & CurStateTypeListMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<CurStateTypeList> CurStateTypeListMaker::create()
	{
		return m_user->createComponent<CurStateTypeList>();
	}

	void CurStateTypeListMaker::reset()
	{
	}
}