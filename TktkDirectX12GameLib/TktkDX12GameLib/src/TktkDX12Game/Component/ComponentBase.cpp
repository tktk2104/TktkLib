#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	ComponentBase::ComponentBase(float drawPriority)
		: m_drawPriority(drawPriority)
	{
	}

	ComponentBase::~ComponentBase()
	{
	}

	float ComponentBase::getDrawPriority() const
	{
		return m_drawPriority;
	}

	bool ComponentBase::activeChangeCheck()
	{
		if (m_isActive != m_nextFrameActive)
		{
			m_isActive = m_nextFrameActive;
			return true;
		}
		return false;
	}

	void ComponentBase::setActive(bool activeFlag)
	{
		m_nextFrameActive = activeFlag;
	}

	void ComponentBase::destroy()
	{
		m_isDead = true;
	}

	bool ComponentBase::isActive() const
	{
		return m_isActive;
	}

	bool ComponentBase::isDead() const
	{
		return m_isDead;
	}
}