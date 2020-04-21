#include "TktkDX12Game/SafetyVoidPtr/SafetyUniqueVoidPtr.h"

#include <algorithm>

namespace tktk
{
	SafetyUniqueVoidPtr::SafetyUniqueVoidPtr()
		: m_rawPtr(nullptr)
		, m_vtablePtr(&SafetyVoidPtrVTableInitializer<void>::m_vtable)
	{
	}

	SafetyUniqueVoidPtr::~SafetyUniqueVoidPtr()
	{
		if (m_rawPtr != nullptr)
		{
			m_vtablePtr->runDestructor(m_rawPtr);
		}
	}

	SafetyUniqueVoidPtr::SafetyUniqueVoidPtr(SafetyUniqueVoidPtr&& other) noexcept
		: m_rawPtr(std::move(other.m_rawPtr))
		, m_vtablePtr(std::move(other.m_vtablePtr))
	{
		other.m_rawPtr = nullptr;
	}

	SafetyUniqueVoidPtr& SafetyUniqueVoidPtr::operator=(SafetyUniqueVoidPtr&& other) noexcept
	{
		m_rawPtr = std::move(other.m_rawPtr);
		m_vtablePtr = std::move(other.m_vtablePtr);
		other.m_rawPtr = nullptr;
		return *this;
	}

	void* SafetyUniqueVoidPtr::voidPtr() const
	{
		return m_rawPtr;
	}

	unsigned int SafetyUniqueVoidPtr::getClassId() const
	{
		return m_vtablePtr->getTypeId();
	}

	unsigned int SafetyUniqueVoidPtr::getClassSize() const
	{
		return m_vtablePtr->getTypeSize();
	}
}