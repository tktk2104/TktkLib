#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Sprite/SpriteDrawer.h>

#include "SpriteTestScript.h"

struct SpriteTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::Transform2DMaker::makeStart()
			.scaleRate(Vector2(0.0000001f))
			.create()
		);

		gameObject->createComponent<tktk::SpriteDrawer>(
			TEXTURE_2D_SPRITE_CUBE
			);

		gameObject->createComponent<SpriteTestScript>();
	}
};