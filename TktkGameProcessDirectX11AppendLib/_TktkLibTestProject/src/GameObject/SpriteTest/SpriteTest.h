#pragma once

#include "CommonIncludePaths.h"
#include <TktkAppendDirectX11Component/Graphics/Sprite/SpriteDrawerMaker.h>
#include <TktkDirectX11Wrapper/Graphics/Texture2D/Asset/SystemTexture2DId.h>

#include "SpriteTestScript.h"

struct SpriteTest
{
	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		tktk::Transform2DMaker::makeStart(gameObject)
			//.scaleRate(Vector2(20.0f))
			.create();

		tktk::SpriteDrawerMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.textureId(tktk::SystemTexture2DId::blueShaderRes)//.textureId(1000000)
			//.blendRate({ 0.5f, 0.5f, 0.5f, 0.5f })
			.create();

		gameObject->createComponent<SpriteTestScript>();
	}
};