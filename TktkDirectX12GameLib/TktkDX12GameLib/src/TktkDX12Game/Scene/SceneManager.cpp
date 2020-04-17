#include "TktkDX12Game/Scene/SceneManager.h"

namespace tktk
{
	SceneManager::SceneManager(unsigned int sceneNum)
	{
		m_sceneArray.resize(sceneNum);
	}

	SceneManager::~SceneManager()
	{
		for (auto& node : m_sceneArray)
		{
			node.finalize();
		}
	}

	void SceneManager::enableScene(unsigned int id)
	{
		m_sceneArray.at(id).enableScene();
	}

	void SceneManager::disableScene(unsigned int id)
	{
		m_sceneArray.at(id).disableScene();
	}

	void SceneManager::update()
	{
		for (auto& node : m_sceneArray)
		{
			node.update();
		}
	}
}