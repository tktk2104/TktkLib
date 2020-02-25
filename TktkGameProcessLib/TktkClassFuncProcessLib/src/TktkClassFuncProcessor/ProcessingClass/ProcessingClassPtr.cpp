#include "TktkClassFuncProcessor/ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	ProcessingClassUseChecker ProcessingClassPtr::m_useChecker;

	void ProcessingClassPtr::deletePtr()
	{
		if (m_managementPtr == nullptr) return;
		m_useChecker.deletePtr(m_managementPtr);
		m_managementPtr = nullptr;
	}

	bool ProcessingClassPtr::isNull() const
	{
		return (m_managementPtr == nullptr || m_useChecker.isNull(m_managementPtr));
	}

	bool ProcessingClassPtr::isSame(ProcessingClassPtr other) const
	{
		return (!isNull() && m_managementPtr->isSame(other.m_managementPtr));
	}

	const SafetyVoidPtr * ProcessingClassPtr::operator->() const
	{
		//if (isNull()) return nullptr;
		return m_managementPtr;
	}
}