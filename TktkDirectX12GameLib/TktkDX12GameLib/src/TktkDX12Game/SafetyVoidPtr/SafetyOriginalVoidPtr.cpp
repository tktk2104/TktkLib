#include "TktkDX12Game/SafetyVoidPtr/SafetyOriginalVoidPtr.h"

#include <algorithm>
#include "..\..\..\inc\TktkDX12Game\SafetyVoidPtr\SafetyOriginalVoidPtr.h"

namespace tktk
{
	std::unordered_set<void*> SafetyOriginalVoidPtr::m_useChecker;

	SafetyOriginalVoidPtr::SafetyOriginalVoidPtr()
		: m_rawPtr(nullptr)
		, m_vtablePtr(&SafetyVoidPtrVTableInitializer<void>::m_vtable)
	{
	}

	SafetyOriginalVoidPtr::~SafetyOriginalVoidPtr()
	{
		if (m_rawPtr != nullptr)
		{
			m_useChecker.erase(m_rawPtr);
			m_vtablePtr->runDestructor(m_rawPtr);
		}
	}

	SafetyOriginalVoidPtr::SafetyOriginalVoidPtr(SafetyOriginalVoidPtr&& other) noexcept
		: m_rawPtr(std::move(other.m_rawPtr))
		, m_vtablePtr(std::move(other.m_vtablePtr))
	{
		other.m_rawPtr = nullptr;
	}

	SafetyOriginalVoidPtr& SafetyOriginalVoidPtr::operator=(SafetyOriginalVoidPtr&& other) noexcept
	{
		m_rawPtr = std::move(other.m_rawPtr);
		m_vtablePtr = std::move(other.m_vtablePtr);
		other.m_rawPtr = nullptr;
		return *this;
	}

	bool SafetyOriginalVoidPtr::isUsePtr(void* ptr)
	{
		return (m_useChecker.count(ptr) != 0U);
	}

	void* SafetyOriginalVoidPtr::voidPtr() const
	{
		return m_rawPtr;
	}

	unsigned int SafetyOriginalVoidPtr::getClassId() const
	{
		return m_vtablePtr->getTypeId();
	}

	unsigned int SafetyOriginalVoidPtr::getClassSize() const
	{
		return m_vtablePtr->getTypeSize();
	}
}