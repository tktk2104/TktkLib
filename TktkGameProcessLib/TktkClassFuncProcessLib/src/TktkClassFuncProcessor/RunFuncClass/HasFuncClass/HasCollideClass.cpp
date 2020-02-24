#include "TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasCollideClass.h"

namespace tktk
{
	void HasCollideClass::runFunc(HasCollideClass* other)
	{
		if (m_processingClass.isNull() || other->processingClassPtr().isNull()) return;
		if (m_processingClass->isSame(other->processingClassPtr()->voidPtr())) return;
		if (!isActive() || !other->isActive()) return;

		if (m_vtablePtr->isCollide(m_processingClass->voidPtr(), other->m_processingClass))
		{
			m_vtablePtr->onCollide(m_processingClass->voidPtr(), other->m_processingClass);
			other->m_vtablePtr->onCollide(other->m_processingClass->voidPtr(), m_processingClass);
		}
	}

	bool HasCollideClass::isActive()
	{
		return m_vtablePtr->isActive(m_processingClass->voidPtr());
	}

	ProcessingClassPtr HasCollideClass::processingClassPtr() const
	{
		return m_processingClass;
	}
}