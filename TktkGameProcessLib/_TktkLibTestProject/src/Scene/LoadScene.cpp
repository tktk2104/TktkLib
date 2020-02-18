#include "LoadScene.h"

#include <TktkComponentFramework/Scene/SceneManager.h>
#include "MainScene.h"

#include "../TestObject/GameObject/TestGameObject.h"

void LoadScene::sceneStart()
{
	TestGameObject::create();

	tktk::SceneManager::enableScene<MainScene>();
	tktk::SceneManager::disableScene<LoadScene>();
}

void LoadScene::sceneEnd()
{
}
