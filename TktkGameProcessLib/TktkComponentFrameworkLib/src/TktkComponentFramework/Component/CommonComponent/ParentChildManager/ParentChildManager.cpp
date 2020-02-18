#include "TktkComponentFramework/Component/CommonComponent/ParentChildManager/ParentChildManager.h"

#include <algorithm>
#include "TktkComponentFramework/GameObject/GameObject.h"
#include "TktkComponentFramework/GameObject/GameObjectManager.h"

namespace tktk
{
	void ParentChildManager::runAfterChangeParentAll(CfpPtr<GameObject> beforParent)
	{
		auto children = m_children.getChildren();
		std::for_each(
			std::begin(children),
			std::end(children),
			[&beforParent](CfpPtr<GameObject> node) { node->runAfterChangeParentAll(beforParent); }
		);
	}

	void ParentChildManager::removeChild(CfpPtr<GameObject> child)
	{
		m_children.remove(child);
	}

	void ParentChildManager::removeChildren()
	{
		m_children.removeAll();
	}

	void ParentChildManager::updateContainer()
	{
		m_children.updateContainer();
	}

	CfpPtr<GameObject> ParentChildManager::getParent() const
	{
		return m_parent;
	}

	void ParentChildManager::setParent(CfpPtr<GameObject> parent)
	{
		m_parent = parent;
	}

	const std::forward_list<CfpPtr<GameObject>>& ParentChildManager::getChildren() const
	{
		return m_children.getChildren();
	}

	void ParentChildManager::addChild(CfpPtr<GameObject> child)
	{
		m_children.addChild(child);
	}

	void ParentChildManager::sendMessage(int eventMessageType, const SafetyVoidPtr & param)
	{
		m_children.sendMessage(eventMessageType, param);
	}
}