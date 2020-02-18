#include "TktkComponentFramework/Component/ComponentList.h"

#include <TktkClassFuncProcessor/ClassFuncProcessor.h>
#include "TktkComponentFramework/Component/ComponentBase.h"

namespace tktk
{
	void ComponentList::updateContainer()
	{
		m_componentList.remove_if(
			[](ProcessingClassPtr node) { return node.isNull(); }
		);

		m_afterChangeParentableList.updateContainer();
		m_messageableList.updateContainer();
		m_hasOnDestroyClassContainer.updateContainer();
		m_hasCollisionEnterClassContainer.updateContainer();
		m_hasCollisionStayClassContainer.updateContainer();
		m_hasCollisionExitClassContainer.updateContainer();
	}

	void ComponentList::destroyAll()
	{
		for (ProcessingClassPtr component : m_componentList)
		{
			component.deletePtr();
		}
		m_componentList.clear();
	}

	void ComponentList::afterChangeParentAll(CfpPtr<GameObject> beforParent)
	{
		m_afterChangeParentableList.runFunc(beforParent);
	}
	
	void ComponentList::handleMessageAll(int eventMessageType, const SafetyVoidPtr& param)
	{
		m_messageableList.runFunc(eventMessageType, param);
	}

	void ComponentList::onDestroyAll()
	{
		m_hasOnDestroyClassContainer.runFunc();
	}
	
	void ComponentList::onCollisionEnterAll(CfpPtr<GameObject> other)
	{
		m_hasCollisionEnterClassContainer.runFunc(other);
	}
	
	void ComponentList::onCollisionStayAll(CfpPtr<GameObject> other)
	{
		m_hasCollisionStayClassContainer.runFunc(other);
	}
	
	void ComponentList::onCollisionExitAll(CfpPtr<GameObject> other)
	{
		m_hasCollisionExitClassContainer.runFunc(other);
	}
}