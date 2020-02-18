#include "TktkComponentFramework/Scene/SceneBase.h"

namespace tktk
{
	void SceneBase::frameBegin()
	{
		m_isActive = m_nextFrameIsActive;
	}

	void SceneBase::onEnable()
	{
		sceneStart();
	}

	void SceneBase::onDisable()
	{
		sceneEnd();
	}

	bool SceneBase::isActive() const
	{
		return m_isActive;
	}

	void SceneBase::setActive(bool isActive)
	{
		m_nextFrameIsActive = isActive;
	}
}