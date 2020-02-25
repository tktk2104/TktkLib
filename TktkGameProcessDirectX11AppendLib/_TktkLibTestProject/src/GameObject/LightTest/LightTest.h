#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Light/PointLightMaker.h>
#include "LightTestScript.h"

struct LightTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform3DMaker::makeStart(gameObject)
			.position(Vector3(0.0f, 0.0f, -100.0f))
			.scaleRate(Vector3(0.5f))
			.create();

		tktk::PointLightMaker::makeStart(gameObject)
			.lightId(1)
			.create();

		gameObject->createComponent<LightTestScript>();
	}
};