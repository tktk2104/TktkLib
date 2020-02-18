#include "TktkClassFuncProcessor/ProcessingClass/ProcessingClassUseChecker.h"

#include <algorithm>

namespace tktk
{
	ProcessingClassUseChecker::~ProcessingClassUseChecker()
	{
		std::for_each(
			std::begin(m_usingPtrList),
			std::end(m_usingPtrList),
			[](SafetyVoidPtr* node) { delete(node); }
		);
		m_usingPtrList.clear();
	}

	void ProcessingClassUseChecker::deletePtr(SafetyVoidPtr * ptr)
	{
		auto deleteItr = m_usingPtrList.find(ptr);
		if (deleteItr == std::end(m_usingPtrList)) return;
		m_usingPtrList.erase(deleteItr);
		delete(ptr);
	}

	bool ProcessingClassUseChecker::isNull(SafetyVoidPtr * ptr) const
	{
		return (m_usingPtrList.count(ptr) == 0);
	}
}