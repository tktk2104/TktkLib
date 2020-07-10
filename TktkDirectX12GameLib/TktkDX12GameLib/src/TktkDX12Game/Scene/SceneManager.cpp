#include "TktkDX12Game/Scene/SceneManager.h"

namespace tktk
{
	SceneManager::SceneManager(unsigned int sceneNum)
		: m_sceneArray(sceneNum)
	{
	}

	void SceneManager::enableScene(unsigned int id)
	{
		m_sceneArray.at(id)->enableScene();
	}

	void SceneManager::disableScene(unsigned int id)
	{
		m_sceneArray.at(id)->disableScene();
	}

	void SceneManager::update()
	{
		for (unsigned int i = 0; i < m_sceneArray.arrayMaxSize(); i++)
		{
			auto ptr = m_sceneArray.at(i);

			if (ptr != nullptr) ptr->update();
		}
	}
}