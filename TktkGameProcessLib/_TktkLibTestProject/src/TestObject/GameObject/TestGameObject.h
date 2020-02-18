#pragma once

#include <TktkComponentFramework/GameObject/GameObjectManager.h>

#include "TestGameObjectScript_1.h"
#include "TestGameObjectScript_2.h"

struct TestGameObject
{
	static void create()
	{
		tktk::CfpPtr<tktk::GameObject> gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->createComponent<TestGameObjectScript_1>();

		gameObject->createComponent<TestGameObjectScript_2>();
	}
};