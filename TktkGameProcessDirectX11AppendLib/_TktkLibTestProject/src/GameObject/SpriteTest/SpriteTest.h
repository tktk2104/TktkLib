#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Sprite/SpriteDrawerMaker.h>

#include "SpriteTestScript.h"

struct SpriteTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform2DMaker::makeStart(gameObject)
			.scaleRate(Vector2(20.0f))
			.create();

		tktk::SpriteDrawerMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.textureId(TEXTURE_2D_SPRITE_TEST)
			.blendRate({ 0.5f, 0.5f, 0.5f, 0.5f })
			.create();

		gameObject->createComponent<SpriteTestScript>();
	}
};