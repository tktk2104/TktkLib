#include "TktkDX12Game/Scene/SceneInstanceCarrier.h"

namespace tktk
{
	void SceneInstanceCarrier::finalize()
	{
		if ((m_scenePtr.voidPtr() != nullptr) && m_isActive)
		{
			m_vtablePtr->end(m_scenePtr);
		}
	}

	void SceneInstanceCarrier::enableScene()
	{
		m_nextFrameIsActive = true;
	}

	void SceneInstanceCarrier::disableScene()
	{
		m_nextFrameIsActive = false;
	}

	void SceneInstanceCarrier::update()
	{
		if (m_scenePtr.voidPtr() == nullptr) return;

		if (m_isActive != m_nextFrameIsActive)
		{
			m_isActive = m_nextFrameIsActive;

			if (m_isActive) m_vtablePtr->start(m_scenePtr);
			else			m_vtablePtr->end(m_scenePtr);
		}

		if (m_isActive)		m_vtablePtr->update(m_scenePtr);
	}
}