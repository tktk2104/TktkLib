#include "TktkDX12Game/SafetyVoidPtr/SafetyReplicaVoidPtr.h"

#include "TktkDX12Game/SafetyVoidPtr/SafetyOriginalVoidPtr.h"

namespace tktk
{
	SafetyReplicaVoidPtr::SafetyReplicaVoidPtr()
		: m_rawPtr(nullptr)
		, m_vtablePtr(&SafetyVoidPtrVTableInitializer<void>::m_vtable)
	{
	}

	SafetyReplicaVoidPtr::SafetyReplicaVoidPtr(const SafetyOriginalVoidPtr& original)
		: m_rawPtr(original.m_rawPtr)
		, m_vtablePtr(original.m_vtablePtr)
	{
	}

	bool SafetyReplicaVoidPtr::isNull()
	{
		if (m_rawPtr == nullptr) return true;

		if (SafetyOriginalVoidPtr::m_useChecker.count(m_rawPtr) != 0) return false;

		m_rawPtr = nullptr;

		return true;
	}

	unsigned int SafetyReplicaVoidPtr::getClassId() const
	{
		return m_vtablePtr->getTypeId();
	}

	unsigned int SafetyReplicaVoidPtr::getClassSize() const
	{
		return m_vtablePtr->getTypeSize();
	}
}