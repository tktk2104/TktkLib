#include "TktkClassFuncProcessor/ProcessingClass/SafetyVoidPtr.h"
#include <algorithm> // std::move

namespace tktk
{
	SafetyVoidPtr::SafetyVoidPtr()
		: m_rawPtr(nullptr)
		, m_vtablePtr(&VTableInitializer<void>::m_vtable)
	{
	}

	SafetyVoidPtr::~SafetyVoidPtr()
	{
		m_vtablePtr->runDestructor(&m_rawPtr);
	}

	SafetyVoidPtr::SafetyVoidPtr(SafetyVoidPtr && other) noexcept
		: m_rawPtr(std::move(other.m_rawPtr))
		, m_vtablePtr(std::move(other.m_vtablePtr))
	{
		other.m_rawPtr = nullptr;
	}

	SafetyVoidPtr & SafetyVoidPtr::operator=(SafetyVoidPtr && other) noexcept
	{
		m_rawPtr = std::move(other.m_rawPtr);
		m_vtablePtr = std::move(other.m_vtablePtr);
		return *this;
	}

	void * SafetyVoidPtr::voidPtr() const
	{
		return m_rawPtr;
	}

	unsigned int SafetyVoidPtr::getClassId() const
	{
		return m_vtablePtr->getTypeId();
	}

	unsigned int SafetyVoidPtr::getClassSize() const
	{
		return m_vtablePtr->getTypeSize();
	}
}