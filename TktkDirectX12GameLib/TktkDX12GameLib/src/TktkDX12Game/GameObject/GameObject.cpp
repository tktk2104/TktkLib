#include "TktkDX12Game/GameObject/GameObject.h"

namespace tktk
{
	GameObject::GameObject()
	{
	}

	void GameObject::update()
	{
		m_componentList.removeDeadComponent();

		m_isActive = m_nextFrameActive;
	}

	void GameObject::setActive(bool activeFlag)
	{
		m_nextFrameActive = activeFlag;
	}

	void GameObject::destroy()
	{
		m_isDead = true;
	}

	bool GameObject::isActive() const
	{
		return m_isActive;
	}

	bool GameObject::isDead() const
	{
		return m_isDead;
	}

	void GameObject::addGameObjectTag(int tag)
	{
		m_tagList.addTag(tag);
	}

	void GameObject::removeGameobjectTag(int tag)
	{
		m_tagList.removeTag(tag);
	}

	bool GameObject::containGameobjectTag(int tag) const
	{
		return m_tagList.contain(tag);
	}
}