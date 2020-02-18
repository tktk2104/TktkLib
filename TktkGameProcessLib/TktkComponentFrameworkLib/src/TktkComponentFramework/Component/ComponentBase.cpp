#include "TktkComponentFramework/Component/ComponentBase.h"

#include "TktkComponentFramework/GameObject/GameObject.h"

namespace tktk
{
	ComponentBase::ComponentBase(float drawPriority, int collisionGroupType)
		: m_drawPriority(drawPriority)
		, m_collisionGroupType(collisionGroupType)
	{
	}

	ComponentBase::~ComponentBase()
	{
	}

	void ComponentBase::frameBegin()
	{
		m_isActive = m_nextFrameIsActive;
	}

	bool ComponentBase::isActive() const
	{
		if (!m_isActive) return false;

		if (m_user.isNull()) return true;

		return m_user->isActive();
	}

	void ComponentBase::setActive(bool isActive)
	{
		m_nextFrameIsActive = isActive;
	}

	float ComponentBase::getUpdatePriority() const
	{
		return m_updatePriority;
	}

	float ComponentBase::getDrawPriority() const
	{
		return m_drawPriority;
	}

	int ComponentBase::getCollisionGroup() const
	{
		return m_collisionGroupType;
	}

	CfpPtr<GameObject> ComponentBase::getGameObject() const
	{
		return m_user;
	}

	void ComponentBase::setGameObject(CfpPtr<GameObject> user)
	{
		m_user = user;
	}
}