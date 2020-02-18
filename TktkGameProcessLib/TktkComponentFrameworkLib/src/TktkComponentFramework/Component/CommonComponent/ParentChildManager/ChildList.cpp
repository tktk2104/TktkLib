#include "TktkComponentFramework/Component/CommonComponent/ParentChildManager/ChildList.h"

#include <algorithm>
#include <TktkClassFuncProcessor/ClassFuncProcessor.h>
#include "TktkComponentFramework/GameObject/GameObject.h"

namespace tktk
{
	void ChildList::addChild(CfpPtr<GameObject> child)
	{
		m_childList.push_front(child);
	}

	const std::forward_list<CfpPtr<GameObject>>& ChildList::getChildren() const
	{
		return m_childList;
	}

	void ChildList::updateContainer()
	{
		m_childList.remove_if(
			[](CfpPtr<GameObject> node) { return node.isNull(); }
		);
	}

	void ChildList::remove(CfpPtr<GameObject> gameObject)
	{
		m_childList.remove_if(
			[gameObject](CfpPtr<GameObject> node) { return (node == gameObject); }
		);
	}

	void ChildList::removeAll()
	{
		std::for_each(
			std::begin(m_childList),
			std::end(m_childList),
			[](CfpPtr<GameObject> node) { if (!node.isNull()) node.processingClassPtr().deletePtr(); }
		);
		m_childList.clear();
	}

	void ChildList::sendMessage(int eventMessageType, const SafetyVoidPtr & param)
	{
		std::for_each(
			std::begin(m_childList),
			std::end(m_childList),
			[&eventMessageType, &param](CfpPtr<GameObject> node) { if (!node.isNull()) node->sendMessage(eventMessageType, param); }
		);
	}
}