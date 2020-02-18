#include "TktkClassFuncProcessor/ProcessingClass/ProcessingSimpleContainer.h"

#include <algorithm>

namespace tktk
{
	ProcessingSimpleContainer::~ProcessingSimpleContainer()
	{
		deleteAll();
	}

	void ProcessingSimpleContainer::updateContainer()
	{
		moveContainerNode();
		removeDeleteClass();
	}

	void ProcessingSimpleContainer::deleteAll()
	{
		std::for_each(
			std::begin(m_processingClassArray),
			std::end(m_processingClassArray),
			[](ProcessingClassPtr& node) { node.deletePtr(); }
		);
		m_processingClassArray.clear();

		std::for_each(
			std::begin(m_processingClassList),
			std::end(m_processingClassList),
			[](ProcessingClassPtr& node) { node.deletePtr(); }
		);
		m_processingClassList.clear();
	}

	void ProcessingSimpleContainer::moveContainerNode()
	{
		m_processingClassArray.reserve(m_processingClassArray.size() + m_addStaticClassNum);
		m_addStaticClassNum = 0U;

		for (AddClass& node : m_addClassList)
		{
			if (node.isStatic)
			{
				m_processingClassArray.push_back(std::move(node.processingClassPtr));
				continue;
			}
			m_processingClassList.push_front(std::move(node.processingClassPtr));
		}
		m_addClassList.clear();
	}

	void ProcessingSimpleContainer::removeDeleteClass()
	{
		for (auto itr = std::begin(m_processingClassArray); itr != std::end(m_processingClassArray);)
		{
			if ((*itr).isNull())
			{
				itr = m_processingClassArray.erase(itr);
				continue;
			}
			++itr;
		}

		m_processingClassList.remove_if(
			[](const ProcessingClassPtr& node) { return node.isNull(); }
		);
	}
}