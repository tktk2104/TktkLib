#pragma once

#include <memory>
#include "CommonIncludePaths.h"
#include "SoundTestScript.h"

struct SoundTest
{
	static tktk::CfpPtr<tktk::GameObject> create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->createComponent<SoundTestScript>();

		return gameObject;
	}
};