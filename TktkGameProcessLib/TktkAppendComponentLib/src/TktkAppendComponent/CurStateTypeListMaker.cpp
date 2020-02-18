#include "TktkAppendComponent/CurStateTypeListMaker.h"

namespace tktk
{
	CurStateTypeListMaker CurStateTypeListMaker::m_self;

	CurStateTypeListMaker & CurStateTypeListMaker::makeStart()
	{
		m_self = CurStateTypeListMaker();
		return m_self;
	}

	CurStateTypeList* CurStateTypeListMaker::create()
	{
		return new CurStateTypeList();
	}
}