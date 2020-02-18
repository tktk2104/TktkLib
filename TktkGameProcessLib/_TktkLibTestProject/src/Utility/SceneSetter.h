#pragma once

#include <TktkComponentFramework/Scene/SceneManager.h>
#include "../Scene/LoadScene.h"
#include "../Scene/MainScene.h"

struct SceneSetter
{
	static void set()
	{
		tktk::SceneManager::createScene<LoadScene>();
		tktk::SceneManager::createScene<MainScene>();

		tktk::SceneManager::enableScene<LoadScene>();
	}
};