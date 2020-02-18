#include "TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasActiveCheckClass.h"

namespace tktk
{
	void HasActiveCheckClass::runFunc()
	{
		if (m_processingClass.isNull()) return;
		bool curIsActive = m_vtablePtr->isActive(m_processingClass->voidPtr());

		if (m_preIsActive != curIsActive)
		{
			if (!m_preIsActive)
			{
				m_vtablePtr->onEnable(m_processingClass->voidPtr());
			}
			else if (m_preIsActive)
			{
				m_vtablePtr->onDisable(m_processingClass->voidPtr());
			}
		}
		m_preIsActive = curIsActive;
	}

	bool HasActiveCheckClass::hasFuncCheck()
	{
		return m_vtablePtr->hasFunc(m_processingClass->voidPtr());
	}

	ProcessingClassPtr HasActiveCheckClass::processingClassPtr() const
	{
		return m_processingClass;
	}
}