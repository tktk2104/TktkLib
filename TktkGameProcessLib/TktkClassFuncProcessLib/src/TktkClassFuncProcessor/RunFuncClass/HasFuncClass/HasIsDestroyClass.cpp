#include "TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasIsDestroyClass.h"

namespace tktk
{
	void HasIsDestroyClass::runFunc()
	{
		if (!m_processingClass.isNull() && m_vtablePtr->isDestroy(m_processingClass->voidPtr()))
		{
			m_processingClass.deletePtr();
		}
	}

	bool HasIsDestroyClass::hasFuncCheck()
	{
		return m_vtablePtr->hasFunc(m_processingClass->voidPtr());
	}

	ProcessingClassPtr HasIsDestroyClass::processingClassPtr() const
	{
		return m_processingClass;
	}
}